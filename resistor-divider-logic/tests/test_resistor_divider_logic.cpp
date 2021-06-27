/**
 * Project: resistor-divider
 * Site: https://github.com/dsabala/resistor-divider
 * License: BSD
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <resistor-divider-logic/resistor_divider_logic.hpp>

TEST_CASE("Default constructor") {
    ResistorDivider::SearchCriteria criteria;
    CHECK(ResistorDivider::CheckCriteria(criteria));
}

TEST_CASE("Correct serie") {
    ResistorDivider::SearchCriteria criteria;
    criteria.res_e_serie = 96;
    CHECK(ResistorDivider::CheckCriteria(criteria));
}

TEST_CASE("Incorrect serie") {
    ResistorDivider::SearchCriteria criteria;
    criteria.res_e_serie = 7;
    CHECK_FALSE(ResistorDivider::CheckCriteria(criteria));
}

TEST_CASE("Correct ratio") {
    ResistorDivider::SearchCriteria criteria;
    criteria.ratio = 0.000001;
    CHECK(ResistorDivider::CheckCriteria(criteria));
    criteria.ratio = 0;
    CHECK(ResistorDivider::CheckCriteria(criteria));
    criteria.ratio = 1;
    CHECK(ResistorDivider::CheckCriteria(criteria));
}

TEST_CASE("Incorrect ratio") {
    ResistorDivider::SearchCriteria criteria;
    criteria.ratio = 1.12;
    CHECK_FALSE(ResistorDivider::CheckCriteria(criteria));
    criteria.ratio = -5;
    CHECK_FALSE(ResistorDivider::CheckCriteria(criteria));
}
