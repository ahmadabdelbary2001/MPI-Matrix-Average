#ifndef APPLICATION_H
#define APPLICATION_H

#include "MPIArrayProcessor.h"
#include "RandomUtils.h"
#include "Formatter.h"
#include <vector>
#include <sstream>
#include <iostream>

// Main logic of the application that connects everything together.
class Application {
private:
    MPIArrayProcessor mpiProcessor; // Manages MPI communication.

public:
    Application(int& argc, char**& argv);

    // Runs the main processing steps.
    void run();
};

#endif // APPLICATION_H

