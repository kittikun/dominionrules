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

#ifndef PERK_IMPL_H
#define PERK_IMPL_H

#include <memory>
#include <bitset>

#include <dominion/core/definitions.h>

#include "dataitem.h"

namespace Dominion
{
	class DatabaseImpl;

	class PerkImpl : public DataItem
	{
		PerkImpl(const PerkImpl&) = delete;
		PerkImpl& operator=(const PerkImpl&) = delete;

	public:
		PerkImpl(const uint_fast32_t id);

		static int LoadFromDB(void*, int, char**, char**);

		bool isRaceUsable(ERace race) const;
	public:
		EPerkType type_;
		uint_fast8_t roll_;
		uint_fast8_t bonus_;
		int32_t target_;
		std::bitset<ERace::RaceCount> usableRace_;
		std::string name_;
	};
} // namespace Dominion

#endif // PERK_IMPL_H
