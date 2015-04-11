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

#include <fstream>
#include <memory>
#include <boost/format.hpp>

#include <dominion/api.h>
#include <dominion/character/style.h>
#include <dominion/core/database.h>

void DoStyles(const std::shared_ptr<Dominion::DataBase>& db)
{
	std::ofstream out("styles.csv");
	auto styles = db->GetStyles();

	out << "Id, Sprite" << std::endl;

	for (auto style : styles) {
		boost::format fmt = boost::format("%1%, %2%") % style->guid() % style->name();
		out << boost::str(fmt) << std::endl;
	}

	out.close();
}

int main(int, char**)
{
	auto api = std::make_shared<Dominion::Api>();

	api->InitializeFromMemory();

	auto db = api->GetDatabase();

	DoStyles(db);
}
