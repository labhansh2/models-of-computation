# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++20 -Wall -Iinclude

# Directories
SRC_DIR := moc
BUILD_DIR := build
INC_DIR := include

# Source files
SRCS := main.cpp $(wildcard $(SRC_DIR)/*.cpp)

# Generate object file paths in build/
OBJS := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Output binary
TARGET := $(BUILD_DIR)/program

# Default target
all: $(TARGET)

# Link object files to create the final binary
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ 

# Compile each source file into build/*.o
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: all
	./$(TARGET)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Phony targets
.PHONY: all clean run
