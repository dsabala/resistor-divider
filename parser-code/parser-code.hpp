/**
 * Project: Resistor Divider
 * Description: Simple program that helps you look for pairs of resistors for voltage dividers. 
 * Author: Dariusz Sabala
 * License: BSD
 */

#pragma once

#include <regex>
#include <cassert>
#include <cmath>

namespace resistor_divider {

namespace code_parser {

int FindPrefix(std::string const code);

int FindSuffix(std::string const code);

int FindMul(std::string const code);

int FindSuffixDiv(std::string const code);

std::uint64_t ParseCodeTo_mR(std::string const code);

}

}