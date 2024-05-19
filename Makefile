# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Iinclude -Wall -Wextra

# Directories
SRC_DIR = src
OBJ_DIR = build
INC_DIR = include

# Target executable
TARGET = main

# Source files
SRCS = main.cpp $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS = $(SRCS:.cpp=.o)
OBJS := $(addprefix $(OBJ_DIR)/, $(notdir $(OBJS)))

# Default rule
all: $(TARGET)

# Link target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure the build directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Phony targets
.PHONY: all clean


