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

#include "character_impl.h"

#include "database_impl.h"
#include "perk_impl.h"

namespace Dominion
{
	CharacterImpl::CharacterImpl(const uint_fast32_t id) :
		DataItem{ id },
		race_{ RaceCount },
		// (DR3.1.1 p31, 4-7 STEP FIVE: DETERMINE YOUR ADVANCEMENT POINTS)
		// All starting characters are given 45 Advancement
		// Points(APs) to spend as you see fit.Some characters
		// start with more that 45 APs.
		ap_{ 45 }
	{}

	const bool CharacterImpl::hasFavourableRounding() const
	{
		// intentionally left Favorable Rounding perk as first item so we can quickly check
		if (perks_[0]->roll_ == 1)
			return true;

		return false;
	}
} // namespace Dominion