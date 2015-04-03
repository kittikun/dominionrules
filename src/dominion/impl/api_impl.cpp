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

#include "api_impl.h"

#include <numeric>
#include <sstream>

#include <dominion/core/database.h>
#include <dominion/character/character_utility.h>

#include "character_utility_impl.h"
#include "database_impl.h"
#include "skill_template_impl.h"

namespace Dominion
{
	ApiImpl::ApiImpl() :
		db_{ std::make_shared<DatabaseImpl>() }
	{}

	std::shared_ptr<DataBase> ApiImpl::database() const
	{
		return std::make_shared<DataBase>(db_);
	}

	void ApiImpl::LoadDatabaseFromMemory()
	{
		db_->OpenDatabaseFromMemory();

		// create data structure from db_ info
		db_->ExecuteQuery("select * from perk", PerkImpl::LoadFromDB);
		db_->ExecuteQuery("select * from skill", SkillTemplateImpl::LoadFromDB);
		db_->ExecuteQuery("select * from style", StyleImpl::LoadFromDB);
	}

	std::unique_ptr<CharacterUtilityImpl> ApiImpl::MakeCharacterTool() const
	{
		return std::unique_ptr<CharacterUtilityImpl>(new CharacterUtilityImpl{ db_ });
	}
} // namespace Dominion