# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I/usr/local/include

# Google Test configuration
GTEST_LIB = -lgtest -lgtest_main -pthread
GTEST_INCLUDE_DIR = /usr/local/include
GTEST_LIB_DIR = /usr/local/lib

# Source files and directories
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

# List of source files and object files
SRCS = $(filter-out $(SRC_DIR)/main.cpp, $(wildcard $(SRC_DIR)/*.cpp))
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

MAIN_SRC = $(SRC_DIR)/main.cpp
MAIN_OBJ = $(MAIN_SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Executable names
EXE = my_executable
TEST_EXE = runTests

# Build targets
all: $(EXE) $(TEST_EXE)

# Rule to build the main executable
$(EXE): $(OBJS) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(MAIN_OBJ)

# Rule to build the test executable
$(TEST_EXE): $(TEST_OBJS) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_OBJS) $(OBJS) $(GTEST_LIB)

# Rule to compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(GTEST_INCLUDE_DIR) -c $< -o $@

# Rule to compile test source files into object files
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(GTEST_INCLUDE_DIR) -c $< -o $@

# Rule to compile main.cpp into object file
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(BUILD_DIR) $(EXE) $(TEST_EXE)

# Run tests
test: $(TEST_EXE)
	./$(TEST_EXE)

.PHONY: all clean test
