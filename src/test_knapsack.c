#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "knapsack.h"

// ======================
// TEST UTILITY FUNCTIONS
// ======================

void print_test_header(const char* algorithm) {
    printf("\n══════════════════════════════════════\n");
    printf("  Testing %s Knapsack Algorithm\n", algorithm);
    printf("══════════════════════════════════════\n");
}

void print_test_case(int id, const char* description, const char* items_str, 
                     int capacity, const char* expected) {
    printf("Test Case %d: %s\n", id, description);
    printf("  Items: %s\n", items_str);
    printf("  Capacity: %d\n", capacity);
    printf("  Expected: %s → ", expected);
}

void print_passed() {
    printf("\033[0;32mPassed\033[0m\n");  // Colored output (green)
}

// ======================
// DYNAMIC PROGRAMMING TESTS (0/1 KNAPSACK)
// ======================

void test_knapsackDP() {
    print_test_header("0/1 (Dynamic Programming)");
    
    // Test Case 1: Basic scenario
    Item items1[] = {{60, 10}, {100, 20}, {120, 30}};
    print_test_case(1, "Basic selection", 
                   "(60,10), (100,20), (120,30)", 50, "220");
    assert(knapsackDP(items1, 3, 50) == 220);
    print_passed();

    // Test Case 2: Full capacity utilization
    Item items2[] = {{10, 5}, {20, 10}, {30, 15}};
    print_test_case(2, "Exact capacity fit", 
                   "(10,5), (20,10), (30,15)", 30, "60");
    assert(knapsackDP(items2, 3, 30) == 60);
    print_passed();

    // Test Case 3: Empty knapsack
    Item items3[] = {{10, 5}};
    print_test_case(3, "Zero capacity", 
                   "(10,5)", 0, "0");
    assert(knapsackDP(items3, 1, 0) == 0);
    print_passed();

    // Test Case 4: All items too heavy
    Item items4[] = {{100, 100}, {200, 200}};
    print_test_case(4, "All items exceed capacity", 
                   "(100,100), (200,200)", 10, "0");
    assert(knapsackDP(items4, 2, 10) == 0);
    print_passed();
}

// ======================
// GREEDY ALGORITHM TESTS (FRACTIONAL KNAPSACK)
// ======================

void test_knapsackGreedy() {
    print_test_header("Fractional (Greedy)");
    
    // Test Case 1: Basic fractional scenario
    Item items1[] = {{60, 10}, {100, 20}, {120, 30}};
    print_test_case(1, "Fractional selection", 
                   "(60,10), (100,20), (120,30)", 50, "240.0");
    assert(knapsackGreedy(items1, 3, 50) == 240.0);
    print_passed();

    // Test Case 2: Exact fit (no fractions needed)
    Item items2[] = {{10, 2}, {5, 1}};
    print_test_case(2, "Perfect fit without fractions", 
                   "(10,2), (5,1)", 3, "15.0");
    assert(knapsackGreedy(items2, 2, 3) == 15.0);
    print_passed();

    // Test Case 3: Zero capacity
    Item items3[] = {{10, 5}};
    print_test_case(3, "Zero capacity", 
                   "(10,5)", 0, "0.0");
    assert(knapsackGreedy(items3, 1, 0) == 0.0);
    print_passed();

    // Test Case 4: Single fractional item
    Item items4[] = {{30, 5}};
    print_test_case(4, "Single fractional item", 
                   "(30,5)", 3, "18.0");
    assert(knapsackGreedy(items4, 1, 3) == 18.0);
    print_passed();
}

// ======================
// MAIN TEST RUNNER
// ======================

int main() {
    // Print execution timestamp
    time_t now;
    time(&now);
    printf("\n=== Knapsack Algorithm Test Suite ===\n");
    printf("Start Time: %s\n", ctime(&now));
    
    // Run test suites with detailed output
    test_knapsackDP();
    test_knapsackGreedy();
    
    // Print completion timestamp
    time(&now);
    printf("\n\033[1;32m✔ All tests passed successfully!\033[0m\n");
    printf("End Time: %s\n", ctime(&now));
    
    return 0;
}