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

#include <dominion/character/character_utility.h>

#include <dominion/character/character.h>
#include <dominion/character/style.h>
#include <dominion/core/dice.h>

#include "../impl/attribute_impl.h"
#include "../impl/character_utility_impl.h"
#include "../impl/dice_impl.h"

namespace Dominion
{
	CharacterUtility::CharacterUtility(std::unique_ptr<CharacterUtilityImpl> impl) :
		impl_{ std::move(impl) }
	{}

	CharacterUtility::~CharacterUtility()
	{}

	void CharacterUtility::attributes(const AttributeArray& attributes)
	{
		impl_->attributes_ = std::make_shared<AttributesImpl>(attributes);
	}

	AttributeArray CharacterUtility::attributesBase() const
	{
		return impl_->attributesBase();
	}

	std::shared_ptr<const AttributePointsRemainder> CharacterUtility::attributesRoll(const std::shared_ptr<Dice>& dice) const
	{
		return impl_->attributesRoll(dice);
	}

	void CharacterUtility::race(const ERace race)
	{
		impl_->race_ = race;
	}

	void CharacterUtility::perk(uint_fast8_t roll)
	{
		impl_->perkRoll_ = roll;
	}

	void CharacterUtility::style(const std::shared_ptr<Style>& style)
	{
		impl_->style_ = style->impl_;
	}

	std::shared_ptr<Character> CharacterUtility::MakeCharacter() const
	{
		return std::make_shared<Character>(impl_->MakeCharacter());
	}

	ECharacterValidationResult CharacterUtility::Validate() const
	{
		return impl_->Validate();
	}
} // namespace Dominion