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

int FindSuffixDiv(std::string const code) {
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

std::uint64_t ParseCodeTo_mR(std::string const code) {
	std::uint64_t const prefix = FindPrefix(code);
	std::uint64_t const mul = FindMul(code);
	std::uint64_t const suffix = FindSuffix(code);
	std::uint64_t const suffix_div = FindSuffixDiv(code);
	std::uint64_t const suffix_mul = mul / suffix_div;
	return ((prefix * mul) + (suffix * suffix_mul));
}

} // namespace code_parser

class Resistor {
public:
	Resistor() : value(0) { }
	Resistor(std::uint64_t val) : value(val) { }
	Resistor(std::string val_code) {
		value = code_parser::ParseCodeTo_mR(val_code);
	}

	std::uint64_t GetValue() {
		return value;
	}

	void SetValue(std::uint64_t val) {
		value = val;
	}

	void SetValue(std::string val_code) {
		value = code_parser::ParseCodeTo_mR(val_code);
	}

	bool operator==(const Resistor& second) const {
		bool ret = false;

		if (value == second.value) {
			ret = true;
		}

		return ret;
	}

private:
	std::uint64_t value;
};

class ResistorsPair {
public:
	ResistorsPair(Resistor res_low, Resistor res_high) {
		resistor_low = res_low;
		resistor_high = res_high;
		CalculateRatio();
	}

	ResistorsPair(std::uint64_t res_low, std::uint64_t res_high)
		: resistor_low(res_low), resistor_high(res_high) {
		CalculateRatio();
	}

	double GetRatio() {
		return ratio;
	}

	Resistor GetResLow() {
		return resistor_low;
	}

	Resistor GetResHigh() {
		return resistor_high;
	}

	void CalculateRatio() {
		double res_low = static_cast<double>(resistor_low.GetValue());
		double res_high = static_cast<double>(resistor_high.GetValue());
		ratio = res_low / (res_low + res_high);
	}

	bool operator<(const ResistorsPair& a) const
	{
		return ratio < a.ratio;
	}

private:
	Resistor resistor_low;
	Resistor resistor_high;
	double ratio;
};

void GenerateRatioList(std::vector<ResistorsPair> &ratio_list,
                       std::vector<std::uint64_t> &val_multipliers,
                       std::vector<std::uint64_t> &val_serie) {
	for (auto n = 0; n < val_multipliers.size(); ++n) {
		for (auto i = 0; i < val_serie.size(); ++i) {
			Resistor res1((val_serie.at(i) * val_multipliers.at(n)));
			for (auto z = 0; z < val_multipliers.size(); ++z) {
				for (auto x = 0; x < val_serie.size(); ++x) {
					Resistor res2((val_serie.at(x) * val_multipliers.at(z)));
					ResistorsPair pair(res1, res2);
					ratio_list.push_back(pair);
				}
			}
		}
	}
	std::sort(ratio_list.begin(), ratio_list.end());
}

} // namespace resistor_divider
