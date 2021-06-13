/**
 * Project: resistor-divider
 * Site: https://github.com/dsabala/resistor-divider
 * License: BSD
 */

#pragma once

namespace parser_code {

int FindPrefix(std::string const code);
int FindSuffix(std::string const code);
int FindMul(std::string const code);
int FindSuffixDiv(std::string const code);
std::uint64_t ParseCodeTo_mR(std::string const code);

}  // namespace parser_code