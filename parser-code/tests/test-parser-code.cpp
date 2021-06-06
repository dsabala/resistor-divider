/**
 * Project: resistor-divider
 * Site: https://github.com/dsabala/resistor-divider
 * License: BSD
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include<doctest/doctest.h>
#include<parser-code.hpp>

TEST_CASE("Find resistor code prefix") {
    CHECK(parser_code::FindPrefix("1k5") == 1);
    CHECK(parser_code::FindPrefix("9k5") == 9);
    CHECK(parser_code::FindPrefix("99k5") == 99);
    CHECK(parser_code::FindPrefix("470k") == 470);

    CHECK(parser_code::FindPrefix(" 9k5") == 9);
    CHECK(parser_code::FindPrefix("9k5 ") == 9);
    CHECK(parser_code::FindPrefix(" 9k5 ") == 9);

    CHECK(parser_code::FindPrefix("0k47") == 0);
    CHECK(parser_code::FindPrefix("k47") == 0);
}

TEST_CASE("Ensure other letter than k are discovered too") {
    CHECK(parser_code::FindPrefix("1R5") == 1);
    CHECK(parser_code::FindPrefix("9M5") == 9);
    CHECK(parser_code::FindPrefix("0R47") == 0);
    CHECK(parser_code::FindPrefix("M47") == 0);
}

TEST_CASE("Find resistor code suffix") {
    CHECK(parser_code::FindSuffix("1k1") == 1);
    CHECK(parser_code::FindSuffix("1k9") == 9);
    CHECK(parser_code::FindSuffix("1k99") == 99);

    CHECK(parser_code::FindSuffix(" 9k5") == 5);
    CHECK(parser_code::FindSuffix("9k5 ") == 5);
    CHECK(parser_code::FindSuffix(" 9k5 ") == 5);

    CHECK(parser_code::FindSuffix("0k47") == 47);
    CHECK(parser_code::FindSuffix("k47") == 47);
}

TEST_CASE("Find multiplier") {
    CHECK(parser_code::FindMul("1R1") == 1'000);
    CHECK(parser_code::FindMul("1k1") == 1'000'000);
    CHECK(parser_code::FindMul("1M1") == 1'000'000'000);
}

TEST_CASE("Find suffix divider") {
    CHECK(parser_code::FindSuffixDiv("1k1") == 10);
    CHECK(parser_code::FindSuffixDiv("3k9") == 10);
    CHECK(parser_code::FindSuffixDiv("1k05") == 100);
    CHECK(parser_code::FindSuffixDiv("1k99") == 100);
}

TEST_CASE("Finally parse the resistore code") {
    CHECK(parser_code::ParseCodeTo_mR("0R01")  ==              10);
    CHECK(parser_code::ParseCodeTo_mR("0R1")   ==             100);
    CHECK(parser_code::ParseCodeTo_mR("0R47")  ==             470);
    CHECK(parser_code::ParseCodeTo_mR("R47")   ==             470);
    CHECK(parser_code::ParseCodeTo_mR("220R")  ==         220'000);
    CHECK(parser_code::ParseCodeTo_mR("k22")   ==         220'000);
    CHECK(parser_code::ParseCodeTo_mR("1k")    ==       1'000'000);
    CHECK(parser_code::ParseCodeTo_mR("1k05")  ==       1'050'000);
    CHECK(parser_code::ParseCodeTo_mR("1k0")   ==       1'000'000);
    CHECK(parser_code::ParseCodeTo_mR("1k12")  ==       1'120'000);
    CHECK(parser_code::ParseCodeTo_mR("47k")   ==      47'000'000);
    CHECK(parser_code::ParseCodeTo_mR("47k2")  ==      47'200'000);
    CHECK(parser_code::ParseCodeTo_mR("470k")  ==     470'000'000);
    CHECK(parser_code::ParseCodeTo_mR("1M0")   ==   1'000'000'000);
    CHECK(parser_code::ParseCodeTo_mR("1M2")   ==   1'200'000'000);
    CHECK(parser_code::ParseCodeTo_mR("1M22")  ==   1'220'000'000);
    CHECK(parser_code::ParseCodeTo_mR("470M0") == 470'000'000'000);
}
