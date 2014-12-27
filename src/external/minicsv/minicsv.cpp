// The MIT License (MIT)
// Minimalistic CSV Streams 1.4
// Copyright (C) 2014, by Wong Shao Voon (shaovoon@yahoo.com)
//
// http://opensource.org/licenses/MIT
//
// version 1.2 : make use of make_shared
// version 1.3 : fixed: to when reading the last line and it does not have linefeed
//               added: skip_1st_line and skip_line functions to ifstream class
// version 1.4 : Removed the use of smart ptr.

#include "minicsv.h"

template<>
csv::ifstream& operator >> (csv::ifstream& istm, std::string& val)
{
	val = istm.get_delimited_str();

	return istm;
}

template<>
csv::ofstream& operator << (csv::ofstream& ostm, const char& val)
{
	if (val == NEWLINE)
	{
		ostm.get_ofstream() << std::endl;

		ostm.set_after_newline(true);
	}
	else
		ostm.get_ofstream() << val;

	return ostm;
}
