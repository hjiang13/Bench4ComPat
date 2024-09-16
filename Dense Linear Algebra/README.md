## Dense Linear Algebra

## Definition
Operations involving dense matrices, such as matrix multiplications and factorizations.
## Loop characteristics
Nested loops iterating on matrix dimensions.
## Sample Code
**Matrix Multiplication**

The following code performs matrix multiplication of two `n x n` matrices `A` and `B` to produce a result matrix `C`.

```cpp
// Matrix multiplication
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        C[i][j] = 0;
        for (int k = 0; k < n; k++) {
            C[i][j] += A[i][k] * B[k][j];
        }
    }
}
