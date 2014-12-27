// Copyright(C) 2014 kittikun
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
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

#ifndef CHARACTER_UTILITY_IMPL_H
#define CHARACTER_UTILITY_IMPL_H

#include <memory>

#include <dominion/character/character_utility.h>
#include <dominion/core/definitions.h>

namespace Dominion
{
	class AttributesImpl;
	class Dice;
	class Style;
	class CharacterImpl;
	class DatabaseImpl;
	class PerkImpl;
	class StyleImpl;

	class CharacterUtilityImpl
	{
		CharacterUtilityImpl(const CharacterUtilityImpl&) = delete;
		CharacterUtilityImpl& operator=(const CharacterUtilityImpl&) = delete;
		CharacterUtilityImpl(CharacterUtilityImpl&&) = delete;
		CharacterUtilityImpl& operator=(CharacterUtilityImpl&&) = delete;

	public:
		CharacterUtilityImpl(std::shared_ptr<DatabaseImpl>);
		~CharacterUtilityImpl();

		AttributeArray attributesBase() const;
		std::shared_ptr<const AttributePointsRemainder> attributesRoll(const std::shared_ptr<Dice>& dice);

		void race(const ERace race);
		void perk(uint_fast8_t roll);

		std::shared_ptr<CharacterImpl> MakeCharacter() const;
		ECharacterValidationResult Validate() const;

	private:
		void ApplyPerks(const std::shared_ptr<CharacterImpl>&) const;
		void SetPerks(const std::shared_ptr<CharacterImpl>&) const;
		void SetSkills(const std::shared_ptr<CharacterImpl>&) const;
		void SetAttributesSkills(const std::shared_ptr<CharacterImpl>&) const;
		void SetCombatSkills(const std::shared_ptr<CharacterImpl>&) const;
		void SetPriestcraftSkills(const std::shared_ptr<CharacterImpl>&) const;
		void SetWitchcraftSkills(const std::shared_ptr<CharacterImpl>&) const;
		std::string GetSkillQuery(const std::shared_ptr<CharacterImpl>&) const;
		std::string RaceToSkillQuery() const;
		std::string RaceToPerkQuery() const;

	public:
		std::shared_ptr<AttributesImpl> attributes_;
		std::shared_ptr<const AttributePointsRemainder> aPtRemain_;
		std::shared_ptr<DatabaseImpl> db_;
		ERace race_;
		uint_fast8_t perkRoll_;
		std::shared_ptr<StyleImpl> style_;
	};
} // namespace Dominion

#endif // CHARACTER_UTILITY_IMPL_H
