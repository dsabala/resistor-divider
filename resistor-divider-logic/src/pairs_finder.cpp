/**
 * Project: resistor-divider
 * Site: https://github.com/dsabala/resistor-divider
 * License: BSD
 */

#include <algorithm>
#include <pairs_finder.hpp>

void PairsFinder::GenerateRatioList(
    std::vector<ResistorsPair>& ratio_list,
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