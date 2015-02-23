// Copyright(C) 2015 kittikun
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

#ifndef CHARACTER_UTILITY_H
#define CHARACTER_UTILITY_H

#include <memory>

#include <dominion/core/definitions.h>
#include <dominion/core/platform.h>

namespace Dominion
{
	enum class ECharacterValidationResult : uint_fast8_t
	{
		InvalidAttributes,
		InvalidPerk,
		InvalidRace,
		MissingAttributes,
		MissingAttributeRoll,
		MissingStyle,
		// (DR3.1.1 p30, 4-6 STEP FOUR: DETERMINE COMPOSITE STATS
		// If you had only 5 Attribute Points or less to divide between your six Attributes (...)
		// (If you are automatically entitled to Favorable Rounding, but your character already
		// got Favorable Rounding from the Character Generation Table, go back and re-roll on that table.
		RerollPerk,
		Valid
	};

	class Character;
	class DatabaseImpl;
	class Dice;
	class Style;
	class CharacterUtilityImpl;

#ifdef _WIN32
	template class DOMINION_API std::unique_ptr < CharacterUtilityImpl > ;
#endif

	// Utility to create characters
	class DOMINION_API CharacterUtility
	{
		CharacterUtility(const CharacterUtility&) = delete;
		CharacterUtility& operator=(const CharacterUtility&) = delete;
		CharacterUtility(CharacterUtility&&) = delete;
		CharacterUtility& operator=(CharacterUtility&&) = delete;

	public:
		CharacterUtility(std::unique_ptr<CharacterUtilityImpl>);
		~CharacterUtility();

		void attributes(const AttributeArray&);

		// (DR3.1.1 p30, 4-6 STEP THREE: DETERMINE ATTRIBUTE STATS)
		// 1. Assign a minimum score of 1 to each of your character six Attributes.
		AttributeArray attributesBase() const;

		// (DR3.1.1 p30, 4-6 STEP THREE: DETERMINE ATTRIBUTE STATS)
		// 2. Roll the twelve - sided die three times and record your results.
		// 3. Calculate the average of your three rolls. This is done by adding the three rolls together and
		// dividing the sum by three.The result is the number of Attribute Points you have to distribute between
		// your six Attributes. Make note of the remainder, if you get one
		std::shared_ptr<const AttributePointsRemainder> attributesRoll(const std::shared_ptr<Dice>& dice) const;

		void race(const ERace race);
		void perk(uint_fast8_t roll);
		void style(const std::shared_ptr<Style>& style);

		std::shared_ptr<Character> MakeCharacter() const;
		ECharacterValidationResult Validate() const;

	private:
		std::unique_ptr<CharacterUtilityImpl> impl_;
	};
} // namespace Dominion

#endif // CHARACTER_UTILITY_H
