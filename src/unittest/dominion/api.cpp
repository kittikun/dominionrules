// Copyright(C) 2014 kittikun
//
// This program is free software : you can redistribute it and / or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.If not, see <http://www.gnu.org/licenses/>.

#include <boost/test/unit_test.hpp>

#include <memory>
#include <chrono>

#if defined(_WIN32)
#include <windows.h>
#endif

#include <dominion/api.h>

#include <minicsv/minicsv.h>

class ApiSetup  {
public:
	ApiSetup()
	{
		csv::ofstream os("Dominion_Api.csv", std::ios_base::app);

		os.set_delimiter(',');
		os << "Initialise" << NEWLINE;

		auto t1 = std::chrono::high_resolution_clock::now();

#if defined(_WIN32)
		if (IsDebuggerPresent())
			Dominion::Initialise("../../data");
#else
		Dominion::Initialise("./data");
#endif
		auto t2 = std::chrono::high_resolution_clock::now();

		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

		os << elapsed << NEWLINE;

		os.close();
	}

	~ApiSetup()
	{}
};

BOOST_GLOBAL_FIXTURE(ApiSetup);