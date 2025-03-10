#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <torch/torch.h>
#include <random>
#include <cstring>

#define DIM 16
#define DIM_K 4
#define NUM 3
#define PRE 5

std::string floatToFP64(double value) {
    uint64_t packed;
    std::memcpy(&packed, &value, sizeof(double));
    std::stringstream ss;
    ss << std::hex << std::setw(16) << std::setfill('0') << packed;
    return ss.str();
}

int main() {
    std::cout << std::fixed << std::setprecision(PRE);
    std::ofstream file("testcase.txt");
    file << std::fixed << std::setprecision(PRE);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    for (int i = 0; i < NUM; i++) {
        torch::Tensor fp_a = torch::empty({DIM, DIM_K});
        torch::Tensor fp_a_transpose = torch::empty({DIM_K, DIM});
        torch::Tensor fp_b = torch::empty({DIM_K, DIM});

        for (int x = 0; x < DIM; x++) {
            for (int y = 0; y < DIM_K; y++) {
                double randomValueA = dis(gen);
                fp_a[x][y] = randomValueA;
            }
        }

        for (int x = 0; x < DIM_K; x++) {
            for (int y = 0; y < DIM; y++) {
                double randomValueB = dis(gen);
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
                file << floatToFP64(tensor_a_transpose[x][y]) << " ";
            }
            file << std::endl;
        }
        file << std::endl;

        for (int x = 0; x < DIM_K; x++) {
            for (int y = 0; y < DIM; y++) {
                file << floatToFP64(tensor_b[x][y]) << " ";
            }
            file << std::endl;
        }
        file << std::endl;

        for (int x = 0; x < DIM; x++) {
            for (int y = 0; y < DIM; y++) {
                file << floatToFP64(tensor_r[x][y]) << " ";
            }
            file << std::endl;
        }
        file << std::endl << std::endl; // Separate test cases
    }

    file.close();
    std::cout << "Test cases are generated and saved in testcase.txt" << std::endl;

    return 0;
}