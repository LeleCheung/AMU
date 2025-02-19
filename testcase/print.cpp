#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define DIM 8
#define NUM 3

FILE* file_read;
int i;

float array_a[DIM][DIM];
float array_b[DIM][DIM];
float array_r[DIM][DIM];

uint64_t array_a_uint64[DIM][DIM];
uint64_t array_b_uint64[DIM][DIM];
uint64_t array_r_uint64[DIM][DIM];

// Convert hexadecimal string to double
double fp64ToFloat(const char* fp64Hex) {
    uint64_t packed = 0;
    sscanf(fp64Hex, "%lx", &packed); // Read the hexadecimal string

    double value;
    memcpy(&value, &packed, sizeof(double)); // Copy memory to convert
    return value;
}

uint64_t fp64ToUint64(const char* fp64Hex) {
    uint64_t packed = 0;
    sscanf(fp64Hex, "%lx", &packed); // Read the hexadecimal string

    return packed;
}

void fun1(){
    char fp64Hex[17]; // 16 characters + 1 for null terminator
    // Read Tensor A
    for (int x = 0; x < DIM; x++) {
        for (int y = 0; y < DIM; y++) {
            fscanf(file_read, "%s", fp64Hex); // Read hex string
            array_a[x][y] = fp64ToFloat(fp64Hex); // Convert to float
            array_a_uint64[x][y] = fp64ToUint64(fp64Hex); // Convert to uint64
        }
    }
    fgetc(file_read); // Ignore newline

    // Read Tensor B
    for (int x = 0; x < DIM; x++) {
        for (int y = 0; y < DIM; y++) {
            fscanf(file_read, "%s", fp64Hex); // Read hex string
            array_b[x][y] = fp64ToFloat(fp64Hex); // Convert to float
            array_b_uint64[x][y] = fp64ToUint64(fp64Hex); // Convert to uint64
        }
    }
    fgetc(file_read); // Ignore newline

    // Read Tensor R
    for (int x = 0; x < DIM; x++) {
        for (int y = 0; y < DIM; y++) {
            fscanf(file_read, "%s", fp64Hex); // Read hex string
            array_r[x][y] = fp64ToFloat(fp64Hex); // Convert to float
            array_r_uint64[x][y] = fp64ToUint64(fp64Hex); // Convert to uint64
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

    printf("************************* Test case in UINT %d *************************\n", i + 1);
    printf("Tensor A:\n");
    for (int x = 0; x < DIM; x++) {
        for (int y = 0; y < DIM; y++) {
            printf("%lx ", array_a_uint64[x][y]); // Print elements of Tensor A
        }
        printf("\n");
    }

    printf("Tensor B:\n");
    for (int x = 0; x < DIM; x++) {
        for (int y = 0; y < DIM; y++) {
            printf("%lx ", array_b_uint64[x][y]); // Print elements of Tensor B
        }
        printf("\n");
    }

    printf("Tensor R:\n");
    for (int x = 0; x < DIM; x++) {
        for (int y = 0; y < DIM; y++) {
            printf("%lx ", array_r_uint64[x][y]); // Print elements of Tensor R
        }
        printf("\n");
    }
    printf("\n");



    i++; // Increment the test case number
}

int main() {
    // Open the input file for reading
    file_read = fopen("testcase.txt", "r");
    if (!file_read) {
        perror("Unable to open file"); // Error handling
        return 1;
    }



    i = 0; // Test case number

    fun1();
    fun1();
    fun1();



    fclose(file_read); // Close the file
    return 0;
}