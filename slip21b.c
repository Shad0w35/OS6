#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char** argv) {
    int rank, size;
    int numbers[ARRAY_SIZE];
    int local_sum = 0;
    int global_sum = 0;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    srand(time(NULL) + rank);  // Seed the random number generator
    
    // Generate random numbers
    for (int i = 0; i < ARRAY_SIZE; i++) {
        numbers[i] = rand() % 100;
    }
    
    // Calculate local sum of odd numbers
    for (int i = rank; i < ARRAY_SIZE; i += size) {
        if (numbers[i] % 2 == 0) {
            local_sum += numbers[i];
        }
    }
    
    // Reduce the local sums to get the global sum
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        printf("Global sum of odd numbers: %d\n", global_sum);
    }
    
    MPI_Finalize();
    
    return 0;
}