// https://github.com/dsabala/resistor-divider
// License: MIT

#include "pairs_finder.hpp"

#include <algorithm>

#include "e_serie_consts.hpp"

std::vector<std::uint64_t> PairsFinder::GenerateSerieVector(int const serie) {
  return GetESerie(serie);
}

std::vector<ResistorsPair> PairsFinder::GenerateRatioList(
    const std::vector<std::uint64_t>& multipliers,
    const std::vector<std::uint64_t>& serie, const std::uint64_t resistance_min,
    const std::uint64_t resistance_max) {
  std::vector<ResistorsPair> ratio_list;
  for (auto r1mul = 0; r1mul < multipliers.size(); ++r1mul) {
    for (auto r1ser = 0; r1ser < serie.size(); ++r1ser) {
      Resistor res1((serie.at(r1ser) * multipliers.at(r1mul)));
      for (auto r2mul = 0; r2mul < multipliers.size(); ++r2mul) {
        for (auto r2ser = 0; r2ser < serie.size(); ++r2ser) {
          Resistor res2((serie.at(r2ser) * multipliers.at(r2mul)));
          if ((res1.GetValue() >= resistance_min) &&
              (res1.GetValue() <= resistance_max) &&
              (res2.GetValue() >= resistance_min) &&
              (res2.GetValue() <= resistance_max) && (res1 != res2)) {
            ResistorsPair pair(res1, res2);
            ratio_list.push_back(pair);
          }
        }
      }
    }
  }

  std::sort(ratio_list.begin(), ratio_list.end());

  return ratio_list;
}

std::vector<ResistorsPair> PairsFinder::GenerateRatioList(
    const int serie, const std::uint64_t resistance_min,
    const std::uint64_t resistance_max) {
  return GenerateRatioList(GetMultipliers(), GenerateSerieVector(serie),
                           resistance_min, resistance_max);
}