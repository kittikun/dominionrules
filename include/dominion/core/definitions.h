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

#ifndef DEFINITION_H
#define DEFINITION_H

#include <array>
#include <cstdint>
#include <tuple>

namespace Dominion
{
	// (DR3.1.1 p9, 1-1 THE SIX ATTRIBUTES)
	enum EAttribute
	{
		AttributeAgility,
		AttributeIntuition,
		AttributeIntellect,
		AttributeLuck,
		AttributeStamina,
		AttributeVigour,
		AttributeCount
	};

	enum class ESkillType : uint_fast8_t {
		Beast_Combat,
		Beast_Defensive,
		Bease_Normal,
		Usable_Combat,
		Usable_Defensive,
		Usable_Normal,
		Passive,
		Priestcraft,
		Weapon_Profiency,
		Witchcraft
	};

	enum class ESkillDependency : uint_fast8_t {
		Attribute,
		None,
		Weapon,
		Armor,
		Archetype
	};

	enum class EPerkType : uint_fast8_t {
		Attribute,
		Advancement_Points,
		Passive,
		Skill,
	};

	// (DR3.1.1 p29, 4-5 Character generation table)
	enum ERace {
		RaceBeast,
		RaceDwarf,
		RaceElf,
		RaceHalfling,
		RaceHuman,
		RaceHumanoid,
		RaceCount
	};

	enum EArchetype {
		ArchetypeBeast,
		ArchetypePriest,
		ArchetypeWitch,
		ArchetypeCount
	};

	// Number of points / Remainder
	typedef std::tuple<const uint_fast8_t, const uint_fast8_t> AttributePointsRemainder;
	typedef std::array<uint_fast8_t, AttributeCount> AttributeArray;
} // namespace Dominion

#endif // DEFINITION_H
