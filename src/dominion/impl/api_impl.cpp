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

#include "api_impl.h"

#include <numeric>
#include <sstream>
#include <boost/filesystem.hpp>
#include <cereal/archives/json.hpp>

#include <dominion/core/database.h>
#include <dominion/character/character_utility.h>

#include "character_utility_impl.h"
#include "database_impl.h"
#include "perk_impl.h"
#include "skill_template.h"
#include "style_impl.h"

namespace Dominion
{
	ApiImpl::ApiImpl() :
		db_{ std::make_shared<DatabaseImpl>() }
	{}

	std::shared_ptr<DataBase> ApiImpl::database() const
	{
		return std::make_shared<DataBase>(db_);
	}

	ApiImpl& ApiImpl::instance()
	{
		static ApiImpl instance;

		return instance;
	}

	void ApiImpl::LoadDatabase(const std::string& dataPath)
	{
		boost::filesystem::path path(dataPath);
		boost::filesystem::path file("dominion.db");
		boost::filesystem::path canonical = boost::filesystem::canonical(dataPath / file);

		canonical = canonical.make_preferred();

		if (boost::filesystem::exists(canonical)) {
			db_->ConnectDatabase(canonical);

			// create data structure from db_ info
			db_->ExecuteQuery("select * from perk", PerkImpl::LoadFromDB);
			db_->ExecuteQuery("select * from skill", SkillTemplate::LoadFromDB);
			db_->ExecuteQuery("select * from style", StyleImpl::LoadFromDB);
		} else {
			throw std::invalid_argument("Invalid path to database");
		}
	}

	std::unique_ptr<CharacterUtilityImpl> ApiImpl::MakeCharacterTool() const
	{
		return std::unique_ptr<CharacterUtilityImpl>(new CharacterUtilityImpl{ db_ });
	}

	std::string ApiImpl::test()
	{
		auto list = db_->GetList<StyleImpl>("select id from style");

		std::stringstream ss;
		cereal::JSONOutputArchive oarchive(ss);

		oarchive(*list[0]);

		return ss.str();
	}
} // namespace Dominion