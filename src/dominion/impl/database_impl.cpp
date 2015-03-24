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

#include "database_impl.h"
#include "database_source.h"

#include "perk_impl.h"

namespace Dominion
{
	DatabaseImpl::DatabaseImpl() :
		db_{ nullptr },
		version_(1)
	{}

	DatabaseImpl::~DatabaseImpl()
	{
		if (db_ != nullptr) {
			sqlite3_close(db_);
			db_ = nullptr;
		}
	}

	void DatabaseImpl::OpenDatabaseFromFile(boost::filesystem::path path)
	{
		int rc;
		rc = sqlite3_open(path.string().c_str(), &db_);

		if (rc) {
			boost::format err = boost::format("Couldn't open database: %1%") % sqlite3_errmsg(db_);
			throw std::runtime_error(boost::str(err));
		}
	}

	void DatabaseImpl::OpenDatabaseFromMemory()
	{
		int rc;
		rc = sqlite3_open(":memory:", &db_);

		if (rc) {
			boost::format err = boost::format("Couldn't open database: %1%") % sqlite3_errmsg(db_);
			throw std::runtime_error(boost::str(err));
		}

		rc = sqlite3_exec(db_, reinterpret_cast<const char*>(dominionDB_sql), nullptr, nullptr, nullptr);

		if (rc) {
			throw std::runtime_error("Query returned with an error");
		}
	}

	void DatabaseImpl::ExecuteQuery(const std::string& query, SQLiteCallback callback) const
	{
		int rc;
		void* ptr = reinterpret_cast<void*>(const_cast<DatabaseImpl*>(this));

		rc = sqlite3_exec(db_, query.c_str(), callback, ptr, nullptr);

		if (rc) {
			throw std::runtime_error("Query returned with an error");
		}
	}

	uint_fast32_t DatabaseImpl::GetIntValue(const std::string& query) const
	{
		int rc;
		uint_fast32_t res;

		auto f = [](void* data, int, char** argv, char**) {
			uint_fast32_t* res = static_cast<uint_fast32_t*>(data);

			*res = boost::lexical_cast<uint_fast32_t>(argv[0]);

			return 0;
		};

		rc = sqlite3_exec(db_, query.c_str(), f, static_cast<void*>(&res), nullptr);

		if (rc) {
			throw std::runtime_error("Query returned with an error");
		}

		return res;
	}
} // namespace Dominion