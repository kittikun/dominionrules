//// Copyright(C) 2014 kittikun
////
//// This program is free software : you can redistribute it and / or modify
//// it under the terms of the GNU General Public License as published by
//// the Free Software Foundation, either version 3 of the License, or
//// (at your option) any later version.
////
//// This program is distributed in the hope that it will be useful,
//// but WITHOUT ANY WARRANTY; without even the implied warranty of
//// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//// GNU General Public License for more details.
////
//// You should have received a copy of the GNU General Public License
//// along with this program.If not, see <http://www.gnu.org/licenses/>.
//
//#include <boost/test/unit_test.hpp>
//#include <memory>
//#include <iostream>
//#include <fstream>
//#include <cereal/archives/json.hpp>
//
//#include <dominion/character/perk.h>
//
//#include "../testFramework.h"
//
//struct PerkFixture : public BaseFixture < PerkFixture, std::chrono::milliseconds > {
//	PerkFixture() :
//		BaseFixture("Dominion_Perk.csv", { "PerkSerialize, PerkDeserialize" })
//	{
//	}
//};
//
//BOOST_FIXTURE_TEST_SUITE(Dominion_Perk, PerkFixture)
//
//BOOST_AUTO_TEST_CASE(PerkSerialize)
//{
//	TestFunc(50, [&] {
//		Dominion::Perk perk1;
//		Dominion::Perk perk2;
//
//		perk1.set_type(Dominion::EPerkType::Skill);
//		perk1.set_roll(1);
//		perk1.set_usable_races("011110");
//
//		perk2.set_type(Dominion::EPerkType::Passive);
//		perk2.set_roll(12);
//		perk2.set_usable_races("100000");
//
//		std::ofstream ofs("perk.txt");
//		cereal::JSONOutputArchive oarchive(ofs);
//
//		oarchive(CEREAL_NVP(perk1), CEREAL_NVP(perk2));
//	});
//}
//
//BOOST_AUTO_TEST_CASE(PerkDeserialize)
//{
//	TestFunc(50, [&] {
//		Dominion::Perk perk1;
//		Dominion::Perk perk2;
//
//		std::ifstream ifs("perk.txt");
//		cereal::JSONInputArchive iarchive(ifs);
//
//		iarchive(CEREAL_NVP(perk1), CEREAL_NVP(perk2));
//
//		BOOST_CHECK(!perk1.guid().is_nil());
//		BOOST_CHECK(perk1.type() == Dominion::EPerkType::Skill);
//		BOOST_CHECK(perk1.roll() == 1);
//		BOOST_CHECK(!perk1.isRaceUsable(Dominion::ERace::Beast));
//		BOOST_CHECK(perk1.isRaceUsable(Dominion::ERace::Dwarf));
//		BOOST_CHECK(perk1.isRaceUsable(Dominion::ERace::Elf));
//		BOOST_CHECK(perk1.isRaceUsable(Dominion::ERace::Halfling));
//		BOOST_CHECK(perk1.isRaceUsable(Dominion::ERace::Human));
//		BOOST_CHECK(!perk1.isRaceUsable(Dominion::ERace::Humanoid));
//
//		BOOST_CHECK(!perk2.guid().is_nil());
//		BOOST_CHECK(perk2.type() == Dominion::EPerkType::Passive);
//		BOOST_CHECK(perk2.roll() == 12);
//		BOOST_CHECK(!perk2.isRaceUsable(Dominion::ERace::Beast));
//		BOOST_CHECK(!perk2.isRaceUsable(Dominion::ERace::Dwarf));
//		BOOST_CHECK(!perk2.isRaceUsable(Dominion::ERace::Elf));
//		BOOST_CHECK(!perk2.isRaceUsable(Dominion::ERace::Halfling));
//		BOOST_CHECK(!perk2.isRaceUsable(Dominion::ERace::Human));
//		BOOST_CHECK(perk2.isRaceUsable(Dominion::ERace::Humanoid));
//	});
//}
//
//BOOST_AUTO_TEST_SUITE_END()
