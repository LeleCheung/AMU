#include <iostream>
#include <fstream>
#include <torch/torch.h>

#define DIM 8

int main() {
  torch::Tensor fp_a = torch::rand({DIM, DIM});
  torch::Tensor fp_b = torch::rand({DIM, DIM});
  torch::Tensor fp_result = torch::matmul(fp_a, fp_b);

  /*
  std::cout << "**********TENSOR 1**********" << std::endl;
  std::cout << fp_a << std::endl;
  std::cout << std::endl;
  std::cout << "**********TENSOR 2**********" << std::endl;
  std::cout << fp_b << std::endl;
  std::cout << std::endl;
  std::cout << "**********TENSOR**********" << std::endl;
  std::cout << fp_result << std::endl;
  std::cout << std::endl;
  */

  // save tensor to array
  auto tensor_a = fp_a.accessor<float, 2>(); // 2D accessor
  auto tensor_b = fp_b.accessor<float, 2>(); // 2D accessor
  auto tensor_r = fp_result.accessor<float, 2>(); // 2D accessor

  // save tensor to file testcase
  std::ofstream file;
  file.open("testcase.txt");
  for (int i = 0; i < DIM; i++) {
    for (int j = 0; j < DIM; j++) {
      file << tensor_a[i][j] << " ";
    }
    file << std::endl;
  }
  for (int i = 0; i < DIM; i++) {
    for (int j = 0; j < DIM; j++) {
      file << tensor_b[i][j] << " ";
    }
    file << std::endl;
  }
  for (int i = 0; i < DIM; i++) {
    for (int j = 0; j < DIM; j++) {
      file << tensor_r[i][j] << " ";
    }
    file << std::endl;
  }

  // Read the array from the file
  float array_a[DIM][DIM];
  float array_b[DIM][DIM];
  float array_r[DIM][DIM];

  std::ifstream file_read;
  file_read.open("testcase.txt");
  for (int i = 0; i < DIM; i++) {
    for (int j = 0; j < DIM; j++) {
      file_read >> array_a[i][j];
    }
  }
  for (int i = 0; i < DIM; i++) {
    for (int j = 0; j < DIM; j++) {
      file_read >> array_b[i][j];
    }
  }
  for (int i = 0; i < DIM; i++) {
    for (int j = 0; j < DIM; j++) {
      file_read >> array_r[i][j];
    }
  }


  // Print the array to verify
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "**********FP_A**********" << std::endl;
  for (int i = 0; i < DIM; i++) {
    for (int j = 0; j < DIM; j++) {
        std::cout << array_a[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  std::cout << "**********FP_B**********" << std::endl;
  for (int i = 0; i < DIM; i++) {
    for (int j = 0; j < DIM; j++) {
        std::cout << array_b[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  std::cout << "**********FP_R**********" << std::endl;
  for (int i = 0; i < DIM; i++) {
    for (int j = 0; j < DIM; j++) {
        std::cout << array_r[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

