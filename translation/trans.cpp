#include <stdio.h>
#include <stdint.h>
#include <string.h>

double fp64ToFloat(const char* fp64Hex) {
    uint64_t packed = 0;
    sscanf(fp64Hex, "%lx", &packed); // Read the hexadecimal string

    double value;
    memcpy(&value, &packed, sizeof(double)); // Copy memory to convert
    return value;
}

double Uint64ToFloat(uint64_t packed) {
    double value;
    memcpy(&value, &packed, sizeof(double)); // Copy memory to convert
    return value;
}

int main(){
    uint64_t packed1 = 0x3fef6cfde0000000;
    double value1 = Uint64ToFloat(packed1);
    printf("value1: %f\n", value1);

    uint64_t packed2 = 0xfe40595077def5c0;
    double value2 = Uint64ToFloat(packed2);
    printf("value2: %f\n", value2);

    return 0;
}