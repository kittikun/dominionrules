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

#ifndef DATABASE_IMPL
#define DATABASE_IMPL

#include <memory>
#include <tuple>
#include <map>
#include <unordered_map>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/functional/hash.hpp>
#include <boost/filesystem.hpp>
#include <sqlite3.h>

#include "dataitem.h"
#include "classid_utility.h"

namespace Dominion
{
	typedef int(*SQLiteCallback)(void*, int, char**, char**);

	class DatabaseImpl : public std::enable_shared_from_this < DatabaseImpl >
	{
		DatabaseImpl(const DatabaseImpl&) = delete;
		DatabaseImpl& operator=(const DatabaseImpl&) = delete;
		DatabaseImpl(DatabaseImpl&&) = delete;
		DatabaseImpl& operator=(DatabaseImpl&&) = delete;

	public:
		DatabaseImpl();
		~DatabaseImpl();

		void OpenDatabaseFromFile(boost::filesystem::path);
		void OpenDatabaseFromMemory();

		template <typename T>
		void AddData(std::shared_ptr<typename ClassIDUtility<T>::ImplType> data)
		{
			std::shared_ptr<DataItem> tmp = std::static_pointer_cast<DataItem>(data);

			tmp->db_ = shared_from_this();
			ClassIDUtility<T>::set_next(tmp->guid());
			database_.insert(std::make_pair(tmp->guid(), tmp));
		}

		template <typename T>
		std::shared_ptr<T> Get(uint_fast32_t guid) const
		{
			return std::static_pointer_cast<T>(database_.find(guid)->second);
		}

		template <typename T>
		std::vector<std::shared_ptr<T>> GetList(const std::string& query) const
		{
			typedef std::unordered_map<uint_fast32_t, std::shared_ptr<DataItem>> DictionaryType;
			typedef std::vector <std::shared_ptr<T>> ResultType;
			typedef std::tuple<const DictionaryType&, ResultType&> TupleType;

			int rc;

			ResultType res;

			// lambda with capture cannot be passed as __cdecl so we have to resort to tuple usage
			TupleType tuple = std::tie(database_, res);

			auto f = [](void* data, int argc, char** argv, char**) {
				TupleType* tuple = static_cast<TupleType*>(data);

				for (int i = 0; i < argc; ++i) {
					int index = ClassIDUtility<T>::ClassIDFromType() + boost::lexical_cast<int>(argv[i]);
					std::get<1>(*tuple).push_back(std::static_pointer_cast<T>(std::get<0>(*tuple).at(index)));
				}

				return 0;
			};

			rc = sqlite3_exec(db_, query.c_str(), f, static_cast<void*>(&tuple), nullptr);

			if (rc) {
				throw std::runtime_error("Query returned with an error");
			}

			return res;
		}

		uint_fast32_t GetIntValue(const std::string& query) const;

		void ExecuteQuery(const std::string&, SQLiteCallback) const;

	private:
		std::unordered_map<uint_fast32_t, std::shared_ptr<DataItem>> database_;
		sqlite3* db_;
		uint_fast32_t version_;
	};
} // namespace Dominion

#endif // DATABASE_IMPL
