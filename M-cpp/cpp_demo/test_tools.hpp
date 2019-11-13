#pragma once
////////////////////////////////////////////////
// DO NOT WORRY ABOUT CODE FROM HERE
////////////////////////////////////////////////

#include <iostream>
#include <iomanip>

namespace utils {

// Length of the test name message
const size_t TESTLENGTH = 100;
const std::string EXTRAMSG= " test";
const char FILLCHAR = '=';

// Beautifully prints test name
// Prints 100 characters centered with test name and the rest filled with '*'
inline void print_test(const std::string& testname)
{
    size_t fillsize = (TESTLENGTH - testname.size() - EXTRAMSG.size()) / 2;
    std::cout << std::setfill(FILLCHAR)
            << std::setw(fillsize)
            << ""
            << std::left
            << std::setfill(FILLCHAR)
            << std::setw(TESTLENGTH - fillsize)
            << testname + EXTRAMSG
            << std::endl
            << std::right;
}

} // namespace utils
