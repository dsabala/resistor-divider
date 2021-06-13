/**
 * Project: resistor-divider
 * Site: https://github.com/dsabala/resistor-divider
 * License: BSD
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <pairs_finder.hpp>
#include <vector>

TEST_CASE("Pairs list generation") {
  const std::vector<std::uint64_t> val_multipliers{10, 100};
  const std::vector<std::uint64_t> val_serie2{22, 47};
  std::vector<ResistorsPair> ratio_list_expected{};
  std::vector<ResistorsPair> ratio_list_gen;
  PairsFinder::GenerateRatioList(ratio_list_gen, val_multipliers, val_serie2);
  CHECK(ratio_list_expected == ratio_list_gen);
}