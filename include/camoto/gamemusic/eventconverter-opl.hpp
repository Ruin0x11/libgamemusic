/**
 * @file   eventconverter-opl.hpp
 * @brief  EventConverter implementation that produces OPL data from Events.
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

#ifndef _CAMOTO_GAMEMUSIC_EVENTCONVERTER_OPL_HPP_
#define _CAMOTO_GAMEMUSIC_EVENTCONVERTER_OPL_HPP_

#include <camoto/gamemusic/events.hpp>
#include <camoto/gamemusic/patchbank-opl.hpp>
#include <camoto/stream.hpp>

namespace camoto {
namespace gamemusic {

/// Flag for delay type
enum DelayType {
	DelayIsPreData,  ///< The delay should occur before using the register value
	DelayIsPostData, ///< The delay should happen after the reg val is used
};

/// Flags that control the conversion to OPL data.
enum OPLWriteFlags {
	Default          = 0x00,  ///< No special treatment
	IntegerNotesOnly = 0x01,  ///< Disable pitchbends
};

/// Information about a single OPL reg/val pair.
struct OPLEvent {
	/// Number of ticks to delay before the data bytes are actioned.
	uint32_t delay;

	/// Which OPL chip to use (0 or 1)
	uint8_t chipIndex;

	/// OPL register
	uint8_t reg;

	/// Value to write to OPL register
	uint8_t val;

	/// Set to non-zero to signify a tempo change.
	/**
	 * This value is only used when decoding OPL data.  It is ignored when
	 * writing OPL data (there is a separate callback function to adjust the
	 * tempo there.)
	 *
	 * If a delay is also specified, the order depends on the DelayType in use.
	 * DelayIsPreData will delay at the old tempo before adjusting to the new
	 * tempo, while DelayIsPostData will immediately adjust to the new tempo
	 * then delay at the new speed.
	 */
	uint32_t tempo;
};

#define OPL_FNUM_DEFAULT  49716.0   ///< Most common conversion value
#define OPL_FNUM_ROUND    50000.0   ///< Alternate value used occasionally

/// Callback used to do something with the OPL data supplied by oplEncode().
class OPLWriterCallback {
	public:
		/// Handle the next OPL register/value pair.
		/**
		 * @param oplEvent
		 *   The reg/val pair and associated data to do something with.
		 *
		 * @throw stream:error
		 *   The data could not be processed for some reason.
		 *
		 * @note The delay value in oplEvent is always to occur before the data
		 *   bytes are actioned, i.e. as if DelayIsPreData is always set.
		 */
		virtual void writeNextPair(const OPLEvent *oplEvent)
			throw (stream::error) = 0;

		/// Change the length of the delay values for subsequent events.
		/**
		 * @param usPerTick
		 *   Number of microseconds per tick.
		 */
		virtual void writeTempoChange(unsigned long usPerTick)
			throw (stream::error) = 0;
};

/// Immediate conversion between incoming events and OPL data.
/**
 * This class is used to convert Event instances into raw OPL data.  It is used
 * for both real time playback of songs and to write them into formats that
 * store raw OPL data.
 *
 * @note Unsupported instruments (i.e. non-OPL instruments, like MIDI) won't
 *   generate any errors.  Instead all notes for those instruments will be
 *   ignored.  This is to facilitate real time playing of a song with
 *   multiple instrument types, without requiring any special code to split
 *   the song up by instrument type.
 *
 * @note This class does no optimisation of the OPL data.  Multiple redundant
 *   writes will occur.  The OPLEncoder class does however perform optimisation.
 */
class EventConverter_OPL: virtual public EventHandler
{
	public:
		/// Set encoding parameters.
		/**
		 * @param flags
		 *   One or more OPLWriteFlags to use to control the conversion.
		 *
		 * @param fnumConversion
		 *   Conversion constant to use when converting Hertz into OPL frequency
		 *   numbers.  Can be one of OPL_FNUM_* or a raw value.
		 */
		EventConverter_OPL(OPLWriterCallback *cb, double fnumConversion,
			unsigned int flags)
			throw ();

		/// Destructor.
		virtual ~EventConverter_OPL()
			throw ();

		/// Set the instruments to use for note events.
		/**
		 * @note Unsupported instruments (i.e. non-OPL instruments, like MIDI) won't
		 *   generate any errors.  Instead all notes for those instruments will be
		 *   ignored.  This is to facilitate real time playing of a song with
		 *   multiple instrument types, without requiring any special code to split
		 *   the song up by instrument type.
		 */
		virtual void setPatchBank(const PatchBankPtr& instruments)
			throw (EBadPatchType);

		// EventHandler overrides

		virtual void handleEvent(const TempoEvent *ev)
			throw (stream::error);

		virtual void handleEvent(const NoteOnEvent *ev)
			throw (stream::error, EChannelMismatch, EBadPatchType);

		virtual void handleEvent(const NoteOffEvent *ev)
			throw (stream::error);

		virtual void handleEvent(const PitchbendEvent *ev)
			throw (stream::error);

		virtual void handleEvent(const ConfigurationEvent *ev)
			throw (stream::error);

	private:
		OPLWriterCallback *cb;     ///< Callback to handle the generated OPL data
		double fnumConversion;     ///< Conversion value to use in Hz -> fnum calc
		unsigned int flags;        ///< One or more OPLWriteFlags

		unsigned long lastTick;    ///< Time of last event
		unsigned long cachedDelay; ///< Delay to add on to next reg write
		unsigned long postponedDelay; ///< Delay for next event when DelayIsPostData
		uint8_t oplState[2][256];  ///< Current register values
		OPLPatchBankPtr inst;      ///< Last set patch bank

		/// Update oplState then call handleNextPair()
		/**
		 * @param delay
		 *   The number of ticks to wait *before* processing reg/val.
		 *
		 * @param chipIndex
		 *   0 or 1 for which OPL chip to use.
		 *
		 * @param reg
		 *   OPL register to write to.
		 *
		 * @param val
		 *   Value to write to the OPL register.
		 *
		 * @throw stream::error
		 *   The data could not be processed.
		 */
		void processNextPair(uint32_t delay, uint8_t chipIndex, uint8_t reg, uint8_t val)
			throw (stream::error);

		/// Write one operator's patch settings (modulator or carrier)
		/**
		 * @param chipIndex
		 *   0 or 1 for which OPL chip to use.
		 *
		 * @param oplChannel
		 *   0-8 inclusive for OPL hardware channel to use.
		 *
		 * @param opNum
		 *   0 for modulator, 1 for carrier.
		 *
		 * @param i
		 *   Patch to write to OPL chip.
		 *
		 * @param velocity
		 *   Velocity value to set.
		 *
		 * @throw stream::error
		 *   The data could not be processed.
		 */
		void writeOpSettings(int chipIndex, int oplChannel, int opNum,
			OPLPatchPtr i, int velocity)
			throw (stream::error);

};

} // namespace gamemusic
} // namespace camoto

#endif // _CAMOTO_GAMEMUSIC_EVENTCONVERTER_OPL_HPP_