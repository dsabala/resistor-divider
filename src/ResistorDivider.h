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
	constexpr Resistor() : value(0) { }
	constexpr Resistor(std::uint64_t val) : value(val) { }
	Resistor(std::string val_code) {
		value = code_parser::ParseCodeTo_mR(val_code);
	}

	constexpr std::uint64_t GetValue() {
		return value;
	}

	constexpr void SetValue(std::uint64_t val) {
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
	constexpr ResistorsPair() : resistor_low(0), resistor_high(0), ratio(0) { }

	constexpr ResistorsPair(Resistor res_low, Resistor res_high)
		: resistor_low(0), resistor_high(0), ratio(0) {
		resistor_low = res_low;
		resistor_high = res_high;
		CalculateRatio();
	}

	constexpr ResistorsPair(std::uint64_t res_low, std::uint64_t res_high)
		: resistor_low(res_low), resistor_high(res_high), ratio(0) {
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

	constexpr bool DivideInHalf() {
		bool ret = false;
		if (ratio == 0.5) {
			ret = true;
		}
		return ret;
	}

	constexpr void CalculateRatio() {
		double res_low = static_cast<double>(resistor_low.GetValue());
		double res_high = static_cast<double>(resistor_high.GetValue());
		ratio = res_low / (res_low + res_high);
	}

	constexpr bool operator<(const ResistorsPair& a) const
	{
		return ratio < a.ratio;
	}

private:
	Resistor resistor_low;
	Resistor resistor_high;
	double ratio;
};

class PairsFinder {
public:
	PairsFinder() : pairs() {
		GenerateRatioList(pairs, multipliers_values, serie_e192_values);
	}

	static void GenerateRatioList(std::vector<ResistorsPair>& ratio_list,
		const std::vector<std::uint64_t>& val_multipliers,
		const std::vector<std::uint64_t>& val_serie) {
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

	static void Find(const std::vector<ResistorsPair>& ratio_list,
		             std::vector<ResistorsPair>& results,
		             const int results_number,
		             const double desired_ratio) {

	}

    static std::vector<ResistorsPair>::iterator
    find_match(std::vector<ResistorsPair> &ratio_list,
               const double desired_ratio) {
		std::vector<ResistorsPair>::iterator element = ratio_list.begin();
		while (element != ratio_list.end()) {
			if ((*element).GetRatio() > desired_ratio) {
				break;
			}
			element++;
		}
		return element;
	}

private:
	std::vector<ResistorsPair> pairs;

	std::vector<std::uint64_t> const multipliers_values
	{ 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000 };

	std::vector<std::uint64_t> const serie_e192_values
	{ 100, 101, 102, 104, 105, 106, 107, 109, 110, 111, 113, 114, 115, 117, 118, 120,
	  121, 123, 124, 126, 127, 129, 130, 132, 133, 135, 137, 138, 140, 142, 143, 145,
	  147, 149, 150, 152, 154, 156, 158, 160, 162, 164, 165, 167, 169, 172, 174, 176,
	  178, 180, 182, 184, 187, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
	  215, 218, 221, 223, 226, 229, 232, 234, 237, 240, 243, 246, 249, 252, 255, 258,
	  261, 264, 267, 271, 274, 277, 280, 284, 287, 291, 294, 298, 301, 305, 309, 312,
	  316, 320, 324, 328, 332, 336, 340, 344, 348, 352, 357, 361, 365, 370, 374, 379,
	  383, 388, 392, 397, 402, 407, 412, 417, 422, 427, 432, 437, 442, 448, 453, 459,
	  464, 470, 475, 481, 487, 493, 499, 505, 511, 517, 523, 530, 536, 542, 549, 556,
	  562, 569, 576, 583, 590, 597, 604, 612, 619, 626, 634, 642, 649, 657, 665, 673,
	  681, 690, 698, 706, 715, 723, 732, 741, 750, 759, 768, 777, 787, 796, 806, 816,
	  825, 835, 845, 856, 866, 876, 887, 898, 909, 920, 931, 942, 953, 965, 976, 988 };
};

} // namespace resistor_divider
