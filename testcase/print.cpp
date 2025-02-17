#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstring>

#define DIM 8
#define NUM 3

double fp64ToFloat(const std::string& fp64Hex) {
    uint64_t packed;
    std::stringstream ss;
    ss << std::hex << fp64Hex;
    ss >> packed;

    double value;
    std::memcpy(&value, &packed, sizeof(double));
    return value;
}

int main() {
    float array_a[DIM][DIM];
    float array_b[DIM][DIM];
    float array_r[DIM][DIM];

    std::ifstream file_read("testcase.txt");
    std::string line;

    for (int i = 0; i < NUM; i++) {
        for (int x = 0; x < DIM; x++) {
            for (int y = 0; y < DIM; y++) {
                std::string fp64Hex;
                file_read >> fp64Hex;
                array_a[x][y] = fp64ToFloat(fp64Hex);
            }
            file_read.ignore(); // Ignore the newline
        }
        for (int x = 0; x < DIM; x++) {
            for (int y = 0; y < DIM; y++) {
                std::string fp64Hex;
                file_read >> fp64Hex;
                array_b[x][y] = fp64ToFloat(fp64Hex);
            }
            file_read.ignore(); // Ignore the newline
        }
        for (int x = 0; x < DIM; x++) {
            for (int y = 0; y < DIM; y++) {
                std::string fp64Hex;
                file_read >> fp64Hex;
                array_r[x][y] = fp64ToFloat(fp64Hex);
            }
            file_read.ignore(); // Ignore the newline
        }
        file_read.ignore(); // Ignore the extra newline

        std::cout << "************************* Test case " << i + 1 << " *************************" << std::endl;
        std::cout << "Tensor A: " << std::endl;
        for (int x = 0; x < DIM; x++) {
            for (int y = 0; y < DIM; y++) {
                std::cout << array_a[x][y] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "Tensor B: " << std::endl;
        for (int x = 0; x < DIM; x++) {
            for (int y = 0; y < DIM; y++) {
                std::cout << array_b[x][y] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "Tensor R: " << std::endl;
        for (int x = 0; x < DIM; x++) {
            for (int y = 0; y < DIM; y++) {
                std::cout << array_r[x][y] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}