/**
 * Project: resistor-divider
 * Site: https://github.com/dsabala/resistor-divider
 * License: BSD
 */

#pragma once

#include <resistor-divider-logic/resistor_pair.hpp>
#include <vector>
#include <unordered_set>

namespace ResistorDivider {

constexpr auto kResistanceMin_mR = 0;
constexpr auto kResistanceMax_mR = 100'000'000'000;
constexpr float kCriteriaRatioMin = 0;
constexpr float kCriteriaRadioMax = 1;
const std::unordered_set<int> kCriteriaSeriesAllowes = {
  3, 6, 12, 24, 48, 96, 192
};


struct SearchCriteria {
  float ratio{0.5};
  int res_e_serie{12};
  int results_no{10};
  Resistor res_min{kResistanceMin_mR};
  Resistor res_max{kResistanceMax_mR};
};

struct SearchResults {
  bool criteria_is_correct {true};
  std::vector<ResistorsPair> pairs_list;
};

SearchResults Search(SearchCriteria & criteria);

bool CheckCriteria(SearchCriteria & criteria);

}  // namespace ResistorDivider
