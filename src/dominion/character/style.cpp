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

#include <dominion/character/style.h>

#include <dominion/core/definitions.h>
#include <generated/style_generated.h>

#include "../impl/style_impl.h"

namespace Dominion
{
	Style::Style(const std::shared_ptr<StyleImpl>& impl)
		: impl_(impl)
	{}

	Style::~Style()
	{}

	bool Style::isBeast() const
	{
		return impl_->archetypes_.test(EArchetype::ArchetypeBeast);
	}

	bool Style::isWitch() const
	{
		return impl_->archetypes_.test(EArchetype::ArchetypeWitch);
	}

	bool Style::isPriest() const
	{
		return impl_->archetypes_.test(EArchetype::ArchetypePriest);
	}

	const std::string& Style::name() const
	{
		return impl_->name_;
	}
} // namespace Dominion