#include "cli/include/error_printer.hpp"

void Cli::ErrorPrinter::single_error(std::ostream &output,
                                     const std::string &error) {
  output << "Erro: " << error << std::endl;
}

void Cli::ErrorPrinter::error_list(std::ostream &output,
                                   const std::vector<std::string> &errors) {
  for (const auto &error : errors) {
    output << error << std::endl;
  }
}
