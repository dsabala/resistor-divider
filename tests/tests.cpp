
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "resistor_divider.h"

#include <array>

namespace res_parser = resistor_divider::code_parser;

TEST_CASE("Resistor class ways of initialising") {
    resistor_divider::Resistor default_resistor;
    CHECK(default_resistor.GetValue() == 0);
    resistor_divider::Resistor sample_resistor(500);
    CHECK(sample_resistor.GetValue() == 500);
    resistor_divider::Resistor sample_resistor_2(470'000'000'000);
    CHECK(sample_resistor_2.GetValue() == 470'000'000'000);
    resistor_divider::Resistor sample_resistor_3("47k2");
    CHECK(sample_resistor_3.GetValue() == 47'200'000);
    resistor_divider::Resistor default_resistor2;
    default_resistor2.SetValue(700);
    CHECK(default_resistor2.GetValue() == 700);
    resistor_divider::Resistor resistor_late_init;
    resistor_late_init.SetValue("1k05");
    CHECK(resistor_late_init.GetValue() == 1'050'000);
}


TEST_CASE("Overloading comparison operators") {
    resistor_divider::Resistor resistor500(500);
    resistor_divider::Resistor resistor700(700);
    resistor_divider::Resistor resistor700_second(700);

    CHECK(resistor700 == resistor700_second);
    CHECK_FALSE(resistor500 == resistor700);
}

TEST_CASE("Resistors pair object construction and comparison") {
    resistor_divider::Resistor resistor_low(100);
    resistor_divider::Resistor resistor_high(900);
    resistor_divider::ResistorsPair example_pair(resistor_low, resistor_high);
    CHECK(example_pair.GetRatio() == 0.1);

    resistor_divider::ResistorsPair example_pair2(200, 800);
    CHECK(example_pair2.GetRatio() == 0.2);

    CHECK(example_pair < example_pair2);
    CHECK_FALSE(example_pair.DivideInHalf());

    resistor_divider::ResistorsPair example_pair3(800, 800);
    CHECK(example_pair3.DivideInHalf());
}

void PrintRatioArray(std::vector<resistor_divider::ResistorsPair>& arr_ref) {
    std::cout << "\n List of available ratios: \n";
    for (auto i = 0; i < arr_ref.size(); ++i) {
        std::cout.precision(5);
        std::cout << "Pair no. " << std::fixed << std::setw(7) << i+1 << " "
                  << "Resistor Low: " << std::fixed << std::setw(7) << arr_ref.at(i).GetResLow().GetValue() << "  "
                  << "Resistor High: " << std::fixed << std::setw(7) << arr_ref.at(i).GetResHigh().GetValue() << "  "
                  << "Ratio: " << std::fixed << arr_ref.at(i).GetRatio() << "\n";
    }
}

void PrintResArray(std::vector<resistor_divider::Resistor>& arr_ref) {
    std::cout << "\n List of available resistors: \n";
    for (auto i = 0; i < arr_ref.size(); ++i) {
        std::cout << "Resistor no. " << i+1 << " value: " << arr_ref.at(i).GetValue() << "  " << "\n";
    }
}

const std::vector<std::uint64_t> val_multipliers{ 1, 10, 100 };
const std::vector<std::uint64_t> val_serie2{ 10, 22, 47 };

TEST_CASE("Generation of available ratio list") { 
    //Generate list
    std::vector<resistor_divider::ResistorsPair> ratio_list;
    resistor_divider::PairsFinder::GenerateRatioList(ratio_list, val_multipliers, val_serie2);
    //PrintRatioArray(ratio_list);
}

TEST_CASE("Extracting the proposed pairs one by one") {
    using namespace resistor_divider;

    std::vector<ResistorsPair> ratio_list;
    ResistorsPair pair1(1, 9);
    ratio_list.push_back(pair1);
    ResistorsPair pair2(1, 4);
    ratio_list.push_back(pair2);
    ResistorsPair pair3(4, 1);
    ratio_list.push_back(pair3);
    ResistorsPair pair4(9, 1);
    ratio_list.push_back(pair4);
    //PrintRatioArray(ratio_list);

    PairsClosest matches;
    CHECK_FALSE(matches.initialised);

    matches.initialised = false;
    PairsFinder::find_next(ratio_list, matches, 0.0);
    REQUIRE((*(matches.latest)).GetRatio() == doctest::Approx(0.1));
    PairsFinder::find_next(ratio_list, matches, 0.0);
    REQUIRE((*(matches.latest)).GetRatio() == doctest::Approx(0.2));
    PairsFinder::find_next(ratio_list, matches, 0.0);
    REQUIRE((*(matches.latest)).GetRatio() == doctest::Approx(0.8));
    PairsFinder::find_next(ratio_list, matches, 0.0);
    REQUIRE((*(matches.latest)).GetRatio() == doctest::Approx(0.9));
    CHECK_FALSE(matches.range_end);
    PairsFinder::find_next(ratio_list, matches, 0.0);
    REQUIRE((*(matches.latest)).GetRatio() == doctest::Approx(0.9));
    CHECK(matches.range_end);

    matches.initialised = false;
    matches.range_end = false;
    PairsFinder::find_next(ratio_list, matches, 0.51);
    CHECK(matches.initialised);
    REQUIRE((*(matches.latest)).GetRatio() == doctest::Approx(0.8));
    PairsFinder::find_next(ratio_list, matches, 0.51);
    REQUIRE((*(matches.latest)).GetRatio() == doctest::Approx(0.2));
    PairsFinder::find_next(ratio_list, matches, 0.51);
    REQUIRE((*(matches.latest)).GetRatio() == doctest::Approx(0.9));
    PairsFinder::find_next(ratio_list, matches, 0.51);
    REQUIRE((*(matches.latest)).GetRatio() == doctest::Approx(0.1));

    matches.initialised = false;
    matches.range_end = false;
    PairsFinder::find_next(ratio_list, matches, 1.0);
    REQUIRE((*(matches.below)).GetRatio() == doctest::Approx(0.9));
    REQUIRE((*(matches.above)).GetRatio() == doctest::Approx(0.9));
    REQUIRE((*(matches.latest)).GetRatio() == doctest::Approx(0.9));
    PairsFinder::find_next(ratio_list, matches, 1.0);
    REQUIRE((*(matches.latest)).GetRatio() == doctest::Approx(0.8));
    PairsFinder::find_next(ratio_list, matches, 1.0);
    REQUIRE((*(matches.latest)).GetRatio() == doctest::Approx(0.2));
    PairsFinder::find_next(ratio_list, matches, 1.0);
    REQUIRE((*(matches.latest)).GetRatio() == doctest::Approx(0.1));
    CHECK_FALSE(matches.range_end);
    PairsFinder::find_next(ratio_list, matches, 1.0);
    REQUIRE((*(matches.latest)).GetRatio() == doctest::Approx(0.1));
    CHECK(matches.range_end);
}

TEST_CASE("Integration of list generation and searching") {
    using namespace resistor_divider;

    std::vector<ResistorsPair> ratio_list;
    std::vector<ResistorsPair> found_pairs_list;
    PairsFinder::GenerateRatioList(ratio_list, val_multipliers, val_serie2);
    PrintRatioArray(ratio_list);

    PairsClosest matches;

    for (int x = 0; (x < 12) && (!matches.range_end); x++){
        PairsFinder::find_next(ratio_list, matches, 0.34);
        found_pairs_list.push_back(*(matches.latest));
    }
    std::sort(found_pairs_list.begin(), found_pairs_list.end());

    PrintRatioArray(found_pairs_list);
}

TEST_CASE("Bom reader") {
    using namespace resistor_divider;
    BomReader bom("bom_example.csv");
    //PrintResArray(bom.GetList());
    //TODO fix this 

    ResistorsPair pair(3300000, 160000000);
    CHECK(bom.CheckIfPossible(pair));

    ResistorsPair pair2(3300000, 160000001);
    CHECK_FALSE(bom.CheckIfPossible(pair2));
}

TEST_CASE("Empty csv or no resistors") {
    using namespace resistor_divider;
    BomReader bom("bom_example_no_res.csv");

    ResistorsPair pair(3300000, 160000000);
    CHECK_FALSE(bom.CheckIfPossible(pair));

    ResistorsPair pair2(3300000, 160000001);
    CHECK_FALSE(bom.CheckIfPossible(pair2));
}