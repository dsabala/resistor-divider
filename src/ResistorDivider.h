/**
 * Project: Resistor Divider
 * Description: Simple program that helps you look for pairs of resistors for voltage dividers. 
 * Author: Dariusz Sabala
 * License: BSD
 */

#pragma once

#include <regex>
#include <cassert>

namespace resistor_divider {

namespace code_parser {

int find_prefix(std::string const code) {
	int ret = 0;
	std::smatch match;
	std::regex const prefix_regexp(R"(\d+(?=(k|R|M)))");
	if (std::regex_search(code, match, prefix_regexp)) {
		ret = std::stoi(match.str());
	}
	return ret;
}

int find_suffix(std::string const code) {
	int ret = 0;
	std::smatch match;
	std::regex const suffix_regexp(R"((k|R|M)\d+)");
	if (std::regex_search(code, match, suffix_regexp)) {
		std::string const match_fixed = match.str().erase(0, 1);
		ret = std::stoi(match_fixed);
	}
	return ret;
}

int find_mul(std::string const code) {
	int ret = 0;
	std::smatch match;
	std::regex const letter_regexp(R"(\D)");
	if (std::regex_search(code, match, letter_regexp)) {
		if (match.str() == "R") {
			ret = 1'000;
		}else if (match.str() == "k") {
			ret = 1000'000;
		}
		else if (match.str() == "M") {
			ret = 1'000'000'000;
		}else {
			assert(false);
		}
	}
	return ret;
}

int find_suffix_div(std::string const code) {
	int ret = 1;
	std::smatch match;
	std::regex const suffix_regexp(R"((k|R|M)\d+)");
	if (std::regex_search(code, match, suffix_regexp)) {
		std::string const match_fixed = match.str().erase(0, 1);
		std::size_t lenght = match_fixed.length();
		if (lenght == 1) {
			ret = 10;
		}else if (lenght == 2) {
			ret = 100;
		}else {
			assert(false);
		}
	}
	return ret;
}

std::uint64_t parse_code_2_mr(std::string const code) {
	std::uint64_t const prefix = find_prefix(code);
	std::uint64_t const mul = find_mul(code);
	std::uint64_t const suffix = find_suffix(code);
	std::uint64_t const suffix_div = find_suffix_div(code);
	std::uint64_t const suffix_mul = mul / suffix_div;
	return ((prefix * mul) + (suffix * suffix_mul));
}

} // namespace code_parser

} // namespace resistor_divider
