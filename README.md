Dominionrules 
=============

![Build Status](https://travis-ci.org/kittikun/dominionrules.svg?branch=develop)

[![Build Status](https://webapi.biicode.com/v1/badges/kittikun/kittikun/dominionrules/master)](https://www.biicode.com/kittikun/dominionrules) 

Implementation of the Dominion Rules 3.1

http://dominionrules.org/

Tested on the following platforms:
- Win8.1, VS2013
- Ubuntu 14.04, GCC 4.9.2
- FreeBSD 10.1, Clang 3.5

##Build

You will need:
- C++14 enabled compiler
- [Boost](http://www.boost.org/)
- [SQLite](http://www.sqlite.org/)
- [Cereal](http://uscilab.github.io/cereal/)

###Windows

When building for windows, please define the following environment variables:

BOOST_ROOT
CEREAL_ROOT
SQLITE_ROOT
GTEST_ROOT

For example:

BOOST_ROOT=C:\boost_1_57_0 

###Linux and BSD

For easier setup it is recommended to use [biicode](https://www.biicode.com/). 

1. bii cpp:configure
1. bii cpp:build

Otherwise builds requires CMake to be installed, files required to build are located under the build/ folder
