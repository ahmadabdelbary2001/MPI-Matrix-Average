#include "Formatter.h"
#include <sstream>

// Converts a vector of numbers into a formatted string.
std::string Formatter::formatArray(const std::vector<int>& data, const std::string& label, int processID) {
    std::ostringstream result;
    result << "Process " << processID << " - " << label << " (" << data.size() << " items):\n";
    for (size_t i = 0; i < data.size(); ++i) {
        result << data[i] << " "; // Add each number to the string.
        if ((i + 1) % 15 == 0) result << "\n";
    }
    result << "\n";
    return result.str();
}
