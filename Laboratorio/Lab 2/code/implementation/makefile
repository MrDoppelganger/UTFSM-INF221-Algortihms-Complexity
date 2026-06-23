CXX = g++
CXXFLAGS = -std=c++17 -Wall -O3 -I./algorithms

# Carpetas
ALGO_DIR = algorithms
DATA_DIR = data
OUT_DIR = $(DATA_DIR)/outputs
MEAS_DIR = $(DATA_DIR)/measurements
TC_DIR = $(DATA_DIR)/inputs

# Archivos fuente y objetos
SRCS = general.cpp \
       $(ALGO_DIR)/brute-force.cpp \
       $(ALGO_DIR)/dynamic-programming.cpp \
       $(ALGO_DIR)/greedy1.cpp \
       $(ALGO_DIR)/greedy2.cpp
OBJS = $(SRCS:.cpp=.o)

# Ejecutable
TARGET = general

all: directories $(TARGET)

directories:
	mkdir -p $(OUT_DIR)
	mkdir -p $(MEAS_DIR)
	mkdir -p $(TC_DIR)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run_tests: $(TARGET)
	@echo "Ejecutando pruebas sobre los casos generados..."
	@for file in $(TC_DIR)/testcases_*.txt; do \
		if [ -f "$$file" ]; then \
			./$(TARGET) "$$file"; \
		fi \
	done
	@echo "Pruebas finalizadas."

clean:
	rm -f $(OBJS) $(TARGET)

clean_data:
	rm -rf $(OUT_DIR)/* $(MEAS_DIR)/* $(TC_DIR)/*

.PHONY: all directories run_tests clean clean_data
