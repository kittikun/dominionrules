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

#include <dominion/capi/cDatabase.h>

#include <dominion/core/database.h>

#include "chelper.h"

int SerializeStyles()
{
	std::string buffer;
	CHelper::instance().GetAPI().lock()->GetDatabase()->SerializeStyles(buffer);

	return CHelper::instance().RegisterFBBuffer(buffer);
}

int GetStylesSize(const int handle)
{
	auto res = CHelper::instance().GetFBBuffer(handle);

	if (!res)
		return -1;

	return static_cast<int>(res->size());
}

bool GetStylesBuffer(const int handle, char* dst)
{
	auto src = CHelper::instance().GetFBBuffer(handle);

	if (!src)
		return false;

	std::copy(src->begin(), src->end(), dst);

	return true;
}

void ReleaseStylesBuffer(const int handle)
{
	CHelper::instance().UnregisterFBBuffer(handle);
}