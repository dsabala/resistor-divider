
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "ResistorDivider.h"

#include <array>

namespace res_parser = resistor_divider::code_parser;

TEST_CASE("Find resistor code prefix") {
    CHECK(res_parser::FindPrefix("1k5") == 1);
    CHECK(res_parser::FindPrefix("9k5") == 9);
    CHECK(res_parser::FindPrefix("99k5") == 99);
    CHECK(res_parser::FindPrefix("470k") == 470);

    CHECK(res_parser::FindPrefix(" 9k5") == 9);
    CHECK(res_parser::FindPrefix("9k5 ") == 9);
    CHECK(res_parser::FindPrefix(" 9k5 ") == 9);

    CHECK(res_parser::FindPrefix("0k47") == 0);
    CHECK(res_parser::FindPrefix("k47") == 0);
}

TEST_CASE("Ensure other letter than k are discovered too") {
    CHECK(res_parser::FindPrefix("1R5") == 1);
    CHECK(res_parser::FindPrefix("9M5") == 9);
    CHECK(res_parser::FindPrefix("0R47") == 0);
    CHECK(res_parser::FindPrefix("M47") == 0);
}

TEST_CASE("Find resistor code suffix") {
    CHECK(res_parser::FindSuffix("1k1") == 1);
    CHECK(res_parser::FindSuffix("1k9") == 9);
    CHECK(res_parser::FindSuffix("1k99") == 99);

    CHECK(res_parser::FindSuffix(" 9k5") == 5);
    CHECK(res_parser::FindSuffix("9k5 ") == 5);
    CHECK(res_parser::FindSuffix(" 9k5 ") == 5);

    CHECK(res_parser::FindSuffix("0k47") == 47);
    CHECK(res_parser::FindSuffix("k47") == 47);
}

TEST_CASE("Find multiplier") {
    CHECK(res_parser::FindMul("1R1") == 1'000);
    CHECK(res_parser::FindMul("1k1") == 1'000'000);
    CHECK(res_parser::FindMul("1M1") == 1'000'000'000);
}

TEST_CASE("Find suffix divider") {
    CHECK(res_parser::FindSuffixDiv("1k1") == 10);
    CHECK(res_parser::FindSuffixDiv("3k9") == 10);
    CHECK(res_parser::FindSuffixDiv("1k05") == 100);
    CHECK(res_parser::FindSuffixDiv("1k99") == 100);
}

TEST_CASE("Finally parse the resistore code") {
    CHECK(res_parser::ParseCodeTo_mR("0R01")  ==              10);
    CHECK(res_parser::ParseCodeTo_mR("0R1")   ==             100);
    CHECK(res_parser::ParseCodeTo_mR("0R47")  ==             470);
    CHECK(res_parser::ParseCodeTo_mR("R47")   ==             470);
    CHECK(res_parser::ParseCodeTo_mR("220R")  ==         220'000);
    CHECK(res_parser::ParseCodeTo_mR("k22")   ==         220'000);
    CHECK(res_parser::ParseCodeTo_mR("1k")    ==       1'000'000);
    CHECK(res_parser::ParseCodeTo_mR("1k05")  ==       1'050'000);
    CHECK(res_parser::ParseCodeTo_mR("1k0")   ==       1'000'000);
    CHECK(res_parser::ParseCodeTo_mR("1k12")  ==       1'120'000);
    CHECK(res_parser::ParseCodeTo_mR("47k")   ==      47'000'000);
    CHECK(res_parser::ParseCodeTo_mR("47k2")  ==      47'200'000);
    CHECK(res_parser::ParseCodeTo_mR("470k")  ==     470'000'000);
    CHECK(res_parser::ParseCodeTo_mR("1M0")   ==   1'000'000'000);
    CHECK(res_parser::ParseCodeTo_mR("1M2")   ==   1'200'000'000);
    CHECK(res_parser::ParseCodeTo_mR("1M22")  ==   1'220'000'000);
    CHECK(res_parser::ParseCodeTo_mR("470M0") == 470'000'000'000);
}

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
    std::cout << "\n List of available ratios: (example) \n";
    for (auto i = 0; i < arr_ref.size(); ++i) {
        std::cout.precision(3);
        std::cout << "Pair no. " << std::fixed << std::setw(7) << i+1 << " "
                  << "Resistor Low: " << std::fixed << std::setw(7) << arr_ref.at(i).GetResLow().GetValue() << "  "
                  << "Resistor High: " << std::fixed << std::setw(7) << arr_ref.at(i).GetResHigh().GetValue() << "  "
                  << "Ratio: " << std::fixed << arr_ref.at(i).GetRatio() << "\n";
    }
}

template<int N>
void PrintRatioArray2(resistor_divider::AvailableRatios<N> ratios) {
    std::cout << "\n List of available ratios: (example) \n";
    for (auto i = 0; i < N; ++i) {
        std::cout.precision(3);
        std::cout << "Pair no. " << std::fixed << std::setw(7) << i + 1 << " "
            << "Resistor Low: " << std::fixed << std::setw(7) << ratios.arr[i].GetResLow().GetValue()
            << "Resistor High: " << std::fixed << std::setw(7) << ratios.arr[i].GetResHigh().GetValue() << "  "
            << "Ratio: " << std::fixed << ratios.arr[i].GetRatio() << "\n";
    }
}

TEST_CASE("Generation of available ratio list") { 
    #define ARRAY_DIM(x) (sizeof(x)/sizeof(x[0]))
    CHECK(resistor_divider::Two_Permutations_Of_N(6) == 30);
    CHECK(resistor_divider::Two_Permutations_Of_N(1200) == 1438800);

    static constexpr int mul[] = { 1, 10 };
    static constexpr int ser[] = { 10, 22, 47 };
    static constexpr int n_factor = ARRAY_DIM(mul) * ARRAY_DIM(ser);
    CHECK(n_factor == 6);

    constexpr resistor_divider::AvailableRatios<n_factor> a(mul, ARRAY_DIM(mul), ser, ARRAY_DIM(ser));

    PrintRatioArray2<n_factor>(a);

    //for (auto x : a.arr){
        //std::cout << "f(" << x[0] << ") = " << x[1] << '\n';
        //std::cout << x.GetValue() << "\n";
        //std::cout << x.GetResHigh().GetValue() << "\n";
    //}
}