#include "Application.h"
#include <iomanip>
#include <sstream>
#include <iostream>

// Constructor
Application::Application(int& argc, char**& argv) : mpiProcessor(argc, argv) {}

// Runs the main processing steps.
void Application::run() {
    int rank = mpiProcessor.getProcessID();
    int total = mpiProcessor.getTotalProcesses();

    std::vector<int> localData;
    std::ostringstream output;

    const int arraySize = 1000;
    std::vector<int> fullArray;

    if (rank == 0) {
        // Rank 0 generates the full dataset
        fullArray = RandomUtils::generateRandomNumbers(arraySize);
        output << Formatter::formatArray(fullArray, "Generated Data", rank);
    }

    // Distribute data to all processes
    mpiProcessor.distributeData(fullArray, localData);

    // Compute the local average
    double localAverage = RandomUtils::computeMean(localData);
    output << "Process " << rank << " - Local Average: " << std::fixed << std::setprecision(2) << localAverage << "\n";

    // Gather local averages to rank 0
    std::vector<double> allAverages;
    if (rank == 0) {
        allAverages.resize(total);
    }
    mpiProcessor.collectResults(localAverage, allAverages);

    if (rank == 0) {
        // Rank 0 processes and prints the global average
        output << "\nLocal Averages from all processes:\n";
        for (size_t i = 0; i < allAverages.size(); ++i) {
            output << "Process " << i << ": " << std::fixed << std::setprecision(2) << allAverages[i] << "\n";
        }

        double globalAverage = RandomUtils::computeMean(allAverages);
        output << "\nGlobal Average: " << std::fixed << std::setprecision(2) << globalAverage << "\n";

        std::cout << output.str();
    }
}
