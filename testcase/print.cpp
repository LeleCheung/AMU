#include <cstdint>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <cstdio>
#include <cmath>

#define DIM 16
#define DIM_K 4
#define NUM 3

FILE* file_read;
int i;

uint64_t array_a_transpose_uint64[DIM_K][DIM];
uint64_t array_b_uint64[DIM_K][DIM];
uint64_t array_r_uint64[DIM][DIM];




// Convert a 64-bit unsigned integer to a float (from FP16 format)
double Uint64FP16ToFloat(uint64_t packed) {
    // Extract the FP16 value (lower 16 bits)
    uint16_t fp16 = static_cast<uint16_t>(packed & 0xFFFF);
    
    // Convert FP16 to float
    if (fp16 == 0) return 0.0; // Handle zero case
    if ((fp16 & 0x7C00) == 0x7C00) return fp16 & 0x8000 ? -INFINITY : INFINITY; // Handle +Inf/-Inf
    if ((fp16 & 0x7FFF) == 0x7FFF) return NAN; // Handle NaN

    int sign = (fp16 >> 15) & 0x1; // Extract sign bit
    int exponent = (fp16 >> 10) & 0x1F; // Extract exponent
    int mantissa = fp16 & 0x3FF; // Extract mantissa

    // Calculate the actual float value
    if (exponent == 0) {
        // Denormalized case
        return (sign ? -1 : 1) * (mantissa / 1024.0f) * pow(2, -14);
    } else {
        // Normalized case
        return (sign ? -1 : 1) * (1 + mantissa / 1024.0f) * pow(2, exponent - 15);
    }
}

// Convert a hexadecimal string to a 64-bit unsigned integer representing FP16
uint64_t CharFP16ToUint64FP16(const char* fp16Hex) {
    uint64_t packed = 0; // Initialize packed variable
    uint16_t fp16; // Variable to store the FP16 value

    // Read the 16-bit FP16 hexadecimal value
    sscanf(fp16Hex, "%hx", &fp16); // Use %hx to read unsigned short

    // Place the FP16 value in the lower 16 bits of the 64-bit integer, setting the rest to 0
    packed = static_cast<uint64_t>(fp16);

    return packed; // Return the 64-bit unsigned integer
}

void fun1(){
    char fp64Hex[17]; // 16 characters + 1 for null terminator
    // Read Tensor A
    for (int x = 0; x < DIM_K; x++) {
        for (int y = 0; y < DIM; y++) {
            fscanf(file_read, "%s", fp64Hex); // Read hex string
            array_a_transpose_uint64[x][y] = CharFP16ToUint64FP16(fp64Hex); // Convert to uint64
        }
    }
    fgetc(file_read); // Ignore newline

    // Read Tensor B
    for (int x = 0; x < DIM_K; x++) {
        for (int y = 0; y < DIM; y++) {
            fscanf(file_read, "%s", fp64Hex); // Read hex string
            array_b_uint64[x][y] = CharFP16ToUint64FP16(fp64Hex); // Convert to uint64
        }
    }
    fgetc(file_read); // Ignore newline

    // Read Tensor R
    for (int x = 0; x < DIM; x++) {
        for (int y = 0; y < DIM; y++) {
            fscanf(file_read, "%s", fp64Hex); // Read hex string
            array_r_uint64[x][y] = CharFP16ToUint64FP16(fp64Hex); // Convert to uint64
        }
    }
    fgetc(file_read); // Ignore newline

    // Print the test case results

    printf("************************* Test case %d *************************\n", i + 1);
    printf("Tensor A Transpose:\n");
    for (int x = 0; x < DIM_K; x++) {
        for (int y = 0; y < DIM; y++) {
            printf("%f ",  Uint64FP16ToFloat(array_a_transpose_uint64[x][y])); // Print elements of Tensor A
        }
        printf("\n");
    }
    printf("Tensor B:\n");
    for (int x = 0; x < DIM_K; x++) {
        for (int y = 0; y < DIM; y++) {
            printf("%f ",  Uint64FP16ToFloat(array_b_uint64[x][y])); // Print elements of Tensor B
        }
        printf("\n");
    }

    printf("Tensor R:\n");
    for (int x = 0; x < DIM; x++) {
        for (int y = 0; y < DIM; y++) {
            printf("%f ",  Uint64FP16ToFloat(array_r_uint64[x][y])); // Print elements of Tensor R
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