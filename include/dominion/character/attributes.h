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

#ifndef ABILITIES_H
#define ABILITIES_H

#include <memory>

#include <dominion/core/definitions.h>
#include <dominion/core/platform.h>

namespace Dominion
{
	class AttributesImpl;

#ifdef _WIN32
	template class DOMINION_API std::shared_ptr < AttributesImpl > ;
#endif

	class DOMINION_API Attributes
	{
	public:
		Attributes(const std::shared_ptr<AttributesImpl>&);
		~Attributes();

		Attributes(const Attributes&) = delete;
		Attributes& operator=(const Attributes&) = delete;

		const AttributeArray asArray() const;
		const uint_fast8_t agility() const;
		const uint_fast8_t intuition() const;
		const uint_fast8_t intellect() const;
		const uint_fast8_t luck() const;
		const uint_fast8_t stamina() const;
		const uint_fast8_t vigour() const;

	private:
		std::shared_ptr<AttributesImpl> impl_;
	};
}

#endif
