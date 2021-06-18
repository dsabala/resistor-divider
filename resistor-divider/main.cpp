/**
 * Project: Resistor Divider
 * Author: Dariusz Sabala
 * License: BSD
 * Site: https://github.com/dsabala/resistor-divider
 */

#include <cstdlib>
#include <iostream>
#include <lyra/lyra.hpp>

int main(int argc, const char** argv) {
  float desired_ratio = 0.5f;
  std::string desired_serie = "e12";

  bool show_help = false;

  auto cli = lyra::help(show_help) |
             lyra::opt(desired_ratio, "ratio")["-r"]["--ratio"](
                 "divider ratio, for example -r 0.205")
                 .required() |
             lyra::opt(desired_serie, "serie")["-s"]["--serie"](
                 "maximum resistor serie, for example -s e24")
                 .choices("e3", "e6", "e12", "e24")
                 .required();

  auto result = cli.parse({argc, argv});

  if (!result) {
    std::cerr << "Error in command line: " << result.errorMessage()
              << std::endl;
    return 1;
  } else if (show_help) {
    std::cout << cli << "\n";
    return 0;
  } else {
    std::cout << "Desired ratio = " << desired_ratio << " desired serie "
              << desired_serie << "\n";
    return 0;
  }
}
