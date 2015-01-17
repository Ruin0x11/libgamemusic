/**
 * @file   mus-mus-dmx.hpp
 * @brief  Support for id Software MIDI (.mus) format.
 *
 * Copyright (C) 2010-2015 Adam Nielsen <malvineous@shikadi.net>
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

#ifndef _CAMOTO_GAMEMUSIC_MUS_MUS_DMX_HPP_
#define _CAMOTO_GAMEMUSIC_MUS_MUS_DMX_HPP_

#include <camoto/gamemusic/musictype.hpp>

namespace camoto {
namespace gamemusic {

/// MusicType implementation for DMX MUS files.
class MusicType_MUS: virtual public MusicType
{
	public:
		MusicType_MUS();
		virtual std::string getCode() const;
		virtual std::string getFriendlyName() const;
		virtual std::vector<std::string> getFileExtensions() const;
		virtual unsigned long getCaps() const;
		virtual Certainty isInstance(stream::input_sptr psMusic) const;
		virtual MusicPtr read(stream::input_sptr input, SuppData& suppData) const;
		virtual void write(stream::output_sptr output, SuppData& suppData,
			MusicPtr music, unsigned int flags) const;
		virtual SuppFilenames getRequiredSupps(stream::input_sptr input,
			const std::string& filenameMusic) const;
		virtual Metadata::MetadataTypes getMetadataList() const;

	protected:
		unsigned int tempo;
};

/// MusicType implementation for DMX MUS files from Raptor (different tempo)
class MusicType_MUS_Raptor: virtual public MusicType_MUS
{
	public:
		MusicType_MUS_Raptor();
		virtual std::string getCode() const;
		virtual std::string getFriendlyName() const;
};

} // namespace gamemusic
} // namespace camoto

#endif // _CAMOTO_GAMEMUSIC_MUS_MUS_DMX_HPP_
