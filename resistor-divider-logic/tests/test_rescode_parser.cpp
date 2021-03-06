// https://github.com/dsabala/resistor-divider
// License: MIT

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <rescode_parser.hpp>

TEST_CASE("Find resistor code prefix") {
  CHECK(rescode_parser::FindPrefix("1k5") == 1);
  CHECK(rescode_parser::FindPrefix("9k5") == 9);
  CHECK(rescode_parser::FindPrefix("99k5") == 99);
  CHECK(rescode_parser::FindPrefix("470k") == 470);

  CHECK(rescode_parser::FindPrefix(" 9k5") == 9);
  CHECK(rescode_parser::FindPrefix("9k5 ") == 9);
  CHECK(rescode_parser::FindPrefix(" 9k5 ") == 9);

  CHECK(rescode_parser::FindPrefix("0k47") == 0);
  CHECK(rescode_parser::FindPrefix("k47") == 0);
}

TEST_CASE("Ensure other letter than k are discovered too") {
  CHECK(rescode_parser::FindPrefix("1R5") == 1);
  CHECK(rescode_parser::FindPrefix("9M5") == 9);
  CHECK(rescode_parser::FindPrefix("0R47") == 0);
  CHECK(rescode_parser::FindPrefix("M47") == 0);
}

TEST_CASE("Find resistor code suffix") {
  CHECK(rescode_parser::FindSuffix("1k1") == 1);
  CHECK(rescode_parser::FindSuffix("1k9") == 9);
  CHECK(rescode_parser::FindSuffix("1k99") == 99);

  CHECK(rescode_parser::FindSuffix(" 9k5") == 5);
  CHECK(rescode_parser::FindSuffix("9k5 ") == 5);
  CHECK(rescode_parser::FindSuffix(" 9k5 ") == 5);

  CHECK(rescode_parser::FindSuffix("0k47") == 47);
  CHECK(rescode_parser::FindSuffix("k47") == 47);
}

TEST_CASE("Find multiplier") {
  CHECK(rescode_parser::FindMul("1R1") == 1'000);
  CHECK(rescode_parser::FindMul("1k1") == 1'000'000);
  CHECK(rescode_parser::FindMul("1M1") == 1'000'000'000);
}

TEST_CASE("Find suffix divider") {
  CHECK(rescode_parser::FindSuffixDiv("1k1") == 10);
  CHECK(rescode_parser::FindSuffixDiv("3k9") == 10);
  CHECK(rescode_parser::FindSuffixDiv("1k05") == 100);
  CHECK(rescode_parser::FindSuffixDiv("1k99") == 100);
}

TEST_CASE("Finally parse the resistore code") {
  CHECK(rescode_parser::ParseCodeTo_mR("0R01") == 10);
  CHECK(rescode_parser::ParseCodeTo_mR("0R1") == 100);
  CHECK(rescode_parser::ParseCodeTo_mR("0R47") == 470);
  CHECK(rescode_parser::ParseCodeTo_mR("R47") == 470);
  CHECK(rescode_parser::ParseCodeTo_mR("220R") == 220'000);
  CHECK(rescode_parser::ParseCodeTo_mR("k22") == 220'000);
  CHECK(rescode_parser::ParseCodeTo_mR("1k") == 1'000'000);
  CHECK(rescode_parser::ParseCodeTo_mR("1k05") == 1'050'000);
  CHECK(rescode_parser::ParseCodeTo_mR("1k0") == 1'000'000);
  CHECK(rescode_parser::ParseCodeTo_mR("1k12") == 1'120'000);
  CHECK(rescode_parser::ParseCodeTo_mR("47k") == 47'000'000);
  CHECK(rescode_parser::ParseCodeTo_mR("47k2") == 47'200'000);
  CHECK(rescode_parser::ParseCodeTo_mR("470k") == 470'000'000);
  CHECK(rescode_parser::ParseCodeTo_mR("1M0") == 1'000'000'000);
  CHECK(rescode_parser::ParseCodeTo_mR("1M2") == 1'200'000'000);
  CHECK(rescode_parser::ParseCodeTo_mR("1M22") == 1'220'000'000);
  CHECK(rescode_parser::ParseCodeTo_mR("470M0") == 470'000'000'000);
}
