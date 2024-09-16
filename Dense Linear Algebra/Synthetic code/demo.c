#include <iostream>
#include <vector>

// Function for matrix multiplication
void matrix_multiply(const std::vector<std::vector<float>>& A, 
                     const std::vector<std::vector<float>>& B, 
                     std::vector<std::vector<float>>& C, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int N = 3; // Size of the matrix
    std::vector<std::vector<float>> A(N, std::vector<float>(N));
    std::vector<std::vector<float>> B(N, std::vector<float>(N));
    std::vector<std::vector<float>> C(N, std::vector<float>(N));

    // Initializing matrix A
    A = {{1.0, 2.0, 3.0}, 
         {4.0, 5.0, 6.0}, 
         {7.0, 8.0, 9.0}};
    
    // Initializing matrix B
    B = {{9.0, 8.0, 7.0}, 
         {6.0, 5.0, 4.0}, 
         {3.0, 2.0, 1.0}};
    
    // Perform matrix multiplication
    matrix_multiply(A, B, C, N);

    // Display result
    std::cout << "Result matrix C: " << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << C[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
