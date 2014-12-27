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

#include <chrono>
#include <random>
#include <vector>
#include <dominion/api.h>
#include <dominion/core/database.h>
#include <dominion/core/dice.h>
#include <dominion/core/definitions.h>
#include <dominion/character/character.h>
#include <dominion/character/character_utility.h>
#include <dominion/character/style.h>

#include "../testFramework.h"

struct CharacterFixture : public BaseFixture < CharacterFixture, std::chrono::milliseconds > {
	CharacterFixture() :
		BaseFixture{ "Dominion_Character.csv", { "CreateHumanSoldier", "CreateElfWitch", "CreateDwarfPriest" } }
	{
		std::random_device rd;

		rng_ = std::mt19937{ rd() };
		db_ = Dominion::GetDatabase();
	}

	std::mt19937 rng_;
	std::shared_ptr<Dominion::DataBase> db_;
};

BOOST_FIXTURE_TEST_SUITE(Dominion_Character, CharacterFixture)

BOOST_AUTO_TEST_CASE(Validation)
{
	auto dice = std::make_shared<Dominion::Dice>();
	auto cTool = Dominion::GetCharacterCreationTool();

	// race should be set to 0 by default
	BOOST_CHECK(cTool->Validate() == Dominion::ECharacterValidationResult::InvalidRace);
	cTool->race(Dominion::RaceCount);
	BOOST_CHECK(cTool->Validate() == Dominion::ECharacterValidationResult::InvalidRace);
	cTool->race(Dominion::RaceHuman);

	// next style is verified
	BOOST_CHECK(cTool->Validate() == Dominion::ECharacterValidationResult::MissingStyle);
	auto styles = db_->GetStyles();
	cTool->style(styles[std::uniform_int_distribution < size_t > { 0, styles.size() - 1 }(rng_)]);

	// next perk roll is verified
	BOOST_CHECK(cTool->Validate() == Dominion::ECharacterValidationResult::InvalidPerk);
	cTool->perk(13);
	BOOST_CHECK(cTool->Validate() == Dominion::ECharacterValidationResult::InvalidPerk);
	cTool->perk(dice->Roll());

	// next attributes are checked
	BOOST_CHECK(cTool->Validate() == Dominion::ECharacterValidationResult::MissingAttributeRoll);
	cTool->attributesRoll(dice);
	BOOST_CHECK(cTool->Validate() == Dominion::ECharacterValidationResult::MissingAttributes);
	Dominion::AttributeArray attr;
	attr.fill(0);
	cTool->attributes(attr);
	BOOST_CHECK(cTool->Validate() == Dominion::ECharacterValidationResult::InvalidAttributes);
	attr.fill(99);
	BOOST_CHECK(cTool->Validate() == Dominion::ECharacterValidationResult::InvalidAttributes);
}

BOOST_AUTO_TEST_CASE(CreateHumanSoldier)
{
	auto dice = std::make_shared<Dominion::Dice>();

	TestFunc(1000, [&] {
		auto cTool = Dominion::GetCharacterCreationTool();

		auto styles = db_->GetStyles();
		auto attributes = cTool->attributesBase();
		auto apr = cTool->attributesRoll(dice);

		int i, j;
		for (i = 0, j = 0; i < std::get<0>(*apr); ++j) {
			if (dice->Roll() % 2 == 1) {
				attributes[j % Dominion::AttributeCount] += 1;
				++i;
			}
		}

		cTool->attributes(attributes);
		cTool->race(Dominion::RaceHuman);
		cTool->style(styles[7]);
		cTool->perk(dice->Roll());

		while (cTool->Validate() == Dominion::ECharacterValidationResult::RerollPerk) {
			cTool->perk(dice->Roll());
		}

		auto npc = cTool->MakeCharacter();

		BOOST_CHECK(npc);
	});
}

BOOST_AUTO_TEST_CASE(CreateElfWitch)
{
	auto dice = std::make_shared<Dominion::Dice>();

	TestFunc(1000, [&] {
		auto cTool = Dominion::GetCharacterCreationTool();

		auto styles = db_->GetStyles();
		auto attributes = cTool->attributesBase();
		auto apr = cTool->attributesRoll(dice);

		int i, j;
		for (i = 0, j = 0; i < std::get<0>(*apr); ++j) {
			if (dice->Roll() % 2 == 1) {
				attributes[j % Dominion::AttributeCount] += 1;
				++i;
			}
		}

		cTool->attributes(attributes);
		cTool->race(Dominion::RaceElf);
		cTool->style(styles[8]);
		cTool->perk(dice->Roll());

		while (cTool->Validate() == Dominion::ECharacterValidationResult::RerollPerk) {
			cTool->perk(dice->Roll());
		}

		auto npc = cTool->MakeCharacter();

		BOOST_CHECK(npc);
	});
}

BOOST_AUTO_TEST_CASE(CreateDwarfPriest)
{
	auto dice = std::make_shared<Dominion::Dice>();

	TestFunc(1000, [&] {
		auto cTool = Dominion::GetCharacterCreationTool();

		auto styles = db_->GetStyles();
		auto attributes = cTool->attributesBase();
		auto apr = cTool->attributesRoll(dice);

		int i, j;
		for (i = 0, j = 0; i < std::get<0>(*apr); ++j) {
			if (dice->Roll() % 2 == 1) {
				attributes[j % Dominion::AttributeCount] += 1;
				++i;
			}
		}

		cTool->attributes(attributes);
		cTool->race(Dominion::RaceDwarf);
		cTool->style(styles[4]);
		cTool->perk(dice->Roll());

		while (cTool->Validate() == Dominion::ECharacterValidationResult::RerollPerk) {
			cTool->perk(dice->Roll());
		}

		auto npc = cTool->MakeCharacter();

		BOOST_CHECK(npc);
	});
}

BOOST_AUTO_TEST_SUITE_END()