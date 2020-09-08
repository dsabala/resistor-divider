/**
 * Project: Resistor Divider
 * Description: Simple program that helps you look for pairs of resistors for voltage dividers. 
 * Author: Dariusz Sabala
 * License: BSD
 */

#pragma once

#include <regex>

namespace resistor_divider {

namespace code_parser {

int find_prefix(std::string const code) {
	int ret = 0;
	std::smatch prefix_match;
	std::regex const prefix_regexp(R"(\d+(?=k|R|M))");
	if (std::regex_search(code, prefix_match, prefix_regexp)) {
		ret = std::stoi(prefix_match.str());
	}
	return ret;
}

}

}