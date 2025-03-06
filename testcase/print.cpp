#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define DIM 16
#define DIM_K 4
#define NUM 3

FILE* file_read;
int i;

uint64_t array_a_transpose_uint64[DIM_K][DIM];
uint64_t array_b_uint64[DIM_K][DIM];
uint64_t array_r_uint64[DIM][DIM];

double Uint64ToFloat(uint64_t packed) {
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
    for (int x = 0; x < DIM_K; x++) {
        for (int y = 0; y < DIM; y++) {
            fscanf(file_read, "%s", fp64Hex); // Read hex string
            array_a_transpose_uint64[x][y] = fp64ToUint64(fp64Hex); // Convert to uint64
        }
    }
    fgetc(file_read); // Ignore newline

    // Read Tensor B
    for (int x = 0; x < DIM_K; x++) {
        for (int y = 0; y < DIM; y++) {
            fscanf(file_read, "%s", fp64Hex); // Read hex string
            array_b_uint64[x][y] = fp64ToUint64(fp64Hex); // Convert to uint64
        }
    }
    fgetc(file_read); // Ignore newline

    // Read Tensor R
    for (int x = 0; x < DIM; x++) {
        for (int y = 0; y < DIM; y++) {
            fscanf(file_read, "%s", fp64Hex); // Read hex string
            array_r_uint64[x][y] = fp64ToUint64(fp64Hex); // Convert to uint64
        }
    }
    fgetc(file_read); // Ignore newline

    // Print the test case results

    printf("************************* Test case %d *************************\n", i + 1);
    printf("Tensor A Transpose:\n");
    for (int x = 0; x < DIM_K; x++) {
        for (int y = 0; y < DIM; y++) {
            printf("%f ", Uint64ToFloat(array_a_transpose_uint64[x][y])); // Print elements of Tensor A
        }
        printf("\n");
    }
    printf("Tensor B:\n");
    for (int x = 0; x < DIM_K; x++) {
        for (int y = 0; y < DIM; y++) {
            printf("%f ", Uint64ToFloat(array_b_uint64[x][y])); // Print elements of Tensor B
        }
        printf("\n");
    }

    printf("Tensor R:\n");
    for (int x = 0; x < DIM; x++) {
        for (int y = 0; y < DIM; y++) {
            printf("%f ", Uint64ToFloat(array_r_uint64[x][y])); // Print elements of Tensor R
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