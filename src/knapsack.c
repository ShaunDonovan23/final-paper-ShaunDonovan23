#include "knapsack.h"
#include <stdio.h>
#include <stdlib.h>

// Helper function for Greedy: Sort items by value/weight ratio (descending)
int compare(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    double ratioA = (double)itemA->value / itemA->weight;
    double ratioB = (double)itemB->value / itemB->weight;
    return (ratioA < ratioB) ? 1 : -1; // Sort descending
}

// Dynamic Programming (0/1 Knapsack)
int knapsackDP(Item items[], int n, int W) {
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((W + 1) * sizeof(int));
    }

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (items[i - 1].weight <= w) {
                dp[i][w] = (items[i - 1].value + dp[i - 1][w - items[i - 1].weight] > dp[i - 1][w])
                           ? items[i - 1].value + dp[i - 1][w - items[i - 1].weight]
                           : dp[i - 1][w];
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int result = dp[n][W];
    for (int i = 0; i <= n; i++) free(dp[i]);
    free(dp);
    return result;
}

// Greedy (Fractional Knapsack)
double knapsackGreedy(Item items[], int n, int W) {
    qsort(items, n, sizeof(Item), compare); // Sort by value/weight ratio
    double totalValue = 0.0;
    int remainingWeight = W;

    for (int i = 0; i < n; i++) {
        if (remainingWeight <= 0) break;
        if (items[i].weight <= remainingWeight) {
            totalValue += items[i].value;
            remainingWeight -= items[i].weight;
        } else {
            totalValue += (double)items[i].value * remainingWeight / items[i].weight;
            remainingWeight = 0;
        }
    }
    return totalValue;
}