/**
 * @file   events.hpp
 * @brief  Declaration of all the Event types.
 *
 * Copyright (C) 2010-2012 Adam Nielsen <malvineous@shikadi.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _CAMOTO_GAMEARCHIVE_EVENTS_HPP_
#define _CAMOTO_GAMEARCHIVE_EVENTS_HPP_

#include <boost/shared_ptr.hpp>
#include <exception>
#include <vector>

#include <camoto/stream.hpp>
#include <stdint.h>
#include <camoto/gamemusic/patchbank.hpp> // bad_patch

namespace camoto {
namespace gamemusic {

class EventHandler;

/// All channel numbers in the %Event struct must be less than this value.
const unsigned int MAX_CHANNELS = 256;

/// Type to use for all microsecond-per-tick values.
typedef double tempo_t;

/// Base class to represent events in the file.
/**
 * Will be extended by descendent classes to hold format-specific data.
 * The entries here will be valid for all music types.
 */
struct Event {
	/// Helper function (for debugging) to return all the data as a string
	virtual std::string getContent() const
		throw ();

	/// Call the handleEvent() function in an EventHandler class, passing this
	/// event as the parameter.
	virtual void processEvent(EventHandler *handler)
		throw (std::exception) = 0;

	/// The number of ticks (since the start of the song) when this event should
	/// be actioned.
	unsigned long absTime;

	/// Channel number (1+, channel 0 means a global event affecting all channels)
	unsigned int channel;

	/// Original channel number in the source file.
	/**
	 * This should only be used by file format handlers which may need to know
	 * where the event came from.  For example the CMF file format assigns special
	 * instruments to certain MIDI channels, so the original MIDI channel will be
	 * stored here.  The 'channel' field above cannot contain this value, as only
	 * one note can be played at a time on that channel, whereas a single MIDI
	 * channel can play up to 128 notes simultaneously.
	 */
	unsigned int sourceChannel;
};

/// Shared pointer to an event
typedef boost::shared_ptr<Event> EventPtr;

/// Vector of shared event pointers
typedef std::vector<EventPtr> EventVector;

/// Shared pointer to a list of events
typedef boost::shared_ptr<EventVector> EventVectorPtr;


/// Changing the tempo changes the rate at which the ticks tick.
/**
 * Remember that since the tick length can vary, you cannot calculate the
 * absolute time of a note by multiplying the tick length by Event.absTime,
 * as this does not take into account any tempo changes in the middle of the
 * song.
 */
struct TempoEvent: virtual public Event
{
	/// Number of microseconds per tick.
	tempo_t usPerTick;

	virtual std::string getContent() const
		throw ();

	virtual void processEvent(EventHandler *handler)
		throw (std::exception);
};


/// A single note is now playing on this channel.
/**
 * @note Only one note can be playing on each channel at a time.  For formats
 *       which allow multiple notes on each channel (e.g. MIDI) some "virtual"
 *       channels will have to be created.
 */
struct NoteOnEvent: virtual public Event
{
	virtual std::string getContent() const
		throw ();

	virtual void processEvent(EventHandler *handler)
		throw (std::exception);

	/// Instrument to play this note with.  This is an index into the vector
	/// returned by Music::getInstruments().
	unsigned int instrument;

	/// Note frequency (440000 == 440Hz)
	unsigned int milliHertz;

	/// Velocity.  0 == unused/default, 1 == quiet, 255 = loud
	uint8_t velocity;
};


/// All notes on this channel are now silenced.
struct NoteOffEvent: virtual public Event
{
	virtual std::string getContent() const
		throw ();

	virtual void processEvent(EventHandler *handler)
		throw (std::exception);
};


/// Change the pitch of the note on this channel.
/**
 * @note Only one note can be playing on each channel at a time.  For formats
 *       which allow multiple notes on each channel (e.g. MIDI) some "virtual"
 *       channels will have to be created.
 */
struct PitchbendEvent: virtual public Event
{
	/// Note frequency (440000 == 440Hz)
	int milliHertz;

	virtual std::string getContent() const
		throw ();

	virtual void processEvent(EventHandler *handler)
		throw (std::exception);
};


/// Configure the synthesiser's global parameters.
/**
 * This event can occur at any time.
 */
struct ConfigurationEvent: virtual public Event
{
	/// What can be configured.
	/**
	 * For boolean values (Enable*) a value of 0 is false/disabled and a value
	 * of nonzero (usually 1) is true/enabled.
	 */
	enum ConfigurationType {

		/// Enable OPL3 mode (or limit to OPL2)
		/**
		 * value: 1 for OPL3 mode, 0 for OPL2 mode
		 */
		EnableOPL3,

		/// Extend range of OPL tremolo
		/**
		 * value: bit0 = 1 to enable, 0 to disable
		 *        bit1 = 0-1 as chip index
		 */
		EnableDeepTremolo,

		/// Extend range of OPL vibrato
		/**
		 * value: bit0 = 1 to enable, 0 to disable
		 *        bit1 = 0-1 as chip index
		 */
		EnableDeepVibrato,

		/// Enable OPL rhythm mode
		/**
		 * value: 1 to enable, 0 to disable
		 *
		 * This is used by the CMF handler and MIDI controller event 0x67.
		 */
		EnableRhythm,

		/// Enable use of wavesel registers
		/**
		 * value: 1 to enable, 0 to disable
		 */
		EnableWaveSel,
	};

	/// What we are configuring
	ConfigurationType configType;

	/// What value we are setting (meaning dependent on config type)
	int value;

	virtual std::string getContent() const
		throw ();

	virtual void processEvent(EventHandler *handler)
		throw (std::exception);
};


/// Exception thrown when playing a note on an invalid channel
/**
 * Certain formats have limits on which types of instruments can be played on
 * which channels (e.g. OPL rhythm mode instruments must be played on special
 * rhythm channels.)  This exception is thrown when a mismatch occurs.  The
 * what() function will return a reason suitable for display to the user.
 */
class EChannelMismatch: virtual public std::exception {
	protected:
		int instIndex;      ///< Instrument ID (starting at 0)
		int targetChannel;  ///< Target channel (starting at 0, but +1 for messages)
		std::string reason; ///< User-readable reason for mismatch

		/// Message displayed to use.
		/**
		 * This is declared mutable as it will be populated by the first call to
		 * the const function what(), then the cached value will be returned on
		 * subsequent calls.
		 */
		mutable std::string msg;

	public:
		EChannelMismatch(int instIndex, int targetChannel, const std::string& reason)
			throw ();

		virtual ~EChannelMismatch()
			throw ();

		virtual const char *what() const
			throw ();
};

/// Callback interface
/**
 * Any class implementing this interface will be able to process different
 * events in typed functions, removing the need to dynamic_cast to figure
 * out the event type.
 */
class EventHandler
{
	public:
		virtual void handleEvent(const TempoEvent *ev)
			throw (stream::error) = 0;

		/// A note is being played.
		/**
		 * @throws EChannelMismatch if the note could not be played on the given
		 *   channel (e.g. channel does not support the instrument.)
		 *
		 * @throws bad_patch if the note could not be played with the given
		 *   instrument (e.g. not enough instruments in patch bank.)
		 */
		virtual void handleEvent(const NoteOnEvent *ev)
			throw (stream::error, EChannelMismatch, bad_patch) = 0;

		virtual void handleEvent(const NoteOffEvent *ev)
			throw (stream::error) = 0;

		virtual void handleEvent(const PitchbendEvent *ev)
			throw (stream::error) = 0;

		virtual void handleEvent(const ConfigurationEvent *ev)
			throw (stream::error) = 0;

		void handleAllEvents(const EventVectorPtr& events)
			throw (stream::error, EChannelMismatch, bad_patch);

};


} // namespace gamemusic
} // namespace camoto

#endif // _CAMOTO_GAMEARCHIVE_EVENTS_HPP_
