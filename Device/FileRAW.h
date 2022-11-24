/*
	Copyright(c) 2021-2022 jvde.github@gmail.com

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include "Device.h"

namespace Device {

	class RAWFile : public Device {
		std::istream* file = NULL;

		std::string filename;
		std::vector<char> buffer;

		std::thread read_thread;
		std::thread run_thread;

		bool eoi = false;
		bool done = false;

		FIFO fifo;

		static const uint32_t BUFFER_SIZE = 16 * 16384;
		uint32_t BUFFER_COUNT = 2;
		Format format = Format::CU8;

		void ReadAsync();
		void Run();

	public:
		// Control
		void Open(uint64_t);
		void Close();
		void Play();
		void Stop();

		bool isCallback() { return true; }
		bool isStreaming() { return Device::isStreaming() && !done; }

		// Device specific
		void setFormat(Format f) { format = f; }
		Format getFormat() { return format; }

		// Settings
		void Set(std::string option, std::string arg);
		std::string Get();
		std::string getProduct() { return "FILE-RAW"; }
	};
}
