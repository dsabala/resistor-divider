// https://github.com/dsabala/resistor-divider
// License: MIT

#pragma once

#include <cstdint>
#include <resistor-divider-logic/resistor_divider_logic.hpp>
#include <resistor-divider-logic/resistor_pair.hpp>
#include <vector>

namespace PairsFinder {

std::vector<std::uint64_t> GenerateSerieVector(int const serie);

std::vector<ResistorsPair> GenerateRatioList(
    const std::vector<std::uint64_t>& val_multipliers,
    const std::vector<std::uint64_t>& val_serie,
    const std::uint64_t resistance_min = ResistorDivider::kResistanceMin_mR,
    const std::uint64_t resistance_max = ResistorDivider::kResistanceMax_mR);

std::vector<ResistorsPair> GenerateRatioList(
    const int serie, const std::uint64_t resistance_min,
    const std::uint64_t resistance_max);



}  // namespace PairsFinder