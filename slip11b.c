#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char** argv) {
    int rank, size;
    int i, min_local, min_global;
    int* array = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Allocate memory for the array on each process
    array = (int*)malloc(ARRAY_SIZE * sizeof(int));

    // Generate random numbers on each process
    srand(rank + 1);
    for (i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand();
    }

    // Find the local minimum
    min_local = array[0];
    for (i = 1; i < ARRAY_SIZE; i++) {
        if (array[i] < min_local) {
            min_local = array[i];
        }
    }

    // Use MPI_Reduce to find the global minimum
    MPI_Reduce(&min_local, &min_global, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    // Print the result from the root process
    if (rank == 0) {
        printf("Minimum number: %d\n", min_global);
    }

    // Clean up
    free(array);
    MPI_Finalize();

    return 0;
    //TO RUN CODE : mpicc mpi_min.c -o mpi_min
    //              mpirun -np 4 ./mpi_min

}
