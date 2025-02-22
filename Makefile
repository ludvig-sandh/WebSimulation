# Compiler and Flags
CXX = g++
CC = gcc
CXXFLAGS = -Wall -Wextra -std=c++20
CCFLAGS = -c -Wall -Wextra
DEBUG_FLAGS = -g -O0 -fno-inline -fno-omit-frame-pointer -ggdb -fno-elide-constructors

INCLUDE_EXTERNAL_DIR = -Iinclude/external
INCLUDE_DIR = -Iinclude
LIBRARY_DIR = -Llib
LIBRARIES = -lglfw3 -lopengl32 -lgdi32 -luser32 -lshell32

# Directories
SRC_DIR = src
SRC_EXTERNAL_DIR = src/external
BUILD_DIR = build
BIN_DIR = bin

# Source and Object Files
SRC_CPP = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_CPP = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_CPP))

SRC_C = $(wildcard $(SRC_EXTERNAL_DIR)/*.c)
OBJ_C = $(patsubst $(SRC_EXTERNAL_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_C))

# Output Executable
TARGET = $(BIN_DIR)/websimulation

# Default target (release mode)
all: CXXFLAGS += -O2  # Optimization for release build
all: CCFLAGS += -O2
all: $(TARGET)

# Debug target
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: CCFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

# Linking Step
$(TARGET): $(OBJ_CPP) $(OBJ_C)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ $(LIBRARY_DIR) $(LIBRARIES) -o $@

# Compiling .cpp files into .o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< $(INCLUDE_DIR) $(INCLUDE_EXTERNAL_DIR) -o $@

# Compiling glad.c file
$(BUILD_DIR)/glad.o: $(SRC_EXTERNAL_DIR)/glad.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CCFLAGS) -c $< $(INCLUDE_EXTERNAL_DIR) -o $@

# Clean Target
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Print Debug Info
print:
	@echo "Sources (c++): $(SRC_CPP)"
	@echo "Objects (c++): $(OBJ_CPP)"
	@echo "Sources (c): $(SRC_C)"
	@echo "Objects (c): $(OBJ_C)"
