// Copyright(C) 2014 kittikun
//
// This program is free software : you can redistribute it and / or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.If not, see <http://www.gnu.org/licenses/>.

#ifndef CEREAL_TYPES_BOOST_UUID_
#define CEREAL_TYPES_BOOST_UUID_

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

namespace cereal
{
    template <class Archive> inline
        void save(Archive& ar, boost::uuids::uuid const& uuid)
    {
        std::string val = boost::lexical_cast<std::string>(uuid);

        ar(val);
        //ar(make_size_tag(static_cast<size_type>(uuid.size())));
        //for (auto it = uuid.begin(), end = uuid.end(); it != end; ++it)
        //	ar(*it);
    }

    template <class Archive> inline
        void load(Archive& ar, boost::uuids::uuid& uuid)
    {
        std::string val;

        ar(val);
        uuid = boost::lexical_cast<boost::uuids::uuid>(val);
        //size_type size;
        //ar(make_size_tag(size));

        //for (auto it = uuid.begin(), end = uuid.end(); it != end; ++it) {
        //	uint_fast8_t val;
        //	ar(val);
        //	*it = val;
        //}
    }
} // namespace cereal

#endif // CEREAL_TYPES_BOOST_UUID_
