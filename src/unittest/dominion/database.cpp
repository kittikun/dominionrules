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

#include <dominion/api.h>
#include <dominion/core/database.h>

#include "../testFramework.h"

struct DatabaseFixture : public BaseFixture < DatabaseFixture, std::chrono::milliseconds > {
	DatabaseFixture() :
		BaseFixture("Dominion_Database.csv", { "GetStyles" }),
		db_(Dominion::GetDatabase())
	{}

	std::shared_ptr<Dominion::DataBase> db_;
};

BOOST_FIXTURE_TEST_SUITE(Dominion_Database, DatabaseFixture)

BOOST_AUTO_TEST_CASE(GetStyles)
{
	TestFunc(1000, [&] {
		db_->GetStyles();
	});
}

BOOST_AUTO_TEST_SUITE_END()