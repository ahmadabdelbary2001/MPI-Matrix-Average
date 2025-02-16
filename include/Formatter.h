#ifndef FORMATTER_H
#define FORMATTER_H

#include <vector>
#include <string>
#include <sstream>

// Class for formatting output strings, making them more readable.
class Formatter {
public:
    // Converts a vector of numbers into a formatted string.
    // `data` is the list of numbers, `label` describes the data, and `processID` identifies the MPI process.
    static std::string formatArray(const std::vector<int>& data, const std::string& label, int processID);
};

#endif // FORMATTER_H

