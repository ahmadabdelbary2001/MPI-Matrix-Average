#ifndef MPI_ARRAY_PROCESSOR_H
#define MPI_ARRAY_PROCESSOR_H

#include <vector>
#include <mpi.h>

// Handles MPI operations for splitting and sharing data between processes.
class MPIArrayProcessor {
private:
    int rank; // The rank of this process.
    int size; // Total number of processes.

public:
    MPIArrayProcessor(int& argc, char**& argv);
    ~MPIArrayProcessor();

    int getProcessID() const;
    int getTotalProcesses() const;

    // Divides and sends chunks of data from the root process to all processes.
    void distributeData(const std::vector<int>& fullArray, std::vector<int>& localData);

    // Collects computed averages from all processes at the root.
    void collectResults(double localAverage, std::vector<double>& allAverages);
};

#endif // MPI_ARRAY_PROCESSOR_H

