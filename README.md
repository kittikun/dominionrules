Dominionrules
=============

Implementation of the Dominion Rules 3.1

http://dominionrules.org/

Tested on the following platforms:
- Win8.1, VS2013
- Ubuntu 14.04, GCC 4.9.2
- FreeBSD 10.1, Clang 3.5

##Build

Files required to build are located under the *build/* folder

You will need:
- C++14
- Boost
- SQLite

###Windows

When building for windows, please define the following environment variables:

BOOST_ROOT

For example:

BOOST_ROOT=C:\boost_1_57_0 

###Linux and BSD


Builds requires CMake to be installed
