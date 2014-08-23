/**
 * @file   test-mus-dsm-dsik.cpp
 * @brief  Test code for Digital Sound Interface Kit DSM modules.
 *
 * Copyright (C) 2010-2014 Adam Nielsen <malvineous@shikadi.net>
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

#include "test-music.hpp"

class test_dsm_dsik: public test_music
{
	public:
		test_dsm_dsik()
		{
			this->type = "dsm-dsik";
			this->outputWidth = 0x10;
			this->numInstruments = 1;
			this->indexInstrumentOPL = -1;
			this->indexInstrumentMIDI = -1;
			this->indexInstrumentPCM = 0;
		}

		void addTests()
		{
			this->test_music::addTests();

			// c00: Normal
			this->isInstance(MusicType::DefinitelyYes, this->standard());

			// c01: Invalid RIFF
			this->isInstance(MusicType::DefinitelyNo, STRING_WITH_NULLS(
				"RUFF" "\x7A\x01\x00\x00" "DSMF"
				"SONG" "\xC0\x00\x00\x00"
				"Test DSM song\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
				"\x00\x00" "\x00\x00" "\x00\x00\x00\x00"
				"\x02\x00" "\x01\x00" "\x01\x00" "\x10\x00"
				"\x3F" "\x3F" "\x06" "\x7D"
				"\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80"
				"\x00\x00\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"INST" "\x50\x00\x00\x00"
				"\0\0\0\0\0\0\0\0\0\0\0\0\0"
				"\x01\x00" "\x3F"
				"\x10\x00\x00\x00" "\x00\x00\x00\x00" "\x10\x00\x00\x00"
				"\x00\x00\x00\x00" "\xAB\x20" "\xAC\x01"
				"PCM instrument 1\0\0\0\0\0\0\0\0\0\0\0\0"
				// PCM inst 1 sample data
				"\x00\x10\x00\xF0\x00\x10\x00\xF0\x00\x10\x00\xF0\x00\x10\x00\xF0"
				"PATT" "\x4E\x00\x00\x00" "\x4E\x00"
				"\xC0\x30\x01\x00\x00\xC0\x31\x01\x00\x10\x0F\x04\x11\x0F\x74\x00"
				"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
			));

			// c02: Invalid DSMF signature
			this->isInstance(MusicType::DefinitelyNo, STRING_WITH_NULLS(
				"RIFF" "\x7A\x01\x00\x00" "DSFM"
				"SONG" "\xC0\x00\x00\x00"
				"Test DSM song\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
				"\x00\x00" "\x00\x00" "\x00\x00\x00\x00"
				"\x02\x00" "\x01\x00" "\x01\x00" "\x10\x00"
				"\x3F" "\x3F" "\x06" "\x7D"
				"\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80"
				"\x00\x00\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"INST" "\x50\x00\x00\x00"
				"\0\0\0\0\0\0\0\0\0\0\0\0\0"
				"\x01\x00" "\x3F"
				"\x10\x00\x00\x00" "\x00\x00\x00\x00" "\x10\x00\x00\x00"
				"\x00\x00\x00\x00" "\xAB\x20" "\xAC\x01"
				"PCM instrument 1\0\0\0\0\0\0\0\0\0\0\0\0"
				// PCM inst 1 sample data
				"\x00\x10\x00\xF0\x00\x10\x00\xF0\x00\x10\x00\xF0\x00\x10\x00\xF0"
				"PATT" "\x4E\x00\x00\x00" "\x4E\x00"
				"\xC0\x30\x01\x00\x00\xC0\x31\x01\x00\x10\x0F\x04\x11\x0F\x74\x00"
				"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
			));

			// c03: File truncated
			this->isInstance(MusicType::DefinitelyNo, STRING_WITH_NULLS(
				"RIFF" "\x7A\x02\x00\x00" "DSMF"
				"SONG" "\xC0\x00\x00\x00"
				"Test DSM song\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
				"\x00\x00" "\x00\x00" "\x00\x00\x00\x00"
				"\x02\x00" "\x01\x00" "\x01\x00" "\x10\x00"
				"\x3F" "\x3F" "\x06" "\x7D"
				"\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80"
				"\x00\x00\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"INST" "\x50\x00\x00\x00"
				"\0\0\0\0\0\0\0\0\0\0\0\0\0"
				"\x01\x00" "\x3F"
				"\x10\x00\x00\x00" "\x00\x00\x00\x00" "\x10\x00\x00\x00"
				"\x00\x00\x00\x00" "\xAB\x20" "\xAC\x01"
				"PCM instrument 1\0\0\0\0\0\0\0\0\0\0\0\0"
				// PCM inst 1 sample data
				"\x00\x10\x00\xF0\x00\x10\x00\xF0\x00\x10\x00\xF0\x00\x10\x00\xF0"
				"PATT" "\x4E\x00\x00\x00" "\x4E\x00"
				"\xC0\x30\x01\x00\x00\xC0\x31\x01\x00\x10\x0F\x04\x11\x0F\x74\x00"
				"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
			));
		}

		virtual std::string standard()
		{
			return STRING_WITH_NULLS(
				"RIFF" "\x7A\x01\x00\x00" "DSMF"
				"SONG" "\xC0\x00\x00\x00"
				"Test DSM song\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
				"\x00\x00" "\x00\x00" "\x00\x00\x00\x00"
				"\x02\x00" "\x01\x00" "\x01\x00" "\x10\x00"
				"\x3F" "\x3F" "\x06" "\x7D"
				"\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80"
				"\x00\x00\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
				"INST" "\x50\x00\x00\x00"
				"\0\0\0\0\0\0\0\0\0\0\0\0\0"
				"\x01\x00" "\x3F"
				"\x10\x00\x00\x00" "\x00\x00\x00\x00" "\x10\x00\x00\x00"
				"\x00\x00\x00\x00" "\xAB\x20" "\xAC\x01"
				"PCM instrument 1\0\0\0\0\0\0\0\0\0\0\0\0"
				// PCM inst 1 sample data
				"\x00\x10\x00\xF0\x00\x10\x00\xF0\x00\x10\x00\xF0\x00\x10\x00\xF0"
				"PATT" "\x4E\x00\x00\x00" "\x4E\x00"
				"\xC0\x30\x01\x00\x00\xC0\x31\x01\x00\x10\x0F\x04\x11\x0F\x73\x00"
				"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
			);
		}
};

IMPLEMENT_TESTS(dsm_dsik);
