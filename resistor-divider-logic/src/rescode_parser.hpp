// https://github.com/dsabala/resistor-divider
// License: MIT

#pragma once

#include <cstdint>
#include <string>

namespace rescode_parser {

int FindPrefix(std::string const code);
int FindSuffix(std::string const code);
int FindMul(std::string const code);
int FindSuffixDiv(std::string const code);
std::uint64_t ParseCodeTo_mR(std::string const code);

}  // namespace rescode_parser