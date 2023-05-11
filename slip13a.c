#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main() {
    int available[MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    bool finished[MAX_PROCESSES] = {false};
    int safe_sequence[MAX_PROCESSES];
    int num_processes, num_resources;
    int i, j, k, count = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    printf("Enter the available resources:\n");
    for (i = 0; i < num_resources; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the maximum demand of each process:\n");
    for (i = 0; i < num_processes; i++) {
        printf("Process %d: ", i);
        for (j = 0; j < num_resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the allocation of each process:\n");
    for (i = 0; i < num_processes; i++) {
        printf("Process %d: ", i);
        for (j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Calculate the content of the need matrix
    printf("The content of the need matrix:\n");
    for (i = 0; i < num_processes; i++) {
        for (j = 0; j < num_resources; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Check if the system is in a safe state
    while (count < num_processes) {
        bool found = false;
        for (i = 0; i < num_processes; i++) {
            if (!finished[i]) {
                bool can_be_allocated = true;
                for (j = 0; j < num_resources; j++) {
                    if (need[i][j] > available[j]) {
                        can_be_allocated = false;
                        break;
                    }
                }
                if (can_be_allocated) {
                    for (k = 0; k < num_resources; k++) {
                        available[k] += allocation[i][k];
                    }
                    safe_sequence[count] = i;
                    finished[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) {
            break;  // System is in an unsafe state
        }
    }

    if (count == num_processes) {
        printf("The system is in a safe state.\nSafe sequence: ");
        for (i = 0; i < num_processes; i++) {
            printf("%d ", safe_sequence[i]);
        }
        printf("\n");
    } else {
        printf("The system is in an unsafe state.\n");
    }

    return 0;
}
