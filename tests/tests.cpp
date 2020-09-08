
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "ResistorDivider.h"

namespace res_parser = resistor_divider::code_parser;

TEST_CASE("Finding resistor code prefix") {
    CHECK(res_parser::find_prefix("1k5") == 1);
    CHECK(res_parser::find_prefix("9k5") == 9);

    CHECK(res_parser::find_prefix(" 9k5") == 9);
    CHECK(res_parser::find_prefix("9k5 ") == 9);
    CHECK(res_parser::find_prefix(" 9k5 ") == 9);

    CHECK(res_parser::find_prefix("0k47") == 0);
    CHECK(res_parser::find_prefix("k47") == 0);
}

TEST_CASE("Ensuring other letter than k are discovered too") {
    CHECK(res_parser::find_prefix("1R5") == 1);
    CHECK(res_parser::find_prefix("9M5") == 9);
    CHECK(res_parser::find_prefix("0R47") == 0);
    CHECK(res_parser::find_prefix("M47") == 0);
}