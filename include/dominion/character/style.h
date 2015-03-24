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

#ifndef STYLE_H
#define STYLE_H

#include <memory>

#include <dominion/core/definitions.h>
#include <dominion/core/platform.h>

namespace Dominion
{
	class StyleImpl;

#ifdef _WIN32
	template class DOMINION_API std::shared_ptr < StyleImpl > ;
#endif

	// (DR3.1.1 p26, 4-2 CHARACTER STYLES)
	// Once you have thought about these questions, you may want to consider
	// some classic RPG character styles.
	class DOMINION_API Style
	{
		friend class CharacterUtility;

		Style(const Style&) = delete;
		Style& operator=(const Style&) = delete;
		Style(Style&&) = delete;
		Style& operator=(Style&&) = delete;

	public:
		Style(const std::shared_ptr<StyleImpl>& impl);
		~Style();

		const std::string& name();

	private:
		std::shared_ptr<StyleImpl> impl_;
	};
} // namespace Dominion

#endif // STYLE_H
