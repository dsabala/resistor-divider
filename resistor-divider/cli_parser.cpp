/**
 * Project: resistor-divider
 * Site: https://github.com/dsabala/resistor-divider
 * License: BSD
 */

#include "cli_parser.hpp"

#include <lyra/lyra.hpp>

cli::SearchResults cli::parse(int argc, const char** argv) {
  SearchResults result;

  bool show_help = false;
  auto cli = lyra::help(show_help) |
             lyra::opt(result.criteria.ratio, "ratio")["-r"]["--ratio"](
                 "divider ratio, for example -r 0.205")
                 .required() |
             lyra::opt(result.criteria.res_e_serie, "serie")["-s"]["--serie"](
                 "maximum resistor serie, for example -s 24")
                 .choices(3, 6, 12, 24)
                 .required() |
             lyra::opt(result.criteria.results_no, "number")["-n"]["--number"](
                 "hits number, for example -n 10")
                 .required();
  auto arguments = cli.parse({argc, argv});

  if (!arguments) {
    std::cerr << "Wrong command: " << arguments.errorMessage() << std::endl;
  } else if (show_help) {
    std::cout << cli << "\n";
  } else {
    std::cout << "Passed parameters: ratio = " << result.criteria.ratio
              << " serie = " << result.criteria.results_no
              << " number = " << result.criteria.results_no << "\n";
    result.is_correct = true;
  }

  return result;
}