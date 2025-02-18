#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define DIM 8
#define NUM 3

// Convert hexadecimal string to double
double fp64ToFloat(const char* fp64Hex) {
    uint64_t packed = 0;
    sscanf(fp64Hex, "%lx", &packed); // Read the hexadecimal string

    double value;
    memcpy(&value, &packed, sizeof(double)); // Copy memory to convert
    return value;
}

int main() {
    float array_a[DIM][DIM];
    float array_b[DIM][DIM];
    float array_r[DIM][DIM];

    // Open the input file for reading
    FILE* file_read = fopen("testcase.txt", "r");
    if (!file_read) {
        perror("Unable to open file"); // Error handling
        return 1;
    }

    char fp64Hex[17]; // 16 characters + 1 for null terminator

    for (int i = 0; i < NUM; i++) {
        // Read Tensor A
        for (int x = 0; x < DIM; x++) {
            for (int y = 0; y < DIM; y++) {
                fscanf(file_read, "%s", fp64Hex); // Read hex string
                array_a[x][y] = fp64ToFloat(fp64Hex); // Convert to float
            }
        }
        fgetc(file_read); // Ignore newline

        // Read Tensor B
        for (int x = 0; x < DIM; x++) {
            for (int y = 0; y < DIM; y++) {
                fscanf(file_read, "%s", fp64Hex); // Read hex string
                array_b[x][y] = fp64ToFloat(fp64Hex); // Convert to float
            }
        }
        fgetc(file_read); // Ignore newline

        // Read Tensor R
        for (int x = 0; x < DIM; x++) {
            for (int y = 0; y < DIM; y++) {
                fscanf(file_read, "%s", fp64Hex); // Read hex string
                array_r[x][y] = fp64ToFloat(fp64Hex); // Convert to float
            }
        }
        fgetc(file_read); // Ignore newline

        // Print the test case results
        printf("************************* Test case %d *************************\n", i + 1);
        printf("Tensor A:\n");
        for (int x = 0; x < DIM; x++) {
            for (int y = 0; y < DIM; y++) {
                printf("%f ", array_a[x][y]); // Print elements of Tensor A
            }
            printf("\n");
        }

        printf("Tensor B:\n");
        for (int x = 0; x < DIM; x++) {
            for (int y = 0; y < DIM; y++) {
                printf("%f ", array_b[x][y]); // Print elements of Tensor B
            }
            printf("\n");
        }

        printf("Tensor R:\n");
        for (int x = 0; x < DIM; x++) {
            for (int y = 0; y < DIM; y++) {
                printf("%f ", array_r[x][y]); // Print elements of Tensor R
            }
            printf("\n");
        }
        printf("\n");
    }

    fclose(file_read); // Close the file
    return 0;
}