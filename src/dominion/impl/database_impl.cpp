// Copyright(C) 2014 kittikun
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

#include "database_impl.h"

#include "perk_impl.h"

namespace Dominion
{
    DatabaseImpl::DatabaseImpl() :
        dbConnection{nullptr}
    {}

    DatabaseImpl::~DatabaseImpl()
    {
        if (dbConnection != nullptr) {
            sqlite3_close(dbConnection);
            dbConnection = nullptr;
        }
    }

    void DatabaseImpl::ConnectDatabase(boost::filesystem::path path)
    {
        int rc;
        rc = sqlite3_open(path.string().c_str(), &dbConnection);

        if (rc) {
            boost::format err = boost::format("Couldn't open database: %1%") % sqlite3_errmsg(dbConnection);
            throw std::runtime_error(boost::str(err));
        }
    }

    void DatabaseImpl::ExecuteQuery(const std::string& query, SQLiteCallback callback) const
    {
        int rc;
        char*err = nullptr;
        void* ptr = reinterpret_cast<void*>(const_cast<DatabaseImpl*>(this));

        rc = sqlite3_exec(dbConnection, query.c_str(), callback, ptr, &err);

        if (rc) {
            throw std::runtime_error("Query returned with an error");
        }
    }

    uint_fast32_t DatabaseImpl::GetIntValue(const std::string& query) const
    {
        int rc;
        char *err = nullptr;
        uint_fast32_t res;

        auto f = [](void* data, int, char** argv, char**) {
            uint_fast32_t* res = static_cast<uint_fast32_t*>(data);

            *res = boost::lexical_cast<uint_fast32_t>(argv[0]);

            return 0;
        };

        rc = sqlite3_exec(dbConnection, query.c_str(), f, static_cast<void*>(&res), &err);

        if (rc) {
            throw std::runtime_error("Query returned with an error");
        }

        return res;
    }
} // namespace Dominion
