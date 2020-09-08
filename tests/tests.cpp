
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "ResistorDivider.h"

namespace res_parser = resistor_divider::code_parser;

TEST_CASE("Find resistor code prefix") {
    CHECK(res_parser::find_prefix("1k5") == 1);
    CHECK(res_parser::find_prefix("9k5") == 9);
    CHECK(res_parser::find_prefix("99k5") == 99);
    CHECK(res_parser::find_prefix("470k") == 470);

    CHECK(res_parser::find_prefix(" 9k5") == 9);
    CHECK(res_parser::find_prefix("9k5 ") == 9);
    CHECK(res_parser::find_prefix(" 9k5 ") == 9);

    CHECK(res_parser::find_prefix("0k47") == 0);
    CHECK(res_parser::find_prefix("k47") == 0);
}

TEST_CASE("Ensure other letter than k are discovered too") {
    CHECK(res_parser::find_prefix("1R5") == 1);
    CHECK(res_parser::find_prefix("9M5") == 9);
    CHECK(res_parser::find_prefix("0R47") == 0);
    CHECK(res_parser::find_prefix("M47") == 0);
}

TEST_CASE("Find resistor code suffix") {
    CHECK(res_parser::find_suffix("1k1") == 1);
    CHECK(res_parser::find_suffix("1k9") == 9);
    CHECK(res_parser::find_suffix("1k99") == 99);

    CHECK(res_parser::find_suffix(" 9k5") == 5);
    CHECK(res_parser::find_suffix("9k5 ") == 5);
    CHECK(res_parser::find_suffix(" 9k5 ") == 5);

    CHECK(res_parser::find_suffix("0k47") == 47);
    CHECK(res_parser::find_suffix("k47") == 47);
}

TEST_CASE("Find multiplier") {
    CHECK(res_parser::find_mul("1R1") == 1'000);
    CHECK(res_parser::find_mul("1k1") == 1'000'000);
    CHECK(res_parser::find_mul("1M1") == 1'000'000'000);
}

TEST_CASE("Find suffix divider") {
    CHECK(res_parser::find_suffix_div("1k1") == 10);
    CHECK(res_parser::find_suffix_div("3k9") == 10);
    CHECK(res_parser::find_suffix_div("1k05") == 100);
    CHECK(res_parser::find_suffix_div("1k99") == 100);
}

TEST_CASE("Finally parse the resistore code") {
    CHECK(res_parser::parse_code_2_mr("0R01")  ==              10);
    CHECK(res_parser::parse_code_2_mr("0R1")   ==             100);
    CHECK(res_parser::parse_code_2_mr("0R47")  ==             470);
    CHECK(res_parser::parse_code_2_mr("R47")   ==             470);
    CHECK(res_parser::parse_code_2_mr("220R")  ==         220'000);
    CHECK(res_parser::parse_code_2_mr("k22")   ==         220'000);
    CHECK(res_parser::parse_code_2_mr("1k")    ==       1'000'000);
    CHECK(res_parser::parse_code_2_mr("1k05")  ==       1'050'000);
    CHECK(res_parser::parse_code_2_mr("1k0")   ==       1'000'000);
    CHECK(res_parser::parse_code_2_mr("1k12")  ==       1'120'000);
    CHECK(res_parser::parse_code_2_mr("47k")   ==      47'000'000);
    CHECK(res_parser::parse_code_2_mr("47k2")  ==      47'200'000);
    CHECK(res_parser::parse_code_2_mr("470k")  ==     470'000'000);
    CHECK(res_parser::parse_code_2_mr("1M0")   ==   1'000'000'000);
    CHECK(res_parser::parse_code_2_mr("1M2")   ==   1'200'000'000);
    CHECK(res_parser::parse_code_2_mr("1M22")  ==   1'220'000'000);
    CHECK(res_parser::parse_code_2_mr("470M0") == 470'000'000'000);
}