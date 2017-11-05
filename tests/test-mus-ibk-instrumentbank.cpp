/**
 * @file   test-mus-ibk-instrumentbank.cpp
 * @brief  Test code for IBK instrument banks.
 *
 * Copyright (C) 2010-2017 Adam Nielsen <malvineous@shikadi.net>
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
#include "../src/mus-ibk-instrumentbank.hpp"

class test_ibk_instrumentbank: public test_music
{
	public:
		test_ibk_instrumentbank()
		{
			this->type = "ibk-instrumentbank";
			this->outputWidth = 0x10;
			this->numInstruments = 128;
			this->indexInstrumentOPL = 0;
			this->indexInstrumentMIDI = -1;
			this->indexInstrumentPCM = -1;
		}

		void addTests()
		{
			this->test_music::addTests();

			// c00: Normal
			this->isInstance(MusicType::Certainty::DefinitelyYes, this->standard());

			// c01: File too small
			this->isInstance(MusicType::Certainty::DefinitelyNo, STRING_WITH_NULLS(
				"IBK"
			));
		}

		virtual std::string standard()
		{
			return STRING_WITH_NULLS(
				"IBK\x1A"
				"\xFF\x0E\xFF\xBE\xFF\xEE\xFF\xEE\x07\x06\x0F" "\x00\x00\x00\x00\x00"
				//"\x21\x21\x8F\x06\xF2\xF2\x45\x76\x00\x00\x08\x00\x00\x00\x00\x00"
				"\x31\x21\x4B\x00\xF2\xF2\x54\x56\x00\x00\x08\x00\x00\x00\x00\x00"
				"\x31\x21\x49\x00\xF2\xF2\x55\x76\x00\x00\x08\x00\x00\x00\x00\x00"
				"\xB1\x61\x0E\x00\xF2\xF3\x3B\x0B\x00\x00\x06\x00\x00\x00\x00\x00"
				"\x01\x21\x57\x00\xF1\xF1\x38\x28\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x01\x21\x93\x00\xF1\xF1\x38\x28\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x21\x36\x80\x0E\xA2\xF1\x01\xD5\x00\x00\x08\x00\x00\x00\x00\x00"
				"\x01\x01\x92\x00\xC2\xC2\xA8\x58\x00\x00\x0A\x00\x00\x00\x00\x00"
				"\x0C\x81\x5C\x00\xF6\xF3\x54\xB5\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x07\x11\x97\x80\xF6\xF5\x32\x11\x00\x00\x02\x00\x00\x00\x00\x00"
				"\x17\x01\x21\x00\x56\xF6\x04\x04\x00\x00\x02\x00\x00\x00\x00\x00"
				"\x18\x81\x62\x00\xF3\xF2\xE6\xF6\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x18\x21\x23\x00\xF7\xE5\x55\xD8\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x15\x01\x91\x00\xF6\xF6\xA6\xE6\x00\x00\x04\x00\x00\x00\x00\x00"
				"\x45\x81\x59\x80\xD3\xA3\x82\xE3\x00\x00\x0C\x00\x00\x00\x00\x00"
				"\x03\x81\x49\x80\x74\xB3\x55\x05\x01\x00\x04\x00\x00\x00\x00\x00"
				"\x71\x31\x92\x00\xF6\xF1\x14\x07\x00\x00\x02\x00\x00\x00\x00\x00"
				"\x72\x30\x14\x00\xC7\xC7\x58\x08\x00\x00\x02\x00\x00\x00\x00\x00"
				"\x70\xB1\x44\x00\xAA\x8A\x18\x08\x00\x00\x04\x00\x00\x00\x00\x00"
				"\x23\xB1\x93\x00\x97\x55\x23\x14\x01\x00\x04\x00\x00\x00\x00\x00"
				"\x61\xB1\x13\x80\x97\x55\x04\x04\x01\x00\x00\x00\x00\x00\x00\x00"
				"\x24\xB1\x48\x00\x98\x46\x2A\x1A\x01\x00\x0C\x00\x00\x00\x00\x00"
				"\x61\x21\x13\x00\x91\x61\x06\x07\x01\x00\x0A\x00\x00\x00\x00\x00"
				"\x21\xA1\x13\x89\x71\x61\x06\x07\x00\x00\x06\x00\x00\x00\x00\x00"
				"\x02\x41\x9C\x80\xF3\xF3\x94\xC8\x01\x00\x0C\x00\x00\x00\x00\x00"
				"\x03\x11\x54\x00\xF3\xF1\x9A\xE7\x01\x00\x0C\x00\x00\x00\x00\x00"
				"\x23\x21\x5F\x00\xF1\xF2\x3A\xF8\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x03\x21\x87\x80\xF6\xF3\x22\xF3\x01\x00\x06\x00\x00\x00\x00\x00"
				"\x03\x21\x47\x00\xF9\xF6\x54\x3A\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x23\x21\x48\x00\x95\x84\x19\x19\x01\x00\x08\x00\x00\x00\x00\x00"
				"\x23\x21\x4A\x00\x95\x94\x19\x19\x01\x00\x08\x00\x00\x00\x00\x00"
				"\x09\x84\xA1\x80\x20\xD1\x4F\xF8\x00\x00\x08\x00\x00\x00\x00\x00"
				"\x21\xA2\x1E\x00\x94\xC3\x06\xA6\x00\x00\x02\x00\x00\x00\x00\x00"
				"\x31\x31\x12\x00\xF1\xF1\x28\x18\x00\x00\x0A\x00\x00\x00\x00\x00"
				"\x31\x31\x8D\x00\xF1\xF1\xE8\x78\x00\x00\x0A\x00\x00\x00\x00\x00"
				"\x31\x32\x5B\x00\x51\x71\x28\x48\x00\x00\x0C\x00\x00\x00\x00\x00"
				"\x01\x21\x8B\x40\xA1\xF2\x9A\xDF\x00\x00\x08\x00\x00\x00\x00\x00"
				"\x01\x21\x89\x40\xA1\xF2\x9A\xDF\x00\x00\x08\x00\x00\x00\x00\x00"
				"\x31\x31\x8B\x00\xF4\xF1\xE8\x78\x00\x00\x0A\x00\x00\x00\x00\x00"
				"\x31\x31\x12\x00\xF1\xF1\x28\x18\x00\x00\x0A\x00\x00\x00\x00\x00"
				"\x31\x21\x15\x00\xDD\x56\x13\x26\x01\x00\x08\x00\x00\x00\x00\x00"
				"\x31\x21\x16\x00\xDD\x66\x13\x06\x01\x00\x08\x00\x00\x00\x00\x00"
				"\x71\x31\x49\x00\xD1\x61\x1C\x0C\x01\x00\x08\x00\x00\x00\x00\x00"
				"\x21\x23\x4D\x80\x71\x72\x12\x06\x01\x00\x02\x00\x00\x00\x00\x00"
				"\xF1\xE1\x40\x00\xF1\x6F\x21\x16\x01\x00\x02\x00\x00\x00\x00\x00"
				"\x02\x01\x1A\x80\xF5\x85\x75\x35\x01\x00\x00\x00\x00\x00\x00\x00"
				"\x02\x01\x1D\x80\xF5\xF3\x75\xF4\x01\x00\x00\x00\x00\x00\x00\x00"
				"\x10\x11\x41\x00\xF5\xF2\x05\xC3\x01\x00\x02\x00\x00\x00\x00\x00"
				"\x21\xA2\x9B\x01\xB1\x72\x25\x08\x01\x00\x0E\x00\x00\x00\x00\x00"
				"\xA1\x21\x98\x00\x7F\x3F\x03\x07\x01\x01\x00\x00\x00\x00\x00\x00"
				"\xA1\x61\x93\x00\xC1\x4F\x12\x05\x00\x00\x0A\x00\x00\x00\x00\x00"
				"\x21\x61\x18\x00\xC1\x4F\x22\x05\x00\x00\x0C\x00\x00\x00\x00\x00"
				"\x31\x72\x5B\x83\xF4\x8A\x15\x05\x00\x00\x00\x00\x00\x00\x00\x00"
				"\xA1\x61\x90\x00\x74\x71\x39\x67\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x71\x72\x57\x00\x54\x7A\x05\x05\x00\x00\x0C\x00\x00\x00\x00\x00"
				"\x90\x41\x00\x00\x54\xA5\x63\x45\x00\x00\x08\x00\x00\x00\x00\x00"
				"\x21\x21\x92\x01\x85\x8F\x17\x09\x00\x00\x0C\x00\x00\x00\x00\x00"
				"\x21\x21\x94\x05\x75\x8F\x17\x09\x00\x00\x0C\x00\x00\x00\x00\x00"
				"\x21\x61\x94\x00\x76\x82\x15\x37\x00\x00\x0C\x00\x00\x00\x00\x00"
				"\x31\x21\x43\x00\x9E\x62\x17\x2C\x01\x01\x02\x00\x00\x00\x00\x00"
				"\x21\x21\x9B\x00\x61\x7F\x6A\x0A\x00\x00\x02\x00\x00\x00\x00\x00"
				"\x61\x22\x8A\x06\x75\x74\x1F\x0F\x00\x00\x08\x00\x00\x00\x00\x00"
				"\xA1\x21\x86\x0D\x72\x71\x55\x18\x01\x00\x00\x00\x00\x00\x00\x00"
				"\x21\x21\x4D\x00\x54\xA6\x3C\x1C\x00\x00\x08\x00\x00\x00\x00\x00"
				"\x31\x61\x8F\x00\x93\x72\x02\x0B\x01\x00\x08\x00\x00\x00\x00\x00"
				"\x31\x61\x8E\x00\x93\x72\x03\x09\x01\x00\x08\x00\x00\x00\x00\x00"
				"\x31\x61\x91\x00\x93\x82\x03\x09\x01\x00\x0A\x00\x00\x00\x00\x00"
				"\x31\x61\x8E\x00\x93\x72\x0F\x0F\x01\x00\x0A\x00\x00\x00\x00\x00"
				"\x21\x21\x4B\x00\xAA\x8F\x16\x0A\x01\x00\x08\x00\x00\x00\x00\x00"
				"\x31\x21\x90\x00\x7E\x8B\x17\x0C\x01\x01\x06\x00\x00\x00\x00\x00"
				"\x31\x32\x81\x00\x75\x61\x19\x19\x01\x00\x00\x00\x00\x00\x00\x00"
				"\x32\x21\x90\x00\x9B\x72\x21\x17\x00\x00\x04\x00\x00\x00\x00\x00"
				"\xE1\xE1\x1F\x00\x85\x65\x5F\x1A\x00\x00\x00\x00\x00\x00\x00\x00"
				"\xE1\xE1\x46\x00\x88\x65\x5F\x1A\x00\x00\x00\x00\x00\x00\x00\x00"
				"\xA1\x21\x9C\x00\x75\x75\x1F\x0A\x00\x00\x02\x00\x00\x00\x00\x00"
				"\x31\x21\x8B\x00\x84\x65\x58\x1A\x00\x00\x00\x00\x00\x00\x00\x00"
				"\xE1\xA1\x4C\x00\x66\x65\x56\x26\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x62\xA1\xCB\x00\x76\x55\x46\x36\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x62\xA1\x99\x00\x57\x56\x07\x07\x00\x00\x0B\x00\x00\x00\x00\x00"
				"\x62\xA1\x93\x00\x77\x76\x07\x07\x00\x00\x0B\x00\x00\x00\x00\x00"
				"\x22\x21\x59\x00\xFF\xFF\x03\x0F\x02\x00\x00\x00\x00\x00\x00\x00"
				"\x21\x21\x0E\x00\xFF\xFF\x0F\x0F\x01\x01\x00\x00\x00\x00\x00\x00"
				"\x22\x21\x46\x80\x86\x64\x55\x18\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x21\xA1\x45\x00\x66\x96\x12\x0A\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x21\x22\x8B\x00\x92\x91\x2A\x2A\x01\x00\x00\x00\x00\x00\x00\x00"
				"\xA2\x61\x9E\x40\xDF\x6F\x05\x07\x00\x00\x02\x00\x00\x00\x00\x00"
				"\x20\x60\x1A\x00\xEF\x8F\x01\x06\x00\x02\x00\x00\x00\x00\x00\x00"
				"\x21\x21\x8F\x80\xF1\xF4\x29\x09\x00\x00\x0A\x00\x00\x00\x00\x00"
				"\x77\xA1\xA5\x00\x53\xA0\x94\x05\x00\x00\x02\x00\x00\x00\x00\x00"
				"\x61\xB1\x1F\x80\xA8\x25\x11\x03\x00\x00\x0A\x00\x00\x00\x00\x00"
				"\x61\x61\x17\x00\x91\x55\x34\x16\x00\x00\x0C\x00\x00\x00\x00\x00"
				"\x71\x72\x5D\x00\x54\x6A\x01\x03\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x21\xA2\x97\x00\x21\x42\x43\x35\x00\x00\x08\x00\x00\x00\x00\x00"
				"\xA1\x21\x1C\x00\xA1\x31\x77\x47\x01\x01\x00\x00\x00\x00\x00\x00"
				"\x21\x61\x89\x03\x11\x42\x33\x25\x00\x00\x0A\x00\x00\x00\x00\x00"
				"\xA1\x21\x15\x00\x11\xCF\x47\x07\x01\x00\x00\x00\x00\x00\x00\x00"
				"\x3A\x51\xCE\x00\xF8\x86\xF6\x02\x00\x00\x02\x00\x00\x00\x00\x00"
				"\x21\x21\x15\x00\x21\x41\x23\x13\x01\x00\x00\x00\x00\x00\x00\x00"
				"\x06\x01\x5B\x00\x74\xA5\x95\x72\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x22\x61\x92\x83\xB1\xF2\x81\x26\x00\x00\x0C\x00\x00\x00\x00\x00"
				"\x41\x42\x4D\x00\xF1\xF2\x51\xF5\x01\x00\x00\x00\x00\x00\x00\x00"
				"\x61\xA3\x94\x80\x11\x11\x51\x13\x01\x00\x06\x00\x00\x00\x00\x00"
				"\x61\xA1\x8C\x80\x11\x1D\x31\x03\x00\x00\x06\x00\x00\x00\x00\x00"
				"\xA4\x61\x4C\x00\xF3\x81\x73\x23\x01\x00\x04\x00\x00\x00\x00\x00"
				"\x02\x07\x85\x03\xD2\xF2\x53\xF6\x00\x01\x00\x00\x00\x00\x00\x00"
				"\x11\x13\x0C\x80\xA3\xA2\x11\xE5\x01\x00\x00\x00\x00\x00\x00\x00"
				"\x11\x11\x06\x00\xF6\xF2\x41\xE6\x01\x02\x04\x00\x00\x00\x00\x00"
				"\x93\x91\x91\x00\xD4\xEB\x32\x11\x00\x01\x08\x00\x00\x00\x00\x00"
				"\x04\x01\x4F\x00\xFA\xC2\x56\x05\x00\x00\x0C\x00\x00\x00\x00\x00"
				"\x21\x22\x49\x00\x7C\x6F\x20\x0C\x00\x01\x06\x00\x00\x00\x00\x00"
				"\x31\x21\x85\x00\xDD\x56\x33\x16\x01\x00\x0A\x00\x00\x00\x00\x00"
				"\x20\x21\x04\x81\xDA\x8F\x05\x0B\x02\x00\x06\x00\x00\x00\x00\x00"
				"\x05\x03\x6A\x80\xF1\xC3\xE5\xE5\x00\x00\x06\x00\x00\x00\x00\x00"
				"\x07\x02\x15\x00\xEC\xF8\x26\x16\x00\x00\x0A\x00\x00\x00\x00\x00"
				"\x05\x01\x9D\x00\x67\xDF\x35\x05\x00\x00\x08\x00\x00\x00\x00\x00"
				"\x18\x12\x96\x00\xFA\xF8\x28\xE5\x00\x00\x0A\x00\x00\x00\x00\x00"
				"\x10\x00\x86\x03\xA8\xFA\x07\x03\x00\x00\x06\x00\x00\x00\x00\x00"
				"\x11\x10\x41\x03\xF8\xF3\x47\x03\x02\x00\x04\x00\x00\x00\x00\x00"
				"\x01\x10\x8E\x00\xF1\xF3\x06\x02\x02\x00\x0E\x00\x00\x00\x00\x00"
				"\x0E\xC0\x00\x00\x1F\x1F\x00\xFF\x00\x03\x0E\x00\x00\x00\x00\x00"
				"\x06\x03\x80\x88\xF8\x56\x24\x84\x00\x02\x0E\x00\x00\x00\x00\x00"
				"\x0E\xD0\x00\x05\xF8\x34\x00\x04\x00\x03\x0E\x00\x00\x00\x00\x00"
				"\x0E\xC0\x00\x00\xF6\x1F\x00\x02\x00\x03\x0E\x00\x00\x00\x00\x00"
				"\xD5\xDA\x95\x40\x37\x56\xA3\x37\x00\x00\x00\x00\x00\x00\x00\x00"
				"\x35\x14\x5C\x08\xB2\xF4\x61\x15\x02\x00\x0A\x00\x00\x00\x00\x00"
				"\x0E\xD0\x00\x00\xF6\x4F\x00\xF5\x00\x03\x0E\x00\x00\x00\x00\x00"
				"\x26\xE4\x00\x00\xFF\x12\x01\x16\x00\x01\x0E\x00\x00\x00\x00\x00"
				"\x00\x00\x00\x00\xF3\xF6\xF0\xC9\x00\x02\x0E\x00\x00\x00\x00\x00"
				"AM000\x00\x00\x00\x00"
				"AM001\x00\x00\x00\x00"
				"AM002\x00\x00\x00\x00"
				"AM003\x00\x00\x00\x00"
				"AM004\x00\x00\x00\x00"
				"AM005\x00\x00\x00\x00"
				"AM006\x00\x00\x00\x00"
				"AM007\x00\x00\x00\x00"
				"AM008\x00\x00\x00\x00"
				"AM009\x00\x00\x00\x00"
				"AM010\x00\x00\x00\x00"
				"AM011\x00\x00\x00\x00"
				"AM012\x00\x00\x00\x00"
				"AM013\x00\x00\x00\x00"
				"AM014\x00\x00\x00\x00"
				"AM015\x00\x00\x00\x00"
				"AM016\x00\x00\x00\x00"
				"AM017\x00\x00\x00\x00"
				"AM018\x00\x00\x00\x00"
				"AM019\x00\x00\x00\x00"
				"AM020\x00\x00\x00\x00"
				"AM021\x00\x00\x00\x00"
				"AM022\x00\x00\x00\x00"
				"AM023\x00\x00\x00\x00"
				"AM024\x00\x00\x00\x00"
				"AM025\x00\x00\x00\x00"
				"AM026\x00\x00\x00\x00"
				"AM027\x00\x00\x00\x00"
				"AM028\x00\x00\x00\x00"
				"AM029\x00\x00\x00\x00"
				"AM030\x00\x00\x00\x00"
				"AM031\x00\x00\x00\x00"
				"AM032\x00\x00\x00\x00"
				"AM033\x00\x00\x00\x00"
				"AM034\x00\x00\x00\x00"
				"AM035\x00\x00\x00\x00"
				"AM036\x00\x00\x00\x00"
				"AM037\x00\x00\x00\x00"
				"AM038\x00\x00\x00\x00"
				"AM039\x00\x00\x00\x00"
				"AM040\x00\x00\x00\x00"
				"AM041\x00\x00\x00\x00"
				"AM042\x00\x00\x00\x00"
				"AM043\x00\x00\x00\x00"
				"AM044\x00\x00\x00\x00"
				"AM045\x00\x00\x00\x00"
				"AM046\x00\x00\x00\x00"
				"AM047\x00\x00\x00\x00"
				"AM048\x00\x00\x00\x00"
				"AM049\x00\x00\x00\x00"
				"AM050\x00\x00\x00\x00"
				"AM051\x00\x00\x00\x00"
				"AM052\x00\x00\x00\x00"
				"AM053\x00\x00\x00\x00"
				"AM054\x00\x00\x00\x00"
				"AM055\x00\x00\x00\x00"
				"AM056\x00\x00\x00\x00"
				"AM057\x00\x00\x00\x00"
				"AM058\x00\x00\x00\x00"
				"AM059\x00\x00\x00\x00"
				"AM060\x00\x00\x00\x00"
				"AM061\x00\x00\x00\x00"
				"AM062\x00\x00\x00\x00"
				"AM063\x00\x00\x00\x00"
				"AM064\x00\x00\x00\x00"
				"AM065\x00\x00\x00\x00"
				"AM066\x00\x00\x00\x00"
				"AM067\x00\x00\x00\x00"
				"AM068\x00\x00\x00\x00"
				"AM069\x00\x00\x00\x00"
				"AM070\x00\x00\x00\x00"
				"AM071\x00\x00\x00\x00"
				"AM072\x00\x00\x00\x00"
				"AM073\x00\x00\x00\x00"
				"AM074\x00\x00\x00\x00"
				"AM075\x00\x00\x00\x00"
				"AM076\x00\x00\x00\x00"
				"AM077\x00\x00\x00\x00"
				"AM078\x00\x00\x00\x00"
				"AM079\x00\x00\x00\x00"
				"AM080\x00\x00\x00\x00"
				"AM081\x00\x00\x00\x00"
				"AM082\x00\x00\x00\x00"
				"AM083\x00\x00\x00\x00"
				"AM084\x00\x00\x00\x00"
				"AM085\x00\x00\x00\x00"
				"AM086\x00\x00\x00\x00"
				"AM087\x00\x00\x00\x00"
				"AM088\x00\x00\x00\x00"
				"AM089\x00\x00\x00\x00"
				"AM090\x00\x00\x00\x00"
				"AM091\x00\x00\x00\x00"
				"AM092\x00\x00\x00\x00"
				"AM093\x00\x00\x00\x00"
				"AM094\x00\x00\x00\x00"
				"AM095\x00\x00\x00\x00"
				"AM096\x00\x00\x00\x00"
				"AM097\x00\x00\x00\x00"
				"AM098\x00\x00\x00\x00"
				"AM099\x00\x00\x00\x00"
				"AM100\x00\x00\x00\x00"
				"AM101\x00\x00\x00\x00"
				"AM102\x00\x00\x00\x00"
				"AM103\x00\x00\x00\x00"
				"AM104\x00\x00\x00\x00"
				"AM105\x00\x00\x00\x00"
				"AM106\x00\x00\x00\x00"
				"AM107\x00\x00\x00\x00"
				"AM108\x00\x00\x00\x00"
				"AM109\x00\x00\x00\x00"
				"AM110\x00\x00\x00\x00"
				"AM111\x00\x00\x00\x00"
				"AM112\x00\x00\x00\x00"
				"AM113\x00\x00\x00\x00"
				"AM114\x00\x00\x00\x00"
				"AM115\x00\x00\x00\x00"
				"AM116\x00\x00\x00\x00"
				"AM117\x00\x00\x00\x00"
				"AM118\x00\x00\x00\x00"
				"AM119\x00\x00\x00\x00"
				"AM120\x00\x00\x00\x00"
				"AM121\x00\x00\x00\x00"
				"AM122\x00\x00\x00\x00"
				"AM123\x00\x00\x00\x00"
				"AM124\x00\x00\x00\x00"
				"AM125\x00\x00\x00\x00"
				"AM126\x00\x00\x00\x00"
				"AM127\x00\x00\x00\x00"
			);
		}
};

IMPLEMENT_TESTS(ibk_instrumentbank);