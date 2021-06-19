/**
 * Project: Resistor Divider
 * Author: Dariusz Sabala
 * License: BSD
 * Site: https://github.com/dsabala/resistor-divider
 */

#include <cli_parser.hpp>

int main(int argc, const char** argv) {
  auto parse_result = cli::parse(argc, argv);

  if (parse_result.is_correct) {
    return 0;
  } else {
    return 1;
  }
}
