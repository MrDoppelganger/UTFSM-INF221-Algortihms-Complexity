CXX = g++
CXXFLAGS = -O3 -Wall -std=c++11

ALGORITHMS = algorithms/mergesort.cpp algorithms/quicksort.cpp algorithms/sort.cpp
MAIN = sorting.cpp
EXEC = sorting

INPUT_DIR = data/array_input
OUTPUT_DIR = data/array_output
MEASURE_DIR = data/measurements

all: $(EXEC)

$(EXEC): $(MAIN) $(ALGORITHMS)
	$(CXX) $(CXXFLAGS) $(MAIN) $(ALGORITHMS) -o $(EXEC)

run: $(EXEC)
	@mkdir -p $(OUTPUT_DIR) $(MEASURE_DIR)
	@echo "algorithm,n,time_seconds,memory_kb" > $(MEASURE_DIR)/results.csv
	@for file in $(INPUT_DIR)/*.txt; do \
		filename=$$(basename $$file .txt); \
		echo "Running Benchmarks for $$filename..."; \
		./$(EXEC) mergesort $$file $(OUTPUT_DIR)/$${filename}_mergesort_out.txt $(MEASURE_DIR)/results.csv; \
		./$(EXEC) quicksort $$file $(OUTPUT_DIR)/$${filename}_quicksort_out.txt $(MEASURE_DIR)/results.csv; \
		./$(EXEC) stdsort $$file $(OUTPUT_DIR)/$${filename}_stdsort_out.txt $(MEASURE_DIR)/results.csv; \
	done

clean:
	rm -f $(EXEC)
	rm -rf $(OUTPUT_DIR)/*
	rm -rf $(MEASURE_DIR)/*

.PHONY: all run clean
