#ifndef KNAPSACK_H
#define KNAPSACK_H

typedef struct {
    int value;
    int weight;
} Item;

int knapsackDP(Item items[], int n, int W);
double knapsackGreedy(Item items[], int n, int W);

#endif