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
//#include <dominion/character/skill.h>
//
//#include "../testFramework.h"
//
//struct SkillFixture : public BaseFixture < SkillFixture, std::chrono::milliseconds > {
//	SkillFixture() :
//		BaseFixture("Dominion_Skill.csv", { "SkillSerialize, SkillDeserialize" })
//	{
//	}
//};
//
//BOOST_FIXTURE_TEST_SUITE(Dominion_Skill, SkillFixture)
//
//BOOST_AUTO_TEST_CASE(SkillSerialize)
//{
//	TestFunc(50, [&] {
//		Dominion::Skill skill1;
//		Dominion::Skill skill2;
//		Dominion::Skill skill3;
//
//		skill1.set_attribute(Dominion::EAttribute::Vigour);
//		skill1.set_name("Climbing");
//		skill2.set_attribute(Dominion::EAttribute::Vigour);
//		skill2.set_name("Grip");
//		skill3.set_attribute(Dominion::EAttribute::Vigour);
//		skill3.set_name("Muscle");
//
//		std::ofstream ofs("Skill.txt");
//		cereal::JSONOutputArchive oarchive(ofs);
//
//		oarchive(CEREAL_NVP(skill1), CEREAL_NVP(skill2), CEREAL_NVP(skill3));
//	});
//}
//
//BOOST_AUTO_TEST_CASE(SkillDeserialize)
//{
//	TestFunc(50, [&] {
//		Dominion::Skill skill1;
//		Dominion::Skill skill2;
//		Dominion::Skill skill3;
//
//		std::ifstream ifs("Skill.txt");
//		cereal::JSONInputArchive iarchive(ifs);
//
//		iarchive(CEREAL_NVP(skill1), CEREAL_NVP(skill2), CEREAL_NVP(skill3));
//
//		BOOST_CHECK(skill1.attribute() == Dominion::EAttribute::Vigour);
//		BOOST_CHECK(skill2.attribute() == Dominion::EAttribute::Vigour);
//		BOOST_CHECK(skill3.attribute() == Dominion::EAttribute::Vigour);
//		BOOST_CHECK(skill1.name() == "Climbing");
//		BOOST_CHECK(skill2.name() == "Grip");
//		BOOST_CHECK(skill3.name() == "Muscle");
//		BOOST_CHECK(!skill1.guid().is_nil());
//		BOOST_CHECK(!skill2.guid().is_nil());
//		BOOST_CHECK(!skill3.guid().is_nil());
//	});
//}
//
//BOOST_AUTO_TEST_SUITE_END()
