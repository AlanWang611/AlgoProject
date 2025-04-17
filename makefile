# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

# Source file
SRC = MaximumMeetingTimes.cpp

# Output executable
TARGET = MaximumMeetingTimes

# Input file
INPUT = input.txt

# Default target
all: compile run

# Compile the program
compile:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Run the program
run:
	./$(TARGET) < $(INPUT)

# Clean up generated files
clean:
	rm -f $(TARGET) output.txt

# Phony targets (not actual files)
.PHONY: all compile run clean
