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

#include "capi.h"

#include <dominion/api.h>
#include <dominion/core/dice.h>
#include <dominion/character/character_utility.h>

#include "../impl/api_impl.h"
#include "../impl/dice_impl.h"
#include "../impl/character_utility_impl.h"

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

//bool getSomeArrayData(int hCTool, int hDice, float* values, int size)
//{
//	auto cTool = CHelper::instance().GetItem<Dominion::CharacterUtility>(hCTool);
//	auto dice = CHelper::instance().GetItem<Dominion::Dice>(hDice);
//
//	auto ar = cTool.lock()->attributesRoll(dice.lock());
//
//	ar->
//
//		return false;
//}