/**
 * @file  mus-dro-dosbox-v2.hpp
 * @brief Support for the second version of the DOSBox Raw OPL .DRO format.
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

#ifndef _CAMOTO_GAMEMUSIC_MUS_DRO_DOSBOX_V2_HPP_
#define _CAMOTO_GAMEMUSIC_MUS_DRO_DOSBOX_V2_HPP_

#include <camoto/gamemusic/musictype.hpp>

namespace camoto {
namespace gamemusic {

/// MusicType implementation for DOSBox .dro version 2.
class MusicType_DRO_v2: virtual public MusicType
{
	public:
		virtual std::string code() const;
		virtual std::string friendlyName() const;
		virtual std::vector<std::string> fileExtensions() const;
		virtual Caps caps() const;
		virtual Certainty isInstance(stream::input& content) const;
		virtual std::unique_ptr<Music> read(stream::input& content, SuppData& suppData) const;
		virtual void write(stream::output& content, SuppData& suppData,
			const Music& music, WriteFlags flags) const;
		virtual SuppFilenames getRequiredSupps(stream::input& content,
			const std::string& filename) const;
		virtual std::vector<Attribute> supportedAttributes() const;
};

} // namespace gamemusic
} // namespace camoto

#endif // _CAMOTO_GAMEMUSIC_MUS_DRO_DOSBOX_V2_HPP_
