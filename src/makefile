# Compiler
CXX = g++

# Flags for the compiler
CXXFLAGS = -std=c++14 -Wall -Wextra

# Include directories
INCLUDES = -I/path/to/gtest/include   # Replace /path/to/gtest/include with the actual path to Google Test headers

# Library directories
LIB_DIRS = -L/path/to/gtest/lib       # Replace /path/to/gtest/lib with the actual path to Google Test library

# Libraries
LIBS = -lgtest -lgtest_main -lpthread

# Source files
SRCS = bank_test.cpp   # Add other source files if any

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable
TARGET = bank_test

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LIB_DIRS) $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS) $(TARGET)
