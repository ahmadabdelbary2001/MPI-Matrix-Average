#include "MPIArrayProcessor.h"

// Constructor: Initialize MPI environment.
MPIArrayProcessor::MPIArrayProcessor(int& argc, char**& argv) {
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
}

// Destructor: Finalize MPI environment.
MPIArrayProcessor::~MPIArrayProcessor() {
    MPI_Finalize();
}

int MPIArrayProcessor::getProcessID() const {
    return rank;
}

int MPIArrayProcessor::getTotalProcesses() const {
    return size;
}

// Divides and sends chunks of data from the root process to all processes.
void MPIArrayProcessor::distributeData(const std::vector<int>& fullArray, std::vector<int>& localData) {
    int chunkSize = fullArray.size() / size; // Divide the array evenly
    int remainder = fullArray.size() % size; // Handle leftover elements

    if (rank == 0) {
        // Root process sends data to other processes
        for (int i = 1; i < size; ++i) {
            int startIndex = i * chunkSize + std::min(i, remainder);
            int elementsToSend = chunkSize + (i < remainder ? 1 : 0);

            MPI_Send(&elementsToSend, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(fullArray.data() + startIndex, elementsToSend, MPI_INT, i, 1, MPI_COMM_WORLD);
        }

        // Root keeps its own portion
        int elementsForRoot = chunkSize + (0 < remainder ? 1 : 0);
        localData.assign(fullArray.begin(), fullArray.begin() + elementsForRoot);
    } else {
        // Other processes receive their portions
        int elementsToReceive;
        MPI_Recv(&elementsToReceive, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        localData.resize(elementsToReceive);
        MPI_Recv(localData.data(), elementsToReceive, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
}

// Collects computed averages from all processes at the root.
void MPIArrayProcessor::collectResults(double localAverage, std::vector<double>& allAverages) {
    if (rank == 0) {
        allAverages[0] = localAverage; // Root stores its own average
        for (int i = 1; i < size; ++i) {
            MPI_Recv(&allAverages[i], 1, MPI_DOUBLE, i, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    } else {
        MPI_Send(&localAverage, 1, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
    }
}
