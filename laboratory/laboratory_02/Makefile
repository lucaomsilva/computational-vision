# Makefile for managing the C++/OpenCV development environment and build processes.
#
# This Makefile provides two build methods:
#   1. 'simple': Direct compilation with g++ (for single-file projects).
#   2. 'cmake': Recommended method using CMake (for scalable projects).
#
# To see available commands, run: make

# Shell colors for help message
cc_blue  := \033[0;34m
cc_red   := \033[0;31m
cc_reset := \033[0m

# --- Variables for 'simple' build ---
CXX = g++
CXXFLAGS = -Wall -std=c++11 $(shell pkg-config --cflags opencv4)
LDFLAGS = $(shell pkg-config --libs opencv4)
SRC = src/main.cpp
EXEC_SIMPLE = main

# --- Variables for 'cmake' build ---
BUILD_DIR = build
EXEC_CMAKE = main

# The 'help' target is the default when 'make' is run without arguments.
.PHONY: all
all: help

.PHONY: help
help: ## Show this help message
	@echo 'Usage: make [target]'
	@echo ''
	@echo 'Recommended (CMake) Targets:'
	@grep -E '^[a-zA-Z_-]+:.*?## CMAKE:.*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## CMAKE: "}; {printf "  $(cc_blue)%-15s$(cc_reset) %s\n", $$1, $$2}'
	@echo ''
	@echo 'Simple (Terminal) Targets:'
	@grep -E '^[a-zA-Z_-]+:.*?## SIMPLE:.*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## SIMPLE: "}; {printf "  $(cc_blue)%-15s$(cc_reset) %s\n", $$1, $$2}'
	@echo ''
	@echo 'Other Targets:'
	@grep -E '^[a-zA-Z_-]+:.*?## OTHER:.*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## OTHER: "}; {printf "  $(cc_blue)%-15s$(cc_reset) %s\n", $$1, $$2}'

# --- CMake Targets (Recommended) ---
.PHONY: build
build: build-cmake ## CMAKE: (Default) Configure and compile the project using CMake

.PHONY: run
run: run-cmake   ## CMAKE: (Default) Run the CMake-built run program

.PHONY: clean
clean: clean-cmake clean-unzip ## CMAKE: (Default) Remove build artifacts and unzipped files

.PHONY: build-cmake
build-cmake: ## CMAKE: Configure and compile the project using CMake
	@echo "--- Configuring and building with CMake ---"
	@mkdir -p $(BUILD_DIR)
	@cmake -S . -B $(BUILD_DIR)
	@cmake --build $(BUILD_DIR)

.PHONY: run-cmake
run-cmake: build-cmake ## CMAKE: Run the CMake-built run program
	@echo "--- Running CMake-built run program ---"
	./$(BUILD_DIR)/$(EXEC_CMAKE)

.PHONY: clean-cmake
clean-cmake: ## CMAKE: Remove the CMake build directory and artifacts
	@echo "Cleaning up CMake build directory..."
	rm -rf $(BUILD_DIR)

# --- Simple Terminal Targets ---
.PHONY: build-simple
build-simple: $(EXEC_SIMPLE) ## SIMPLE: Compile main.cpp directly with g++

$(EXEC_SIMPLE): $(SRC)
	@echo "--- Compiling with g++ directly ---"
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXEC_SIMPLE) $(LDFLAGS)

.PHONY: run-simple
run-simple: build-simple ## SIMPLE: Run the program compiled with g++
	@echo "--- Running simple-built run program ---"
	./$(EXEC_SIMPLE)

.PHONY: clean-simple
clean-simple: ## SIMPLE: Remove the executable from the simple build
	@echo "Cleaning up simple-build executable..."
	rm -f $(EXEC_SIMPLE)

# --- Other Targets ---
.PHONY: unzip
unzip: ## OTHER: Unzip the images file
	@echo "--- Unzipping images file ---"
	@if [ -f img/sel_data.zip ]; then \
		unzip -o img/sel_data.zip -d img/; \
	else \
		echo "[$(cc_red)FAILED$(cc_reset)] File img/sel_data.zip not found."; \
	fi

.PHONY: clean-unzip
clean-unzip: ## OTHER: Remove the unzipped image directory
	@echo "--- Cleaning up unzipped images ---"
	@rm -rf img/sel_data
