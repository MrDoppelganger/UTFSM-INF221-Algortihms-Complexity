CXX = g++
CXXFLAGS = -O3 -Wall -std=c++11

ALGORITHMS = algorithms/naive.cpp algorithms/strassen.cpp
MAIN = matrix_multiplication.cpp
EXEC = matrix_multiplication

INPUT_DIR = data/matrix_input
OUTPUT_DIR = data/matrix_output
MEASURE_DIR = data/measurements

all: $(EXEC)

$(EXEC): $(MAIN) $(ALGORITHMS)
	$(CXX) $(CXXFLAGS) $(MAIN) $(ALGORITHMS) -o $(EXEC)

run: $(EXEC)
	@mkdir -p $(OUTPUT_DIR) $(MEASURE_DIR)
	@echo "algorithm,n,time_seconds,memory_kb" > $(MEASURE_DIR)/results.csv
	@for file1 in $(INPUT_DIR)/*_1.txt; do \
		file2=$${file1%_1.txt}_2.txt; \
		base=$$(basename $$file1 _1.txt); \
		echo "Running Benchmarks for $$base..."; \
		./$(EXEC) naive $$file1 $$file2 $(OUTPUT_DIR)/$${base}_naive_out.txt $(MEASURE_DIR)/results.csv; \
		./$(EXEC) strassen $$file1 $$file2 $(OUTPUT_DIR)/$${base}_strassen_out.txt $(MEASURE_DIR)/results.csv; \
	done

clean:
	rm -f $(EXEC)
	rm -rf $(OUTPUT_DIR)/*
	rm -rf $(MEASURE_DIR)/*

.PHONY: all run clean
