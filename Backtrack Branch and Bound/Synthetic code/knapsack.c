#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 4 // Number of items

typedef struct {
    int weight;
    int value;
} Item;

typedef struct {
    int level;
    int profit;
    int weight;
    float bound;
} Node;

// Comparison function for sorting items by value/weight ratio
int cmp(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    double r1 = (double)itemA->value / itemA->weight;
    double r2 = (double)itemB->value / itemB->weight;
    return r2 - r1;
}

// Calculate bound for node
float calculateBound(Node u, int n, int W, Item items[]) {
    if (u.weight >= W) return 0;
    float profitBound = u.profit;
    int j = u.level + 1;
    int totWeight = u.weight;
    
    while (j < n && totWeight + items[j].weight <= W) {
        totWeight += items[j].weight;
        profitBound += items[j].value;
        j++;
    }
    
    if (j < n) {
        profitBound += (W - totWeight) * items[j].value / items[j].weight;
    }
    
    return profitBound;
}

// Knapsack using Branch and Bound
int knapsack(int W, Item items[], int n) {
    qsort(items, n, sizeof(Item), cmp);

    Node Q[100];  // Simple queue to hold nodes
    int front = 0, rear = 0;

    Node u, v;
    u.level = -1;
    u.profit = u.weight = 0;
    u.bound = calculateBound(u, n, W, items);
    Q[rear++] = u;

    int maxProfit = 0;
    
    while (front < rear) {
        u = Q[front++];
        if (u.level == -1) v.level = 0;
        if (u.level == n - 1) continue;
        
        v.level = u.level + 1;
        
        // Taking the item
        v.weight = u.weight + items[v.level].weight;
        v.profit = u.profit + items[v.level].value;
        
        if (v.weight <= W && v.profit > maxProfit) {
            maxProfit = v.profit;
        }
        
        v.bound = calculateBound(v, n, W, items);
        
        if (v.bound > maxProfit) {
            Q[rear++] = v;
        }
        
        // Not taking the item
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = calculateBound(v, n, W, items);
        
        if (v.bound > maxProfit) {
            Q[rear++] = v;
        }
    }
    
    return maxProfit;
}

int main() {
    Item items[N] = {
        {2, 40}, // {weight, value}
        {3, 50},
        {4, 60},
        {5, 70}
    };
    int W = 5; // Maximum capacity of knapsack

    printf("Maximum profit: %d\n", knapsack(W, items, N));

    return 0;
}
