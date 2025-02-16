#ifndef RANDOM_UTILS_H
#define RANDOM_UTILS_H

#include <vector>
#include <numeric>
#include <cstddef>

// Utility class for handling random numbers and math operations.
class RandomUtils {
public:
    // Generates a list of random numbers.
    static std::vector<int> generateRandomNumbers(std::size_t count, int maxValue = 100);

    // Overload computeMean for both int and double vectors
    static double computeMean(const std::vector<int>& data);
    static double computeMean(const std::vector<double>& data);
};

#endif // RANDOM_UTILS_H

