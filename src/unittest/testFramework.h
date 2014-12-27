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

#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <chrono>
#include <iterator>
#include <numeric>
#include <array>

#include <minicsv/minicsv.h>

template <typename Derived, typename TimePrecision>
struct BaseFixture {
	explicit BaseFixture(std::string filename, std::vector<std::string> testNames) :
		os(filename.c_str(), std::ios_base::app)
	{
		static bool initalized = false;

		os.set_delimiter(',');

		if (!initalized && os.is_open()) {
			for (auto& str : testNames) {
				os << str;
			}

			os << NEWLINE;
			initalized = true;
		}
	}

	~BaseFixture() {}

	template<typename F>
	void TestFunc(int times, F lambda)
	{
		std::array<typename TimePrecision::rep, 10> time;

		for (int i = 0; i < 10; ++i) {
			auto t1 = std::chrono::high_resolution_clock::now();

			for (int j = 0; j < times; ++j) {
				lambda();
			}

			auto t2 = std::chrono::high_resolution_clock::now();

			time[i] = std::chrono::duration_cast<TimePrecision>(t2 - t1).count();
		}

		typename TimePrecision::rep avg = std::accumulate(begin(time), end(time), (typename TimePrecision::rep)0) / (typename TimePrecision::rep)time.size();

		if (os.is_open()) {
			os << avg << "";
		}
	}

	csv::ofstream os;
};

#endif // TEST_FRAMEWORK_H
