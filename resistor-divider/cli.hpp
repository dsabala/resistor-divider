/**
 * Project: resistor-divider
 * Site: https://github.com/dsabala/resistor-divider
 * License: BSD
 */

#pragma once

#include <resistor-divider-logic/resistor_divider_logic.hpp>

namespace cli {

struct SearchResults {
  bool is_correct {false};
  ResistorDivider::SearchCriteria criteria;
};

SearchResults parse(int argc, const char** argv);

}  // namespace cli