// Copyright(C) 2015 kittikun
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sub-license, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// This work is compatible with the Dominion Rules role-playing system.To learn more about
// Dominion Rules, visit the Dominion Rules web site at <http://www.dominionrules.org>

#include <gtest/gtest.h>

#include <random>
#include <vector>
#include <dominion/api.h>
#include <dominion/core/database.h>
#include <dominion/core/dice.h>
#include <dominion/core/definitions.h>
#include <dominion/character/character.h>
#include <dominion/character/character_utility.h>
#include <dominion/character/style.h>
#include <dominion/core/dice.h>

namespace DominionTest
{
	class CharacterTest : public testing::Test
	{
	public:
		CharacterTest()
			: api_(std::make_unique<Dominion::Api>())
		{
			std::random_device rd;

			rng_ = std::mt19937{ rd() };
			db_ = api_->GetDatabase();
		}

	protected:
		void SetUp() override
		{
			api_->InitializeFromMemory();
		}

	public:
		std::mt19937 rng_;
		std::shared_ptr<Dominion::DataBase> db_;
		std::unique_ptr<Dominion::Api> api_;
	};

	TEST_F(CharacterTest, Validation)
	{
		auto dice = std::make_shared<Dominion::Dice>();
		auto cTool = api_->GetCharacterCreationTool();

		// race should be set to 0 by default
		EXPECT_EQ(cTool->Validate(), Dominion::ECharacterValidationResult::InvalidRace);
		cTool->race(Dominion::RaceCount);
		EXPECT_EQ(cTool->Validate(), Dominion::ECharacterValidationResult::InvalidRace);
		cTool->race(Dominion::RaceHuman);

		// next style is verified
		EXPECT_EQ(cTool->Validate(), Dominion::ECharacterValidationResult::MissingStyle);
		auto styles = db_->GetStyles();
		cTool->style(styles[std::uniform_int_distribution < size_t > { 0, styles.size() - 1 }(rng_)]);

		// next perk roll is verified
		EXPECT_EQ(cTool->Validate(), Dominion::ECharacterValidationResult::InvalidPerk);
		cTool->perk(13);
		EXPECT_EQ(cTool->Validate(), Dominion::ECharacterValidationResult::InvalidPerk);
		cTool->perk(dice->Roll());

		// next attributes are checked
		EXPECT_EQ(cTool->Validate(), Dominion::ECharacterValidationResult::MissingAttributeRoll);
		cTool->attributesRoll(dice);
		EXPECT_EQ(cTool->Validate(), Dominion::ECharacterValidationResult::MissingAttributes);
		Dominion::AttributeArray attr;
		attr.fill(0);
		cTool->attributes(attr);
		EXPECT_EQ(cTool->Validate(), Dominion::ECharacterValidationResult::InvalidAttributes);
		attr.fill(99);
		EXPECT_EQ(cTool->Validate(), Dominion::ECharacterValidationResult::InvalidAttributes);
	}

	TEST_F(CharacterTest, CreateHumanSoldier)
	{
		auto dice = std::make_shared<Dominion::Dice>();
		auto cTool = api_->GetCharacterCreationTool();

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

		EXPECT_TRUE(static_cast<bool>(npc));
	}

	TEST_F(CharacterTest, CreateElfWitch)
	{
		auto dice = std::make_shared<Dominion::Dice>();
		auto cTool = api_->GetCharacterCreationTool();

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

		EXPECT_TRUE(static_cast<bool>(npc));
	}

	TEST_F(CharacterTest, CreateDwarfPriest)
	{
		auto dice = std::make_shared<Dominion::Dice>();
		auto cTool = api_->GetCharacterCreationTool();

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

		EXPECT_TRUE(static_cast<bool>(npc));
	}
} // namespace DominionTest