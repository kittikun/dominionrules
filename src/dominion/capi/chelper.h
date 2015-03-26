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

#ifndef C_HELPER_H
#define C_HELPER_H

#include <memory>
#include <random>
#include <unordered_map>

#include <dominion/api.h>

#include "../impl/api_impl.h"

class CHelper
{
public:
	CHelper();

	static CHelper& CHelper::instance();

	std::weak_ptr<Dominion::Api> GetAPI() const;

	template<typename T>
	std::weak_ptr<T> GetItem(const int handle) const
	{
		auto res = container_.find(handle);

		if (res != container_.end())
			return std::static_pointer_cast<T>(res->second);

		return std::weak_ptr<T>();
	}

	const int RegisterItem(std::shared_ptr<Dominion::Object>);
	void UnregisterItem(const int);

private:
	std::shared_ptr<Dominion::Api> api_;
	std::unordered_map<int, std::shared_ptr<Dominion::Object>> container_;
	std::mt19937 rng_;
};

#endif // C_HELPER_H