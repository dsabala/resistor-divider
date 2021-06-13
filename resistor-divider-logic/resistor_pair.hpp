/**
 * Project: resistor-divider
 * Site: https://github.com/dsabala/resistor-divider
 * License: BSD
 */

#pragma once

#include <cstdint>
#include <string>
#include <rescode_parser.hpp>

class Resistor {
public:
	constexpr Resistor() : value(0) { }
	constexpr Resistor(std::uint64_t val) : value(val) { }
	Resistor(std::string val_code) {
		value = rescode_parser::ParseCodeTo_mR(val_code);
	}

	constexpr std::uint64_t GetValue() {
		return value;
	}

	constexpr void SetValue(std::uint64_t val) {
		value = val;
	}

	void SetValue(std::string val_code) {
		value = rescode_parser::ParseCodeTo_mR(val_code);
	}

	bool operator==(const Resistor& second) const {
		bool ret = false;

		if (value == second.value) {
			ret = true;
		}

		return ret;
	}

	constexpr bool operator<(const Resistor& a) const
	{
		return value < a.value;
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

	constexpr double GetRatio() {
		return ratio;
	}

	constexpr Resistor GetResLow() {
		return resistor_low;
	}

	constexpr Resistor GetResHigh() {
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