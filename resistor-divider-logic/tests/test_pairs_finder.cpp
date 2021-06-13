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
  // clang-format off
  std::vector<ResistorsPair> ratio_list_expected{
    {220,  4700},
    {220,  2200},
    {470,  4700},
    {470,  2200},
    {220,  470},
    {2200, 4700},
    {220,  220},
    {470,  470},
    {2200, 2200},
    {4700, 4700},
    {470,  220},
    {4700, 2200},
    {2200, 470},
    {2200, 220},
    {4700, 470},
    {4700, 220}
  };
  // clang-format on
  std::vector<ResistorsPair> ratio_list_gen;
  PairsFinder::GenerateRatioList(ratio_list_gen, val_multipliers, val_serie2);
  CHECK(ratio_list_expected == ratio_list_gen);
}