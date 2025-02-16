#include "RandomUtils.h"
#include <cstdlib>
#include <ctime>
#include <numeric>

// Generates a list of random numbers.
std::vector<int> RandomUtils::generateRandomNumbers(size_t count, int maxValue) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    std::vector<int> numbers(count);
    for (auto& num : numbers) {
        num = std::rand() % maxValue + 1; // Generate a number between 1 and `maxValue`.
    }
    return numbers;
}

// Calculates the mean of a list of numbers.
// Overload for std::vector<int>
double RandomUtils::computeMean(const std::vector<int>& data) {
    if (data.empty()) return 0.0;
    return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}

// Overload for std::vector<double>
double RandomUtils::computeMean(const std::vector<double>& data) {
    if (data.empty()) return 0.0;
    return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}

