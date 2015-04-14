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

#ifndef PERK_H
#define PERK_H

#include <memory>

#include <dominion/core/definitions.h>
#include <dominion/core/platform.h>

namespace Dominion
{
	class PerkImpl;

#ifdef _WIN32
	template class DOMINION_API std::shared_ptr < PerkImpl > ;
#endif

	// (DR3.1.1 p28, 4-4 STEP TWO: THE CHARACTER GENERATION TABLE)
	// Once you have determined who your character is, you must make a roll
	// on the Character Generation Table.This table give perks to starting characters.
	class DOMINION_API Perk
	{
		Perk(const Perk&) = delete;
		Perk& operator=(const Perk&) = delete;

	public:
		Perk(const std::shared_ptr<PerkImpl>& impl);
		~Perk();

		uint_fast32_t guid() const;
		const std::string& name();

	private:
		std::shared_ptr<PerkImpl> impl_;
	};
}

#endif // PERK_H
