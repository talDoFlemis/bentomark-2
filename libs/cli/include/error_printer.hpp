#ifndef ERROR_PRINTER_HPP
#define ERROR_PRINTER_HPP

#include <istream>
#include <string>
#include <vector>

namespace Cli {
class ErrorPrinter {
public:
  ErrorPrinter() = default;
  ~ErrorPrinter() = default;

  static void single_error(std::ostream &, const std::string &);
  static void error_list(std::ostream &, const std::vector<std::string> &);
};
};     // namespace Cli
#endif // !ERROR_PRINTER_HPP
