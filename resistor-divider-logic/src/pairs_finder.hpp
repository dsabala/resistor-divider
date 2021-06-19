/**
 * Project: resistor-divider
 * Site: https://github.com/dsabala/resistor-divider
 * License: BSD
 */

#pragma once

#include <cstdint>
#include <vector>
#include <resistor_pair.hpp>

namespace PairsFinder {

void GenerateRatioList(std::vector<ResistorsPair>& ratio_list,
                       const std::vector<std::uint64_t>& val_multipliers,
                       const std::vector<std::uint64_t>& val_serie);

}  // namespace PairsFinder