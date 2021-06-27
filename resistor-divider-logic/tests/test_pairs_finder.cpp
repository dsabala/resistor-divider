// https://github.com/dsabala/resistor-divider
// License: MIT

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <pairs_finder.hpp>
#include <vector>

TEST_CASE("Serie list generation") {
  const std::vector<std::uint64_t> serie_expected{10, 15, 22, 33, 47, 68};
  std::vector<std::uint64_t> serie = PairsFinder::GenerateSerieVector(6);
  CHECK(serie_expected == serie);
}

TEST_CASE("Pairs list generation - core") {
  const std::vector<std::uint64_t> multipliers{10, 100};
  const std::vector<std::uint64_t> serie{22, 47};
  // clang-format off
  std::vector<ResistorsPair> ratio_list_expected{
    {220,  4700},
    {220,  2200},
    {470,  4700},
    {470,  2200},
    {220,  470},
    {2200, 4700},
    {470,  220},
    {4700, 2200},
    {2200, 470},
    {2200, 220},
    {4700, 470},
    {4700, 220}
  };
  // clang-format on
  std::vector<ResistorsPair> ratio_list_gen;
  ratio_list_gen = PairsFinder::GenerateRatioList(multipliers, serie);
  CHECK(ratio_list_expected == ratio_list_gen);
}

TEST_CASE("Pairs list generation - usage") {
  // clang-format off
  std::vector<ResistorsPair> ratio_list_expected{
    {100,  470},
    {100,  220},
    {220,  470},
    {470,  220},
    {220,  100},
    {470,  100}
  };
  // clang-format on
  std::vector<ResistorsPair> ratio_list_gen;
  ratio_list_gen = PairsFinder::GenerateRatioList(3, 100, 470);
  CHECK(ratio_list_expected == ratio_list_gen);
}