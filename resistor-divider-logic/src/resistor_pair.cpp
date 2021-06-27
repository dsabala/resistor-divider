// https://github.com/dsabala/resistor-divider
// License: MIT

#include <resistor-divider-logic/resistor_pait.h>

#include "rescode_parser.hpp"

Resistor(std::string const res_code) {
    value = ParseCodeTo_mR(res_code);
}