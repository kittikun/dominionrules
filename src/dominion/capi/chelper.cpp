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

#include "cHelper.h"

CHelper::CHelper()
	: api_(std::make_shared<Dominion::Api>())
{
	std::random_device rd;
	rng_ = std::mt19937{ rd() };
}

CHelper& CHelper::instance()
{
	static CHelper instance;

	return instance;
}

std::weak_ptr<Dominion::Api> CHelper::GetAPI() const
{
	return api_;
}

boost::optional<std::string> CHelper::GetFBBuffer(const int handle) const
{
	auto res = FBBuffers_.find(handle);

	if (res != FBBuffers_.end())
		return res->second;

	return boost::none;
}

const int CHelper::RegisterFBBuffer(const std::string& buffer)
{
	std::uniform_int_distribution<> dist(0, INT_MAX);

	const int rng = dist(rng_);

	FBBuffers_.insert(std::make_pair(rng, buffer));

	return rng;
}

const int CHelper::RegisterItem(std::shared_ptr<Dominion::Object> item)
{
	std::uniform_int_distribution<> dist(0, INT_MAX);

	const int rng = dist(rng_);

	container_.insert(std::make_pair(rng, item));

	return rng;
}

void CHelper::UnregisterFBBuffer(const int handle)
{
	if (FBBuffers_.erase(handle) != 1)
		throw new std::exception("Item not removed");
}

void CHelper::UnregisterItem(const int handle)
{
	if (container_.erase(handle) != 1)
		throw new std::exception("Item not removed");
}