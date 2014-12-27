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

#ifndef DICE_H
#define DICE_H

#include <cstdint>
#include <memory>

#include <dominion/core/platform.h>

namespace Dominion
{
	class DiceImpl;

#ifdef _WIN32
	template class DOMINION_API std::unique_ptr < DiceImpl > ;
#endif

	class DOMINION_API Dice
	{
		Dice(const Dice&) = delete;
		Dice& operator=(const Dice&) = delete;
		Dice(Dice&&) = delete;
		Dice& operator=(Dice&&) = delete;

	public:
		Dice();
		~Dice();

		// (DR3.1.1 p7, 4-2 WHAT YOU NEED TO PLAY)
		// To play DR, you need [..] A one twelve-sided die.
		const uint_fast8_t Roll() const;

	private:
		std::unique_ptr<DiceImpl> impl_;
	};
} // namespace Dominion

#endif // DICE_H
