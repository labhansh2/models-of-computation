# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -pedantic -Iinclude

# Directories
SRC_DIR := moc
BUILD_DIR := build
INC_DIR := include

# pugixml setup
PUGIXML_DIR := $(BUILD_DIR)/pugixml
PUGIXML_REPO := https://github.com/zeux/pugixml.git
PUGIXML_SRC := $(PUGIXML_DIR)/src/pugixml.cpp
PUGIXML_OBJ := $(BUILD_DIR)/pugixml.o
CXXFLAGS += -I$(PUGIXML_DIR)/src

# Source files
SRCS := main.cpp $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Output binary
TARGET := $(BUILD_DIR)/program

# Default target
all: pugixml $(TARGET)

# Build pugixml
pugixml: $(PUGIXML_OBJ)

$(PUGIXML_DIR):
	git clone --depth 1 --branch v1.13 $(PUGIXML_REPO) $(PUGIXML_DIR)

$(PUGIXML_OBJ): $(PUGIXML_DIR)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $(PUGIXML_SRC) -o $(PUGIXML_OBJ)

# Link object files to create the final binary
$(TARGET): $(OBJS) $(PUGIXML_OBJ)
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

# Run tests
test: all
	./$(TARGET)

# Phony targets
.PHONY: all clean run test pugixml
