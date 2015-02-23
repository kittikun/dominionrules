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

#include "character_utility_impl.h"

#include <numeric>

#include <dominion/core/dice.h>
#include <dominion/character/style.h>

#include "attribute_impl.h"
#include "character_impl.h"
#include "database_impl.h"
#include "dice_impl.h"
#include "skill_impl.h"
#include "skill_template.h"
#include "style_impl.h"
#include "classid_utility.h"

namespace Dominion
{
	CharacterUtilityImpl::CharacterUtilityImpl(std::shared_ptr<DatabaseImpl> db) :
		db_{ db },
		race_{ RaceCount }
	{}

	CharacterUtilityImpl::~CharacterUtilityImpl()
	{}

	void CharacterUtilityImpl::ApplyPerks(const std::shared_ptr<CharacterImpl>& character) const
	{
		for (auto perk : character->perks_) {
			switch (perk->type_) {
				case EPerkType::Advancement_Points: {
					character->ap_ += perk->bonus_;
					break;
				}

				case EPerkType::Attribute: {
					if (perk->target_ == AttributeCount) {
						for (int i = 0; i < AttributeCount; ++i)
							character->attributes_->array_[i] += perk->bonus_;
					} else {
						character->attributes_->array_[perk->target_] += perk->bonus_;
					}
					break;
				}

				case EPerkType::Skill: {
					if (perk->target_ == ClassID_Skill_Template) {
						for (auto skill : character->skills_)
							skill.second->level_ += perk->bonus_;
					} else {
						character->skills_[perk->target_]->level_ += perk->bonus_;
					}
					break;
				}

				default: {
					break;
				}
			}
		}
	}

	AttributeArray CharacterUtilityImpl::attributesBase() const
	{
		AttributeArray attributes;

		attributes.fill(1);

		return attributes;
	}

	std::shared_ptr<const AttributePointsRemainder> CharacterUtilityImpl::attributesRoll(const std::shared_ptr<Dice>& dice)
	{
		std::array < uint_fast8_t, 3 >  res;

		for (size_t i = 0; i < res.size(); ++i)
			res[i] = dice->Roll();

		const uint_fast8_t sum = std::accumulate(std::begin(res), std::end(res), uint_fast8_t(0));

		aPtRemain_ = std::make_shared<const AttributePointsRemainder>(std::make_tuple(sum / 3, sum % 3));

		return aPtRemain_;
	}

	std::string CharacterUtilityImpl::GetSkillQuery(const std::shared_ptr<CharacterImpl>& character) const
	{
		std::string res;

		switch (character->race_) {
			case RaceBeast:
			case RaceHumanoid: {
				res = "select id from skill where id > 0 and %1%";
				break;
			}

			case RaceHuman:
			case RaceElf:
			case RaceDwarf:
			case RaceHalfling: {
				res = "select id from skill where id > 0 and %1% and dependency <= 3";
				break;
			}

			default:
				throw std::out_of_range("race value");
		}

		if (character->style_->archetypes_[ArchetypePriest])
			res += " or dependency = 4 and target = 1";
		else if (character->style_->archetypes_[ArchetypeWitch])
			res += " or dependency = 4 and target = 2";

		res = boost::str(boost::format(res) % RaceToSkillQuery());

		return res;
	}

	std::shared_ptr<CharacterImpl> CharacterUtilityImpl::MakeCharacter() const
	{
		if (Validate() == ECharacterValidationResult::Valid) {
			uint_fast32_t id = ClassIDUtility<CharacterImpl>::next();
			std::shared_ptr<CharacterImpl> character = std::make_shared<CharacterImpl>(id);

			character->attributes_ = attributes_;
			character->race_ = race_;
			character->style_ = style_;
			SetPerks(character);
			SetSkills(character);

			// (DR3.1.1 p31, 4-7 STEP FIVE: DETERMINE YOUR ADVANCEMENT POINTS)
			// If you had a remainder when you determined your Attribute stats, that remainder is converted into an
			// equivalent number of starting Advancement Points	(APs)
			character->ap_ = 45 + std::get<1>(*aPtRemain_);

			ApplyPerks(character);

			return character;
		}

		return std::shared_ptr<CharacterImpl>();
	}

	void CharacterUtilityImpl::SetAttributesSkills(const std::shared_ptr<CharacterImpl>& character) const
	{
		for (auto skill : character->skills_) {
			if ((skill.second->template_->dependency_ == ESkillDependency::Attribute) && (skill.second->template_->target_ == AttributeAgility))
				skill.second->level_ = character->attributes_->array_[AttributeAgility];
			else if ((skill.second->template_->dependency_ == ESkillDependency::Attribute) && (skill.second->template_->target_ == AttributeIntellect))
				skill.second->level_ = character->attributes_->array_[AttributeIntellect];
			else if ((skill.second->template_->dependency_ == ESkillDependency::Attribute) && (skill.second->template_->target_ == AttributeIntuition))
				skill.second->level_ = character->attributes_->array_[AttributeIntuition];
			else if ((skill.second->template_->dependency_ == ESkillDependency::Attribute) && (skill.second->template_->target_ == AttributeLuck))
				skill.second->level_ = character->attributes_->array_[AttributeLuck];
			else if ((skill.second->template_->dependency_ == ESkillDependency::Attribute) && (skill.second->template_->target_ == AttributeStamina))
				skill.second->level_ = character->attributes_->array_[AttributeStamina];
			else if ((skill.second->template_->dependency_ == ESkillDependency::Attribute) && (skill.second->template_->target_ == AttributeVigour))
				skill.second->level_ = character->attributes_->array_[AttributeVigour];
		}
	}

	void CharacterUtilityImpl::SetCombatSkills(const std::shared_ptr<CharacterImpl>& character) const
	{
		// (DR3.1.1 p30, 4-6 STEP TWO: THE CHARACTER GENERATION TABLE)
		// For the Combat Composite, take your Vigor and Agility stats
		float composite = (character->attributes_->array_[AttributeAgility] + character->attributes_->array_[AttributeVigour]) / 2.f;

		if (character->hasFavourableRounding())
			composite = ceil(composite);
		else
			composite = floor(composite);

		for (auto skill : character->skills_) {
			if ((skill.second->template_->type_ == ESkillType::Usable_Combat) || (skill.second->template_->type_ == ESkillType::Usable_Defensive))
				skill.second->level_ = static_cast<int_fast8_t>(composite);
		}
	}

	void CharacterUtilityImpl::SetPerks(const std::shared_ptr<CharacterImpl>& character) const
	{
		boost::format fmt = boost::format("select id from perk where %1% and roll=%2%") % RaceToPerkQuery() % (uint_fast32_t)perkRoll_;
		std::string query = boost::str(fmt);

		// (DR3.1.1 p30, 4-6 STEP TWO: THE CHARACTER GENERATION TABLE)
		// If you had only 5 Attribute Points or less to divide between your six Attributes
		// in Step Three, your character is automatically entitled to Favorable Rounding.
		if (std::get<0>(*aPtRemain_) <= 5) {
			fmt = boost::format("select id from perk where %1% and roll=1") % RaceToPerkQuery();
			character->perks_.push_back(db_->Get<PerkImpl>(ClassID_Perk + db_->GetIntValue(boost::str(fmt))));
		}

		character->perks_.push_back(db_->Get<PerkImpl>(ClassID_Perk + db_->GetIntValue(query)));
	}

	void CharacterUtilityImpl::SetPriestcraftSkills(const std::shared_ptr<CharacterImpl>& character) const
	{
		// (DR3.1.1 p30, 4-6 STEP TWO: THE CHARACTER GENERATION TABLE)
		// For the Priest-craft Composite, take your Stamina and Intuition stats
		float composite = (character->attributes_->array_[AttributeStamina] + character->attributes_->array_[AttributeIntuition]) / 2.f;

		if (character->hasFavourableRounding())
			composite = ceil(composite);
		else
			composite = floor(composite);

		for (auto skill : character->skills_) {
			if (skill.second->template_->type_ == ESkillType::Priestcraft)
				skill.second->level_ = static_cast<int_fast8_t>(composite);
		}
	}

	void CharacterUtilityImpl::SetSkills(const std::shared_ptr<CharacterImpl>& character) const
	{
		auto templates = db_->GetList<SkillTemplate>(GetSkillQuery(character));

		character->skills_.reserve(templates.size());

		for (auto tplt : templates) {
			character->skills_.insert(std::make_pair(tplt->guid(), std::make_shared<SkillImpl>(tplt)));
		}

		SetAttributesSkills(character);
		SetCombatSkills(character);

		if (character->style_->archetypes_[ArchetypePriest]) {
			SetPriestcraftSkills(character);
		}

		if (character->style_->archetypes_[ArchetypeWitch]) {
			SetWitchcraftSkills(character);
		}
	}

	void CharacterUtilityImpl::SetWitchcraftSkills(const std::shared_ptr<CharacterImpl>& character) const
	{
		// (DR3.1.1 p30, 4-6 STEP TWO: THE CHARACTER GENERATION TABLE)
		// For the Witchcraft Composite, take your Intellect and Luck stats
		float composite = (character->attributes_->array_[AttributeIntellect] + character->attributes_->array_[AttributeLuck]) / 2.f;

		if (character->hasFavourableRounding())
			composite = ceil(composite);
		else
			composite = floor(composite);

		for (auto skill : character->skills_) {
			if (skill.second->template_->type_ == ESkillType::Witchcraft)
				skill.second->level_ = static_cast<int_fast8_t>(composite);
		}
	}

	ECharacterValidationResult CharacterUtilityImpl::Validate() const
	{
		if ((race_ < 0) || (race_ >= RaceCount))
			return ECharacterValidationResult::InvalidRace;

		if (!style_)
			return ECharacterValidationResult::MissingStyle;

		if ((perkRoll_ == 0) || (perkRoll_ > 12))
			return ECharacterValidationResult::InvalidPerk;

		// Gifted perk specific
		boost::format fmt = boost::format("select id from perk where %1% and roll=%2%") % RaceToPerkQuery() % (uint_fast32_t)perkRoll_;
		auto perk = db_->Get<PerkImpl>(ClassID_Perk + db_->GetIntValue(boost::str(fmt)));

		if (!aPtRemain_)
			return ECharacterValidationResult::MissingAttributeRoll;

		if (!attributes_)
			return ECharacterValidationResult::MissingAttributes;

		uint_fast8_t sum = std::accumulate(attributes_->array_.begin(), attributes_->array_.end(), (uint_fast8_t)0);
		uint_fast8_t expected = 6 + std::get<0>(*aPtRemain_);
		uint_fast8_t max = 6 + 12;

		if ((sum > max) || (sum < expected) || (sum > expected)) {
			return ECharacterValidationResult::InvalidAttributes;
		}

		// (DR3.1.1 p30, 4-6 STEP TWO: THE CHARACTER GENERATION TABLE)
		// If you had only 5 Attribute Points or less to divide between your six Attributes (...)
		// If you are automatically entitled to Favorable Rounding, but your character already
		// got Favorable Rounding from the Character Generation Table, go back and re-roll on that table.
		if ((perkRoll_ == 1) && (std::get<0>(*aPtRemain_) <= 5))
			return ECharacterValidationResult::RerollPerk;

		return ECharacterValidationResult::Valid;
	}

	std::string CharacterUtilityImpl::RaceToPerkQuery() const
	{
		switch (race_) {
			case RaceBeast:
				return "isBeast";

			case RaceDwarf:
				return "isDwarf";

			case RaceElf:
				return "isElf";

			case RaceHalfling:
				return "isHalfling";

			case RaceHuman:
				return "isHuman";

			case RaceHumanoid:
				return "isHumanoid";

			default:
				throw std::out_of_range("race value");
		}
	}

	std::string CharacterUtilityImpl::RaceToSkillQuery() const
	{
		switch (race_) {
			case RaceHuman:
			case RaceElf:
			case RaceHalfling:
			case RaceDwarf:
				return "bySentient";

			case RaceBeast:
				return "byBeast";

			case RaceHumanoid:
				return "byHumanoid";

			default:
				throw std::out_of_range("race value");
		}
	}
} // namespace Dominion