#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "knapsack.h"

// Function to generate random items
void generate_random_items(Item items[], int n, int max_value, int max_weight) {
    for (int i = 0; i < n; i++) {
        items[i].value = rand() % max_value + 1;
        items[i].weight = rand() % max_weight + 1;
    }
}

// Function to measure execution time in milliseconds
double measure_time(Item items[], int n, int W, int is_dp) {
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    if (is_dp) {
        knapsackDP(items, n, W);
    } else {
        knapsackGreedy(items, n, W);
    }
    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC * 1000.0;
    return cpu_time_used;
}

// Function to calculate value difference between DP and Greedy
double calculate_value_difference(Item items[], int n, int W) {
    int dp_value = knapsackDP(items, n, W);
    double greedy_value = knapsackGreedy(items, n, W);
    return ((greedy_value - dp_value) / dp_value) * 100.0;
}

int main() {
    // Test configurations
    int test_sizes[] = {10, 100, 1000};
    int capacities[] = {100, 1000, 10000};
    int num_tests = sizeof(test_sizes) / sizeof(test_sizes[0]);
    
    printf("=== Knapsack Algorithm Benchmark ===\n");
    printf("| Input Size (n) | Capacity (W) | DP Time (ms) | Greedy Time (ms) | Value Difference |\n");
    printf("|----------------|--------------|--------------|------------------|------------------|\n");
    
    for (int i = 0; i < num_tests; i++) {
        int n = test_sizes[i];
        int W = capacities[i];
        
        // Allocate memory for items
        Item* items = (Item*)malloc(n * sizeof(Item));
        if (!items) {
            printf("Memory allocation failed\n");
            return 1;
        }
        
        // Generate random items
        generate_random_items(items, n, 1000, 100);
        
        // Measure execution times
        double dp_time = measure_time(items, n, W, 1);
        double greedy_time = measure_time(items, n, W, 0);
        double value_diff = calculate_value_difference(items, n, W);
        
        // Print results
        printf("| %-14d | %-12d | %-12.2f | %-16.2f | %-16.1f%% |\n",
               n, W, dp_time, greedy_time, value_diff);
        
        free(items);
    }
    
    return 0;
} 