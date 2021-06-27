// https://github.com/dsabala/resistor-divider
// License: MIT

#pragma once

#include <cstdint>
#include <string>

class Resistor {
 public:
  constexpr Resistor() {}
  constexpr Resistor(std::uint64_t const val) : value(val) {}
  Resistor(std::string const res_code) {}

  constexpr std::uint64_t GetValue() { return value; }

  constexpr void SetValue(std::uint64_t val) { value = val; }

  constexpr bool operator==(const Resistor& second) const {
    return value == second.value;
  }

  constexpr bool operator!=(const Resistor& second) const {
    return value != second.value;
  }

  constexpr bool operator<(const Resistor& a) const { return value < a.value; }

  constexpr bool operator>(const Resistor& a) const { return value > a.value; }

 private:
  std::uint64_t value{0};
};

class ResistorsPair {
 public:
  constexpr ResistorsPair() : resistor_low(0), resistor_high(0), ratio(0) {}

  constexpr ResistorsPair(Resistor const res_low, Resistor const res_high)
      : resistor_low(res_low), resistor_high(res_high), ratio(0) {
    CalculateRatio();
  }

  constexpr ResistorsPair(std::uint64_t res_low, std::uint64_t res_high)
      : resistor_low(res_low), resistor_high(res_high), ratio(0) {
    CalculateRatio();
  }

  constexpr double GetRatio() { return ratio; }

  constexpr Resistor GetResLow() { return resistor_low; }

  constexpr Resistor GetResHigh() { return resistor_high; }

  constexpr bool DividesInHalf() { return ratio == 0.5; }

  constexpr void CalculateRatio() {
    double res_low = static_cast<double>(resistor_low.GetValue());
    double res_high = static_cast<double>(resistor_high.GetValue());
    ratio = res_low / (res_low + res_high);
  }

  constexpr bool operator==(const ResistorsPair& a) const {
    return ratio == a.ratio;
  }

  constexpr bool operator<(const ResistorsPair& a) const {
    return ratio < a.ratio;
  }

  constexpr bool operator>(const ResistorsPair& a) const {
    return ratio > a.ratio;
  }

 private:
  Resistor resistor_low;
  Resistor resistor_high;
  double ratio;
};