#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_BLOCKS 100

typedef struct {
    int start;
    int length;
    char name[20];
} File;

bool allocated[MAX_BLOCKS] = {false};
File directory[MAX_BLOCKS];

int n;

void initializeDisk() {
    int i;
    for (i = 0; i < n; i++) {
        allocated[i] = false;
    }
}

void displayBitVector() {
    int i;
    printf("Bit Vector: ");
    for (i = 0; i < n; i++) {
        printf("%d ", allocated[i]);
    }
    printf("\n");
}

void displayDirectory() {
    int i;
    printf("Directory:\n");
    printf("Index\tStart\tLength\tName\n");
    for (i = 0; i < n; i++) {
        if (allocated[i]) {
            printf("%d\t%d\t%d\t%s\n", i, directory[i].start, directory[i].length, directory[i].name);
        }
    }
}

void deleteFile() {
    char filename[20];
    int i;

    printf("Enter the name of the file to delete: ");
    scanf("%s", filename);

    for (i = 0; i < n; i++) {
        if (allocated[i] && strcmp(directory[i].name, filename) == 0) {
            allocated[i] = false;
            printf("File '%s' deleted successfully.\n", filename);
            return;
        }
    }

    printf("File '%s' not found.\n", filename);
}

int main() {
    int choice;

    printf("Enter the number of blocks on the disk: ");
    scanf("%d", &n);

    initializeDisk();

    do {
        printf("\nSequential (Contiguous) File Allocation\n");
        printf("1. Show Bit Vector\n");
        printf("2. Show Directory\n");
        printf("3. Delete File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayBitVector();
                break;
            case 2:
                displayDirectory();
                break;
            case 3:
                deleteFile();
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 4);

    return 0;
}
