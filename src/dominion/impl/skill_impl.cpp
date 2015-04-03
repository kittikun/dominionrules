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

#include "skill_impl.h"

#include "skill_template_impl.h"

namespace Dominion
{
	SkillImpl::SkillImpl(const std::shared_ptr<SkillTemplateImpl>& tplt) :
		template_(tplt),
		level_(0)
	{
	}

	const std::string& SkillImpl::name() const
	{
		return template_->name_;
	}

	uint_fast16_t SkillImpl::CostToRaise() const
	{
		// Triangular numbers: a(n) = C(n+1,2) = n(n+1)/2 = 0+1+2+...+n.
		// https://oeis.org/A000217
		static std::array<uint_fast16_t, 54> costPerLevel = {
			0, 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 66, 78, 91, 105,
			120, 136, 153, 171, 190, 210, 231, 253, 276, 300, 325, 351,
			378, 406, 435, 465, 496, 528, 561, 595, 630, 666, 703, 741,
			780, 820, 861, 903, 946, 990, 1035, 1081, 1128, 1176, 1225,
			1275, 1326, 1378, 1431 };

		if (static_cast<uint_fast16_t>(level_ + 1) >= costPerLevel.size())
			throw std::out_of_range("Requested level is too high");

		return costPerLevel[level_ + 1] - costPerLevel[level_];
	}
} // namespace Dominion
