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

#include "style_impl.h"

#include <memory>
#include <boost/lexical_cast.hpp>

#include "classid.h"
#include "database_impl.h"

namespace Dominion
{
	StyleImpl::StyleImpl(const uint_fast32_t id) :
		DataItem(id)
	{}

	int StyleImpl::LoadFromDB(void* data, int argc, char** argv, char** col)
	{
		DatabaseImpl* db = static_cast<DatabaseImpl*>(data);
		std::shared_ptr<StyleImpl> style;

		for (int i = 0; i < argc; ++i) {
			if (argv[i] == nullptr)
				continue;

			if (strcmp(col[i], "Id") == 0) {
				uint_fast32_t id = ClassID_Style + boost::lexical_cast<uint_fast32_t>(argv[i]);
				style = std::make_shared<StyleImpl>(id);
			} else if (strcmp(col[i], "name") == 0) {
				style->name_ = argv[i];
			} else if (strcmp(col[i], "isPriest") == 0) {
				style->archetypes_[ArchetypePriest] = boost::lexical_cast<bool>(argv[i]);
			} else if (strcmp(col[i], "isWitch") == 0) {
				style->archetypes_[ArchetypeWitch] = boost::lexical_cast<bool>(argv[i]);
			} else if (strcmp(col[i], "isBeast") == 0) {
				style->archetypes_[ArchetypeBeast] = boost::lexical_cast<bool>(argv[i]);
			}
		}

		db->AddData<StyleImpl>(style);

		return 0;
	}
} // namespace Dominion