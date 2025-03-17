#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <torch/torch.h>
#include <random>
#include <cstring>
#include <cmath>

#define DIM 16
#define DIM_K 4
#define NUM 3
#define PRE 5

uint16_t floatToFP16(float value) {
    // Handle special cases
    if (std::isnan(value)) return 0x7E00; // NaN
    if (value == 0.0f) return 0;          // Zero
    if (value == INFINITY) return 0x7C00; // +Infinity
    if (value == -INFINITY) return 0xFC00; // -Infinity

    int sign = (value < 0) ? 1 : 0;
    if (sign) value = -value;

    // Find exponent and mantissa
    int exponent = 0;
    while (value >= 2.0f) {
        value /= 2.0f;
        exponent++;
    }
    while (value < 1.0f && exponent > -14) {
        value *= 2.0f;
        exponent--;
    }

    // Handle overflow and underflow
    if (exponent > 15) return 0x7C00; // +Infinity
    if (exponent < -14) return 0;     // Zero

    // Adjust exponent for FP16
    exponent += 15; // Bias for FP16 is 15

    // Get the mantissa (10 bits for FP16)
    uint32_t mantissa = static_cast<uint32_t>(value * (1 << 10)) & 0x3FF;

    // Construct FP16
    uint16_t fp16 = (sign << 15) | (exponent << 10) | mantissa;
    return fp16;
}

std::string floatTo64BitFP16(float value) {
    uint64_t packed = 0; // Initialize 64-bit packed variable

    // Convert float to FP16
    uint16_t fp16 = floatToFP16(value);

    // Pack FP16 into the lower 16 bits of the 64-bit integer
    packed |= static_cast<uint64_t>(fp16);

    // Create a stringstream to format the output
    std::stringstream ss;
    ss << std::hex << std::setw(16) << std::setfill('0') << packed;

    return ss.str(); // Return the formatted string
}

int main() {
    std::cout << std::fixed << std::setprecision(PRE);
    std::ofstream file("testcase.txt");
    file << std::fixed << std::setprecision(PRE);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0, 1.0);

    for (int i = 0; i < NUM; i++) {
        torch::Tensor fp_a = torch::empty({DIM, DIM_K});
        torch::Tensor fp_a_transpose = torch::empty({DIM_K, DIM});
        torch::Tensor fp_b = torch::empty({DIM_K, DIM});

        for (int x = 0; x < DIM; x++) {
            for (int y = 0; y < DIM_K; y++) {
                float randomValueA = dis(gen);
                fp_a[x][y] = randomValueA;
            }
        }

        for (int x = 0; x < DIM_K; x++) {
            for (int y = 0; y < DIM; y++) {
                float randomValueB = dis(gen);
                fp_b[x][y] = randomValueB;
            }
        }

        torch::Tensor fp_result = torch::matmul(fp_a, fp_b);

        // Transpose A
        for (int x = 0; x < DIM; x++) {
            for (int y = 0; y < DIM_K; y++) {
                fp_a_transpose[y][x] = fp_a[x][y];
            }
        }

        auto tensor_a_transpose = fp_a_transpose.accessor<float, 2>();
        auto tensor_b = fp_b.accessor<float, 2>();
        auto tensor_r = fp_result.accessor<float, 2>();

        for (int x = 0; x < DIM_K; x++) {
            for (int y = 0; y < DIM; y++) {
                file << floatTo64BitFP16(tensor_a_transpose[x][y]) << " ";
            }
            file << std::endl;
        }
        file << std::endl;

        for (int x = 0; x < DIM_K; x++) {
            for (int y = 0; y < DIM; y++) {
                file << floatTo64BitFP16(tensor_b[x][y]) << " ";
            }
            file << std::endl;
        }
        file << std::endl;

        for (int x = 0; x < DIM; x++) {
            for (int y = 0; y < DIM; y++) {
                file << floatTo64BitFP16(tensor_r[x][y]) << " ";
            }
            file << std::endl;
        }
        file << std::endl << std::endl; // Separate test cases
    }

    file.close();
    std::cout << "Test cases are generated and saved in testcase.txt" << std::endl;

    return 0;
}