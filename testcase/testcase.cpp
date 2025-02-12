#include <iostream>
#include <fstream>
#include <torch/torch.h>

#define DIM 8
#define NUM 3
#define PRE 5

int main() {
    std::cout << std::fixed << std::setprecision(PRE);

    std::ofstream file;
    file.open("testcase.txt");
    file << std::fixed << std::setprecision(PRE);

    for (int i = 0; i < NUM; i++) {
        srand(time(0));
        torch::Tensor fp_a = torch::rand({DIM, DIM});
        torch::Tensor fp_b = torch::rand({DIM, DIM});
        torch::Tensor fp_result = torch::matmul(fp_a, fp_b);

        // Save tensor to 2D accessors
        auto tensor_a = fp_a.accessor<float, 2>(); 
        auto tensor_b = fp_b.accessor<float, 2>(); 
        auto tensor_r = fp_result.accessor<float, 2>(); 

        // Write tensors to file
        for (int i = 0; i < DIM; i++) {
            for (int j = 0; j < DIM; j++) {
                file << tensor_a[i][j] << " ";
            }
            file << std::endl;
        }
        file << std::endl;
        for (int i = 0; i < DIM; i++) {
            for (int j = 0; j < DIM; j++) {
                file << tensor_b[i][j] << " ";
            }
            file << std::endl;
        }
        file << std::endl;
        for (int i = 0; i < DIM; i++) {
            for (int j = 0; j < DIM; j++) {
                file << tensor_r[i][j] << " ";
            }
            file << std::endl;
        }
        file << std::endl;
        file << std::endl;  // Separate test cases
    }

    file.close();

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Test cases are generated and saved in testcase.txt" << std::endl;
    std::cout << std::endl;

    // Read the array from the file
    float array_a[DIM][DIM];
    float array_b[DIM][DIM];
    float array_r[DIM][DIM];

    std::ifstream file_read("testcase.txt");
    std::string line;
    
    for(int i = 0; i < NUM; i++) {
        for (int i = 0; i < DIM; i++) {
            for (int j = 0; j < DIM; j++) {
                file_read >> array_a[i][j];
            }
            file_read.ignore();
            file_read.ignore();
        }
        for (int i = 0; i < DIM; i++) {
            for (int j = 0; j < DIM; j++) {
                file_read >> array_b[i][j];
            }
            file_read.ignore();
            file_read.ignore();
        }
        for (int i = 0; i < DIM; i++) {
            for (int j = 0; j < DIM; j++) {
                file_read >> array_r[i][j];
            }
            file_read.ignore();
            file_read.ignore();
        }
        file_read.ignore();
        file_read.ignore();


        // print the array
        std::cout << "************************* Test case " << i+1 << " *************************" << std::endl;
        std::cout << "Tensor A: " << std::endl;
        for (int i = 0; i < DIM; i++) {
            for (int j = 0; j < DIM; j++) {
                std::cout << array_a[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "Tensor B: " << std::endl;
        for (int i = 0; i < DIM; i++) {
            for (int j = 0; j < DIM; j++) {
                std::cout << array_b[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "Tensor R: " << std::endl;
        for (int i = 0; i < DIM; i++) {
            for (int j = 0; j < DIM; j++) {
                std::cout << array_r[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }


    return 0;
}
