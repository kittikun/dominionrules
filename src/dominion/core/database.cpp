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

#include <dominion/core/database.h>

#include <sstream>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>

#include <dominion/character/perk.h>
#include <dominion/character/skill_template.h>
#include <dominion/character/style.h>

#include "../impl/database_impl.h"
#include "../impl/perk_impl.h"
#include "../impl/skill_template_impl.h"
#include "../impl/style_impl.h"

namespace Dominion
{
	DataBase::DataBase(const std::shared_ptr<DatabaseImpl>& impl) :
		impl_(impl)
	{}

	DataBase::~DataBase()
	{}

	std::vector<std::shared_ptr<Perk>> DataBase::GetPerks() const
	{
		auto results = impl_->GetList<PerkImpl>("select id from perk");

		std::vector<std::shared_ptr<Perk>> res;

		res.reserve(results.size());

		for (auto item : results) {
			res.push_back(std::make_shared<Perk>(item));
		}

		return res;
	}

	std::vector<std::shared_ptr<SkillTemplate>> DataBase::GetSkillTemplates() const
	{
		auto results = impl_->GetList<SkillTemplateImpl >("select id from style");

		std::vector<std::shared_ptr<SkillTemplate>> res;

		res.reserve(results.size());

		for (auto item : results) {
			res.push_back(std::make_shared<SkillTemplate>(item));
		}

		return res;
	}

	std::vector<std::shared_ptr<Style>> DataBase::GetStyles() const
	{
		auto results = impl_->GetList<StyleImpl>("select id from style");

		std::vector<std::shared_ptr<Style>> res;

		res.reserve(results.size());

		for (auto item : results) {
			res.push_back(std::make_shared<Style>(item));
		}

		return res;
	}

	std::string DataBase::GetStylesAsJSON() const
	{
		std::stringstream ss;
		cereal::JSONOutputArchive archive(ss);
		auto results = impl_->GetList<StyleImpl>("select id from style");

		archive(results);

		return ss.str();
	}

	const uint32_t DataBase::GetVersion() const
	{
		return impl_->GetIntValue("select value from config where type is \"version\"");
	}
} // namespace Dominion