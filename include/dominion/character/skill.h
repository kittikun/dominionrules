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

#ifndef SKILL_H
#define SKILL_H

#include <memory>
#include <string>

#include <dominion/core/definitions.h>
#include <dominion/core/platform.h>

namespace Dominion
{
	class SkillImpl;

#ifdef _WIN32
	template class DOMINION_API std::shared_ptr < SkillImpl > ;
#endif

	// (DR3.1.1 p13, 4-4 SkillS)
	class DOMINION_API Skill
	{
		Skill(const Skill&) = delete;
		Skill& operator=(const Skill&) = delete;

	public:
		Skill(const std::shared_ptr<SkillImpl>&);
		~Skill();

		const std::string& name() const;
		uint_fast8_t level() const;

	private:
		std::shared_ptr<SkillImpl> impl_;
	};
} // namespace Dominion

#endif // SKILL_H
