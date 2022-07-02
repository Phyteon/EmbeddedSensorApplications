
#include "diagnostic.hpp"

std::string diagnostic::DiagnosticUtils::prepare_error_msg(const std::string& base,
                                                           const std::string& context,
                                                           esp_err_t error) {
    std::string concatentated{base + context};
    concatentated += "\n##### ERROR CODE: ";
    concatentated += std::to_string(error);
    concatentated += " #####\n";
    return concatentated;
}