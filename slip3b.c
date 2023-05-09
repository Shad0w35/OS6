#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char** argv) {
    int rank, size;
    int i, sum = 0, local_sum = 0;
    double avg = 0.0, local_avg = 0.0;
    int numbers[ARRAY_SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Generate random numbers on the root process
        srand(time(NULL));
        for (i = 0; i < ARRAY_SIZE; i++) {
            numbers[i] = rand() % 100;  // Generate numbers between 0 and 99
        }
    }

    // Scatter the numbers to all processes
    MPI_Scatter(numbers, ARRAY_SIZE / size, MPI_INT, numbers, ARRAY_SIZE / size, MPI_INT, 0, MPI_COMM_WORLD);

    // Calculate the local sum
    for (i = 0; i < ARRAY_SIZE / size; i++) {
        local_sum += numbers[i];
    }

    // Reduce the local sums to the root process
    MPI_Reduce(&local_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Calculate the global average on the root process
    if (rank == 0) {
        avg = (double)sum / ARRAY_SIZE;
    }

    // Broadcast the average to all processes
    MPI_Bcast(&avg, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Calculate the local average
    for (i = 0; i < ARRAY_SIZE / size; i++) {
        local_avg += numbers[i] / (double)ARRAY_SIZE;
    }

    // Reduce the local averages to the root process
    MPI_Reduce(&local_avg, &avg, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Print the results on the root process
    if (rank == 0) {
        printf("Sum: %d\n", sum);
        printf("Average: %.2f\n", avg);
    }

    MPI_Finalize();

    return 0;
}