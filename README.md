# MPI Array Processing Example

This project demonstrates how to use **MPI** (Message Passing Interface) to distribute a large array of randomly generated integers among multiple processes, compute partial averages locally, and then combine these partial averages into a global average on the root process.

## Project Description

This project demonstrates:
1. Matrix generation and distribution across MPI processes
2. Local average computation on each process
3. Global average aggregation using MPI collective operations

## Features

1. **Random Data Generation**  
   - The root process (rank 0) creates an array of 1000 random integers.
2. **Data Distribution**  
   - The array is divided among all participating processes. Each process prints its received portion.
3. **Local Average Calculation**  
   - Each process computes the average of the elements it received.
4. **Result Collection**  
   - The root process gathers local averages from all processes.
5. **Global Average**  
   - The root process computes the global average from the collected partial averages and prints the final result.

## Project Structure
```
mpi-matrix-average/
├── include/
│ ├── Application.h
│ ├── Formatter.h
│ ├── MPIArrayProcessor.h
│ └── RandomUtils.h
├── src/
│ ├── Application.cpp
│ ├── Formatter.cpp
│ ├── MPIArrayProcessor.cpp
│ ├── RandomUtils.cpp
│ └── main.cpp
└── mpi_application
```

## How It Works

1. **Initialization**  
   - `main.cpp` initializes the application (`Application`) and starts the MPI environment.
2. **Generation & Distribution**  
   - `RandomUtils::generateRandomNumbers` creates the 1000-element array (only in rank 0).
   - `MPIArrayProcessor::distributeData` splits the array and sends the chunks to each process.
3. **Local Computation**  
   - Each process receives its chunk and computes the local average using `RandomUtils::computeMean`.
4. **Collection & Global Average**  
   - The root process (rank 0) collects all partial averages via `MPIArrayProcessor::collectResults`.
   - It then computes the global average by averaging the partial averages.
5. **Output**  
   - `Formatter::formatArray` and standard I/O are used to print data at each step.

## Building & Running
```
   # Build
   mpicxx -o mpi_application src/*.cpp

   # Run with 4 processes
   mpirun -n 4 ./mpi_application
```
