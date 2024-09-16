**Definition:** Algorithmic techniques for solving combinatorial optimization problems by exploring possible solutions incrementally and abandoning those that do not meet the criteria.
**Loop Characteristics:** Recursion with loops trying out possible steps.

## Sample Code
```cpp
// N-Queens problem
bool solveNQueens(int board[N][N], int col) {
    if (col >= N)
        return true;
    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col)) {
            board[i][col] = 1;
            if (solveNQueens(board, col + 1))
                return true;
            board[i][col] = 0;
        }
    }
    return false;
}