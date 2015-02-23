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

#include "perk_impl.h"

#include <boost/lexical_cast.hpp>

#include "classid.h"
#include "database_impl.h"

namespace Dominion
{
	PerkImpl::PerkImpl(const uint_fast32_t id) :
		DataItem(id),
		bonus_(0),
		target_(-1)
	{}

	int PerkImpl::LoadFromDB(void* data, int argc, char** argv, char** col)
	{
		DatabaseImpl* db = static_cast<DatabaseImpl*>(data);
		std::shared_ptr<PerkImpl> perk;

		for (int i = 0; i < argc; ++i) {
			if (argv[i] == nullptr)
				continue;

			if (strcmp(col[i], "Id") == 0) {
				uint_fast32_t id = ClassID_Perk + boost::lexical_cast<uint_fast32_t>(argv[i]);
				perk = std::make_shared<PerkImpl>(id);
			}
			else if (strcmp(col[i], "type") == 0) {
				perk->type_ = static_cast<EPerkType>(boost::lexical_cast<int32_t>(argv[i]));
			}
			else if (strcmp(col[i], "name") == 0) {
				perk->name_ = argv[i];
			}
			else if (strcmp(col[i], "roll") == 0) {
				perk->roll_ = (uint_fast8_t)boost::lexical_cast<int32_t>(argv[i]);
			}
			else if (strcmp(col[i], "target") == 0) {
				int32_t target = boost::lexical_cast<int32_t>(argv[i]);

				switch (perk->type_) {
				case EPerkType::Attribute:
					perk->target_ = target;
					break;

				case EPerkType::Skill:
					perk->target_ = ClassID_Skill_Template + target;
					break;

				case EPerkType::Advancement_Points:
				case EPerkType::Passive:
					break;

				default:
					throw std::out_of_range("perk target");
					return 1;
				}
			}
			else if (strcmp(col[i], "bonus") == 0) {
				perk->bonus_ = (uint_fast8_t)boost::lexical_cast<int32_t>(argv[i]);
			}
			else if (strcmp(col[i], "isHuman") == 0) {
				perk->usableRace_[ERace::RaceHuman] = boost::lexical_cast<bool>(argv[i]);
			}
			else if (strcmp(col[i], "isElf") == 0) {
				perk->usableRace_[ERace::RaceElf] = boost::lexical_cast<bool>(argv[i]);
			}
			else if (strcmp(col[i], "isDwarf") == 0) {
				perk->usableRace_[ERace::RaceDwarf] = boost::lexical_cast<bool>(argv[i]);
			}
			else if (strcmp(col[i], "isHalfling") == 0) {
				perk->usableRace_[ERace::RaceHalfling] = boost::lexical_cast<bool>(argv[i]);
			}
			else if (strcmp(col[i], "isHumanoid") == 0) {
				perk->usableRace_[ERace::RaceHumanoid] = boost::lexical_cast<bool>(argv[i]);
			}
			else if (strcmp(col[i], "isBeast") == 0) {
				perk->usableRace_[ERace::RaceBeast] = boost::lexical_cast<bool>(argv[i]);
			}
		}

		db->AddData<PerkImpl>(perk);

		return 0;
	}

	bool PerkImpl::isRaceUsable(ERace race) const
	{
		return usableRace_[race];
	}
}