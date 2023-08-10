#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int arraySize = 8;
    int localArray[arraySize];
    int globalArray[arraySize];
    
    for(int i=0;i<arraySize;i++)
    {
    globalArray[i]=i;
    }

    // Distribute array data among processes
    MPI_Scatter(globalArray, arraySize / size, MPI_INT,
                localArray, arraySize / size, MPI_INT, 0, MPI_COMM_WORLD);

    // Compute: square the elements
    for (int i = 0; i < arraySize / size; ++i) {
        localArray[i] = localArray[i] * localArray[i];
    }

    // Gather results back to root process
    MPI_Gather(localArray, arraySize / size, MPI_INT,
               globalArray, arraySize / size, MPI_INT, 0, MPI_COMM_WORLD);

    // Print results on root process
    if (rank == 3) {
        std::cout << "Original array: ";
        for (int i = 0; i < arraySize; ++i) {
            std::cout << globalArray[i] << " ";
        }
        std::cout << std::endl;
    }

    MPI_Finalize();

    return 0;
}

