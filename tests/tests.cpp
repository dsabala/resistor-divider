
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

TEST_CASE("Generation of available ratio list") { 
    std::vector<std::uint64_t> val_multipliers{ 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000 };

    std::vector<std::uint64_t> val_serie2 { 10, 15, 22, 33, 47, 68 };

    std::vector<std::uint64_t> val_serie1 { 100, 101, 102, 104, 105, 106, 107, 109, 110, 111, 113, 114, 115, 117, 118, 120,
                                         121, 123, 124, 126, 127, 129, 130, 132, 133, 135, 137, 138, 140, 142, 143, 145,
                                         147, 149, 150, 152, 154, 156, 158, 160, 162, 164, 165, 167, 169, 172, 174, 176 };

    std::vector<std::uint64_t> val_serie { 100, 101, 102, 104, 105, 106, 107, 109, 110, 111, 113, 114, 115, 117, 118, 120,
                                  121, 123, 124, 126, 127, 129, 130, 132, 133, 135, 137, 138, 140, 142, 143, 145, 
                                  147, 149, 150, 152, 154, 156, 158, 160, 162, 164, 165, 167, 169, 172, 174, 176, 
                                  178, 180, 182, 184, 187, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213, 
                                  215, 218, 221, 223, 226, 229, 232, 234, 237, 240, 243, 246, 249, 252, 255, 258, 
                                  261, 264, 267, 271, 274, 277, 280, 284, 287, 291, 294, 298, 301, 305, 309, 312, 
                                  316, 320, 324, 328, 332, 336, 340, 344, 348, 352, 357, 361, 365, 370, 374, 379, 
                                  383, 388, 392, 397, 402, 407, 412, 417, 422, 427, 432, 437, 442, 448, 453, 459, 
                                  464, 470, 475, 481, 487, 493, 499, 505, 511, 517, 523, 530, 536, 542, 549, 556, 
                                  562, 569, 576, 583, 590, 597, 604, 612, 619, 626, 634, 642, 649, 657, 665, 673, 
                                  681, 690, 698, 706, 715, 723, 732, 741, 750, 759, 768, 777, 787, 796, 806, 816, 
                                  825, 835, 845, 856, 866, 876, 887, 898, 909, 920, 931, 942, 953, 965, 976, 988 };

    std::vector<resistor_divider::ResistorsPair> ratio_list;

    GenerateRatioList(ratio_list, val_multipliers, val_serie);

    PrintRatioArray(ratio_list);
}