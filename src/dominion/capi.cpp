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

#include <dominion/capi.h>

#include <memory>
#include <random>
#include <unordered_map>

#include <dominion/api.h>
#include <dominion/core/dice.h>
#include <dominion/character/character_utility.h>

#include "impl/api_impl.h"
#include "impl/dice_impl.h"
#include "impl/character_utility_impl.h"

class CHelper
{
public:
	CHelper::CHelper()
		: api_(std::make_shared<Dominion::Api>())
	{
		std::random_device rd;
		rng_ = std::mt19937{ rd() };
	}

	static CHelper& CHelper::instance()
	{
		static CHelper instance;

		return instance;
	}

	std::weak_ptr<Dominion::Api> GetAPI()
	{
		return api_;
	}

	template<typename T>
	std::weak_ptr<T> GetItem(const int handle)
	{
		auto res = container_.find(handle);

		if (res != container_.end())
			return std::static_pointer_cast<T>(res->second);

		return std::weak_ptr<T>();
	}

	void InitializeFromMemory()
	{
		api_->InitializeFromMemory();
	}

	const int RegisterItem(std::shared_ptr<Dominion::Object> item)
	{
		std::uniform_int_distribution<> dist(0, INT_MAX);

		const int rng = dist(rng_);

		container_.insert(std::make_pair(rng, item));

		return rng;
	}

private:
	std::shared_ptr<Dominion::Api> api_;
	std::unordered_map<int, std::shared_ptr<Dominion::Object>> container_;
	std::mt19937 rng_;
};

void InitializeFromMemory()
{
	CHelper::instance().InitializeFromMemory();
}

int GetCharacterCreationTool()
{
	const int ret = CHelper::instance().RegisterItem(std::move(CHelper::instance().GetAPI().lock()->GetCharacterCreationTool()));

	return ret;
}

int CreateDice()
{
	const int ret = CHelper::instance().RegisterItem(std::make_shared<Dominion::Dice>());

	return ret;
}

bool getSomeArrayData(int hCTool, int hDice, float* values, int size)
{
	auto cTool = CHelper::instance().GetItem<Dominion::CharacterUtility>(hCTool);
	auto dice = CHelper::instance().GetItem<Dominion::Dice>(hDice);

	auto ar = cTool.lock()->attributesRoll(dice.lock());

	return false;
}