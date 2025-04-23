[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/eGOtDXeS)
# Research Paper: The Knapsack Problem
* Name: Shaun Donovan
* Semester: Spring 2025
* Topic: Comparative Analysis of 0/1 and Fractional Knapsack Algorithms
* Link The Repository: https://github.com/Sp25-CS5008-Online-Stern/final-paper-ShaunDonovan23

## Introduction

The knapsack problem is a classic optimization problem that examines how to maximize the value of items in a knapsack without exceeding its weight capacity. This paper explores two solution approaches:

- **0/1 Knapsack (Dynamic Programming)**: Items cannot be divided
- **Fractional Knapsack (Greedy Algorithm)**: Items can be divided

First formally described in the 1957 RAND Corporation report by Dantzig [1], the problem has become fundamental in complexity theory and has numerous real-world applications. Our empirical analysis demonstrates significant performance differences between these approaches, with the Greedy algorithm showing up to 400x speed improvements for large inputs while maintaining near-optimal solutions.

---

## Analysis of Algorithm

### Time Complexity
| Algorithm          | Complexity  | Description                     |
|--------------------|-------------|---------------------------------|
| 0/1 Knapsack (DP)  | O(nW)       | Pseudo-polynomial (n = items, W = capacity) |
| Fractional Knapsack| O(n log n)  | Dominated by sorting operation  |

Our benchmark results confirm these theoretical complexities, showing exponential growth in DP execution time with increasing capacity, while Greedy maintains sub-millisecond performance even for large inputs.

### Space Complexity
| Algorithm          | Complexity  |
|--------------------|-------------|
| 0/1 Knapsack (DP)  | O(nW)       |
| Fractional Knapsack| O(1)        |

**Key Findings**:
- DP guarantees optimality but becomes infeasible for large W [2], as demonstrated by our 43.56ms execution time for W=10000
- Greedy provides faster solutions but only optimal for fractional cases [3]
- Memory optimization using a 1D array was crucial for DP's performance with large W

---

## Empirical Analysis

### Test Results (Verified Execution)

=== Knapsack Algorithm Test Suite ===
Start Time: Wed Apr 16 17:37:21 2025

0/1 Knapsack:
Test 1 - Capacity 50: 220 (Expected: 220) ✓
Test 2 - Capacity 30: 60 (Expected: 60) ✓

Fractional Knapsack: 
Test 1 - Capacity 50: 240.0 (Expected: 240.0) ✓
Test 2 - Capacity 3: 15.0 (Expected: 15.0) ✓

**Performance Observations**:
- DP solution handled discrete constraints perfectly
- Greedy solution showed varying value differences (4.6% to 0.0%) depending on input size
- Greedy algorithm demonstrated consistent sub-millisecond performance across all test cases
- Tests conducted on Mac with arm64 architecture using GCC 12.2

### Performance Metrics

**Table 1**: Runtime comparison (measured using `clock()` in milliseconds)

| Input Size (n) | Capacity (W) | DP Time (ms) | Greedy Time (ms) | Value Difference |
|----------------|--------------|--------------|------------------|------------------|
| 10             | 100          | 0.01         | 0.00             | +4.6%            |
| 100            | 1000         | 0.47         | 0.01             | +0.3%            |
| 1000           | 10000        | 43.56        | 0.11             | +0.0%            |

### Complexity Comparison

**Table 2**: Algorithmic tradeoffs
| Metric          | 0/1 Knapsack (DP) | Fractional Knapsack (Greedy) |
|-----------------|-------------------|------------------------------|
| **Time**        | O(nW)             | O(n log n)                   |
| **Space**       | O(W)              | O(1)                         |
| **Optimality**  | Always            | Only for fractional cases    |
| **Best Use Case**| Small W           | Large n                      |

**Key Observations**:
1. Greedy is ~400x faster for n=1000 due to better time complexity
2. DP's performance degrades significantly with larger W (43.56ms for W=10000)
3. Value difference decreases with input size, suggesting Greedy becomes more optimal for larger problems
4. Memory optimization using 1D array was crucial for DP's performance with large W

---

## Application

### Real-World Uses
1. **Cryptography**:
    - Used in Merkle-Hellman knapsack cryptosystem [4]
    - DP approach for exact solutions in key generation

2. **Resource Allocation**:
    - Cloud task scheduling (Azure's VM allocation) [5]
    - 5G network bandwidth distribution [6]

**Industry Impact**:
- Amazon uses knapsack variants for:
    - Warehouse robot loading optimization
    - EC2 spot instance pricing

---

## Implementation

### **Technical Specifications**
| **Component**       | **Choice**                          |
|----------------------|-------------------------------------|
| Language             | C (C11 standard)                    |
| Compiler             | GCC 12.2 (`-Wall -Wextra -g`)       |
| Libraries            | `stdio.h`, `stdlib.h`, `assert.h`   |
| Testing              | Custom test harness (8 test cases)   |
| Benchmarking         | Custom benchmark suite (3 test sizes)|
| Timing              | `clock()` from `time.h`             |

### **Key Challenges**
1. **Memory Efficiency**:
    - Problem: DP's O(nW) space was prohibitive for large `W`.
    - Solution: Used a rolling 1D array (O(W) space):
      ```c
      int dp[W+1] = {0};
      for (int i = 0; i < n; i++) {
          for (int w = W; w >= items[i].weight; w--) {
              dp[w] = max(dp[w], items[i].value + dp[w - items[i].weight]);
          }
      }
      ```

2. **Precision in Greedy**:
    - Avoided floating-point errors by comparing ratios as integers:
      ```c
      return (itemA->value * itemB->weight) > (itemB->value * itemA->weight);
      ```

### **Code Walkthrough**
#### Dynamic Programming
```c
int knapsackDP(Item items[], int n, int W) {
    int dp[W+1] = {0};  // Space-optimized
    for (int i = 0; i < n; i++) {
        for (int w = W; w >= items[i].weight; w--) {
            if (dp[w - items[i].weight] + items[i].value > dp[w]) {
                dp[w] = dp[w - items[i].weight] + items[i].value;
            }
        }
    }
    return dp[W];
}
```
- Key Insight: Processes items in reverse to avoid overwriting.
#### Greedy Algorithm
```c
double knapsackGreedy(Item items[], int n, int W) {
    qsort(items, n, sizeof(Item), compare);  // O(n log n)
    double total = 0.0;
    for (int i = 0; i < n && W > 0; i++) {
        int take = min(items[i].weight, W);
        total += take * ((double)items[i].value / items[i].weight);
        W -= take;
    }
    return total;
}
```
- Optimization: Early exit when knapsack is full.

---

## Summary

**Key Findings:**
1. DP remains essential for exact 0/1 solutions despite higher complexity
2. Greedy algorithms provide faster but approximate solutions
3. Modern applications span from cloud computing to cryptography
4. Memory optimization is crucial for DP's performance with large inputs

**Lessons Learned:**
- Problem constraints dictate algorithm choice
- Systematic testing prevents implementation errors
- Memory optimization is crucial for DP solutions
- Greedy algorithms can provide near-optimal solutions with significantly better performance

---

## References
1. Dantzig, G. B. (1957). Discrete-Variable Extremum Problems. RAND Corporation.
2. Garey, M. R., & Johnson, D. S. (1979). Computers and Intractability. W.H. Freeman.
3. Cormen, T. H., et al. (2022). Introduction to Algorithms (4th ed.). MIT Press.
4. Merkle, R., & Hellman, M. (1978). Hiding Information in Trapdoor Knapsacks. IEEE.
5. Microsoft Azure (2023). Virtual Machine Scale Sets - Design Considerations. Microsoft Learn. https://learn.microsoft.com/en-us/azure/virtual-machine-scale-sets/virtual-machine-scale-sets-design-overview
6. 3GPP TS 28.541 (2022). Management and orchestration; 5G Network Resource Model (NRM). 3GPP. https://www.3gpp.org/ftp/Specs/archive/28_series/28.541/

Thank you