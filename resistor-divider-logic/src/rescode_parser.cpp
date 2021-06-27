// https://github.com/dsabala/resistor-divider
// License: MIT

#include <cassert>
#include <regex>
#include <rescode_parser.hpp>

namespace rescode_parser {

int FindPrefix(std::string const code) {
  int ret = 0;
  std::smatch match;
  std::regex const prefix_regexp(R"(\d+(?=(k|R|M)))");
  if (std::regex_search(code, match, prefix_regexp)) {
    ret = std::stoi(match.str());
  }
  return ret;
}

int FindSuffix(std::string const code) {
  int ret = 0;
  std::smatch match;
  std::regex const suffix_regexp(R"((k|R|M)\d+)");
  if (std::regex_search(code, match, suffix_regexp)) {
    std::string const match_fixed = match.str().erase(0, 1);
    ret = std::stoi(match_fixed);
  }
  return ret;
}

int FindMul(std::string const code) {
  int ret = 0;
  std::smatch match;
  std::regex const letter_regexp(R"(\D)");
  if (std::regex_search(code, match, letter_regexp)) {
    if (match.str() == "R") {
      ret = 1'000;
    } else if (match.str() == "k") {
      ret = 1000'000;
    } else if (match.str() == "M") {
      ret = 1'000'000'000;
    } else {
      assert(false);
    }
  }
  return ret;
}

int FindSuffixDiv(std::string const code) {
  int ret = 1;
  std::smatch match;
  std::regex const suffix_regexp(R"((k|R|M)\d+)");
  if (std::regex_search(code, match, suffix_regexp)) {
    std::string const match_fixed = match.str().erase(0, 1);
    std::size_t lenght = match_fixed.length();
    if (lenght == 1) {
      ret = 10;
    } else if (lenght == 2) {
      ret = 100;
    } else {
      assert(false);
    }
  }
  return ret;
}

std::uint64_t ParseCodeTo_mR(std::string const code) {
  std::uint64_t const prefix = FindPrefix(code);
  std::uint64_t const mul = FindMul(code);
  std::uint64_t const suffix = FindSuffix(code);
  std::uint64_t const suffix_div = FindSuffixDiv(code);
  std::uint64_t const suffix_mul = mul / suffix_div;
  return ((prefix * mul) + (suffix * suffix_mul));
}

}  // namespace rescode_parser