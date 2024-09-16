#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define N 4 // Number of cities

// Function to find the minimum edge cost
int findMinCost(int costMatrix[N][N], int i, int excluded[]) {
    int minCost = INT_MAX;
    for (int j = 0; j < N; j++) {
        if (!excluded[j] && costMatrix[i][j] < minCost && i != j) {
            minCost = costMatrix[i][j];
        }
    }
    return minCost;
}

// Function to find the second minimum edge cost
int findSecondMinCost(int costMatrix[N][N], int i, int excluded[]) {
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < N; j++) {
        if (i == j) continue;
        if (!excluded[j]) {
            if (costMatrix[i][j] <= first) {
                second = first;
                first = costMatrix[i][j];
            } else if (costMatrix[i][j] <= second && costMatrix[i][j] != first) {
                second = costMatrix[i][j];
            }
        }
    }
    return second;
}

// Function to calculate the lower bound
int calculateLowerBound(int costMatrix[N][N], int excluded[]) {
    int lowerBound = 0;
    for (int i = 0; i < N; i++) {
        if (!excluded[i]) {
            lowerBound += (findMinCost(costMatrix, i, excluded) + findSecondMinCost(costMatrix, i, excluded)) / 2;
        }
    }
    return lowerBound;
}

// Function to solve the TSP using Backtrack Branch and Bound
void TSP(int costMatrix[N][N], int path[], bool visited[], int currentPos, int n, int cost, int *minCost, int bound) {
    if (n == N) {
        if (costMatrix[currentPos][0] != 0) {
            int currentResult = cost + costMatrix[currentPos][0];
            if (currentResult < *minCost) {
                *minCost = currentResult;
                path[N] = 0;
            }
        }
        return;
    }

    for (int i = 0; i < N; i++) {
        if (costMatrix[currentPos][i] != 0 && !visited[i]) {
            int tempBound = bound;
            cost += costMatrix[currentPos][i];
            bound -= ((findMinCost(costMatrix, currentPos, visited) + findMinCost(costMatrix, i, visited)) / 2);

            if (bound + cost < *minCost) {
                path[n] = i;
                visited[i] = true;
                TSP(costMatrix, path, visited, i, n + 1, cost, minCost, bound);
            }

            cost -= costMatrix[currentPos][i];
            bound = tempBound;
            visited[i] = false;
        }
    }
}

// Function to find the minimum cost path
void findMinCostPath(int costMatrix[N][N]) {
    int path[N + 1];
    bool visited[N] = { false };
    int minCost = INT_MAX;

    int bound = calculateLowerBound(costMatrix, visited);
    visited[0] = true;
    path[0] = 0;

    TSP(costMatrix, path, visited, 0, 1, 0, &minCost, bound);

    printf("Minimum cost: %d\n", minCost);
    printf("Path: ");
    for (int i = 0; i <= N; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

int main() {
    int costMatrix[N][N] = {
        { 0, 10, 15, 20 },
        { 10, 0, 35, 25 },
        { 15, 35, 0, 30 },
        { 20, 25, 30, 0 }
    };

    findMinCostPath(costMatrix);
    return 0;
}
