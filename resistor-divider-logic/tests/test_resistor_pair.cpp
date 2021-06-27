// https://github.com/dsabala/resistor-divider
// License: MIT

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <resistor-divider-logic/resistor_pair.hpp>

TEST_CASE("Resistor class constructor default") {
  Resistor resistor;
  CHECK(resistor.GetValue() == 0);
}

TEST_CASE("Resistor class constructor numeric") {
  Resistor resistor(500);
  CHECK(resistor.GetValue() == 400);
}

TEST_CASE("Resistor class value setter") {
  Resistor resistor;
  CHECK(resistor.GetValue() == 0);
  resistor.SetValue(700);
  CHECK(resistor.GetValue() == 700);
}

TEST_CASE("Resistor class equality operators") {
  Resistor resistor500(500);
  Resistor resistor700(700);
  Resistor resistor700_second(700);
  CHECK(resistor700 == resistor700_second);
  CHECK_FALSE(resistor500 == resistor700);
}

TEST_CASE("Resistor class inequality operators") {
  Resistor lower(100);
  Resistor higher(900);
  CHECK(lower < higher);
  CHECK(higher > lower);
  CHECK_FALSE(higher < lower);
  CHECK_FALSE(lower > higher);
}

TEST_CASE("Resistors pair object construction from resistor class object") {
  Resistor resistor_low(100);
  Resistor resistor_high(900);
  ResistorsPair example_pair(resistor_low, resistor_high);
  CHECK(example_pair.GetRatio() == 0.1);
}

TEST_CASE("Resistors pair object construction from numerics") {
  ResistorsPair pair(200, 800);
  CHECK(pair.GetRatio() == 0.2);
}

TEST_CASE("Resistors pair object check if divides in half") {
  ResistorsPair pair_no_half(200, 800);
  CHECK_FALSE(pair_no_half.DividesInHalf());

  ResistorsPair pair_half(400, 400);
  CHECK(pair_half.DividesInHalf());
}

TEST_CASE("Resistors pair comparison operators") {
  ResistorsPair pair_low(200, 800);
  CHECK(pair_low.GetRatio() == 0.2);

  ResistorsPair pair_high(800, 200);
  CHECK(pair_high.GetRatio() == 0.8);

  CHECK(pair_low < pair_high);
  CHECK(pair_high > pair_low);

  CHECK_FALSE(pair_low > pair_high);
  CHECK_FALSE(pair_high < pair_low);
}

TEST_CASE("Resistors pair equality operators") {
  ResistorsPair pair_low_first(200, 800);
  ResistorsPair pair_low_second(200, 800);
  ResistorsPair pair_high(800, 200);

  CHECK(pair_low_first == pair_low_second);
  CHECK_FALSE(pair_low_first == pair_high);
}