CC = gcc
CFLAGS = -Wall -Wextra -g -Isrc  # Added -Isrc for header inclusion
SRC_DIR = src
TARGET = knapsack_test
BENCHMARK = knapsack_benchmark
OUTPUT_DIR = outputs

all: $(TARGET) $(BENCHMARK)

$(TARGET): $(SRC_DIR)/test_knapsack.c $(SRC_DIR)/knapsack.c
	@mkdir -p $(OUTPUT_DIR)  # Ensure outputs directory exists
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Build successful: ./$(TARGET)"

$(BENCHMARK): $(SRC_DIR)/benchmark_knapsack.c $(SRC_DIR)/knapsack.c
	@mkdir -p $(OUTPUT_DIR)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Build successful: ./$(BENCHMARK)"

run: $(TARGET)
	./$(TARGET) | tee $(OUTPUT_DIR)/results.txt  # Save output while showing it
	@echo "\nResults saved to $(OUTPUT_DIR)/results.txt"

benchmark: $(BENCHMARK)
	./$(BENCHMARK) | tee $(OUTPUT_DIR)/benchmark_results.txt
	@echo "\nBenchmark results saved to $(OUTPUT_DIR)/benchmark_results.txt"

clean:
	rm -f $(TARGET) $(BENCHMARK)
	@echo "Removed $(TARGET) and $(BENCHMARK)"

.PHONY: all run benchmark clean