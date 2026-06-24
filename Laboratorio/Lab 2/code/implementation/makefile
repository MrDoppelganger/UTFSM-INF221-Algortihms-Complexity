CXX = g++
CXXFLAGS = -std=c++17 -Wall -O3 -I./algorithms

# Carpetas
ALGO_DIR = algorithms
DATA_DIR = data
OUT_DIR = $(DATA_DIR)/outputs
MEAS_DIR = $(DATA_DIR)/measurements
TC_DIR = $(DATA_DIR)/inputs
BUILD_DIR = build

# Archivos fuente y objetos
SRCS = general.cpp \
       $(ALGO_DIR)/brute-force.cpp \
       $(ALGO_DIR)/dynamic-programming.cpp \
       $(ALGO_DIR)/greedy1.cpp \
       $(ALGO_DIR)/greedy2.cpp
OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Ejecutable
TARGET = general

all: directories $(TARGET)

directories:
	mkdir -p $(OUT_DIR)
	mkdir -p $(MEAS_DIR)
	mkdir -p $(TC_DIR)
	mkdir -p $(BUILD_DIR)/$(ALGO_DIR)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run_tests: $(TARGET)
	@echo "Ejecutando pruebas sobre los casos generados..."
	@for file in $(TC_DIR)/testcases_*.txt; do \
		if [ -f "$$file" ]; then \
			./$(TARGET) "$$file"; \
		fi \
	done
	@echo "Pruebas finalizadas."

generate_data: directories
	python3 scripts/testcases_generator.py

generate_plots: directories
	python3 scripts/plot_generator.py

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

clean_data:
	rm -rf $(OUT_DIR)/* $(MEAS_DIR)/* $(TC_DIR)/*

clean_graficos:
	rm -rf $(DATA_DIR)/plots/*

clean_all: clean clean_data clean_graficos

.PHONY: all directories run_tests clean clean_data clean_graficos clean_all generate_data generate_plots
