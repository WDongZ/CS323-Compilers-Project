# Makefile for Bison and Flex

# Tools and flags
BISON = bison
FLEX = flex
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Input files
BISON_FILE = syntax.y
LEX_FILE = lex.l

# Generated files
BISON_C = syntax.tab.c
BISON_H = syntax.tab.h
LEX_C = lex.yy.c
OUTPUT = spl

# Default target: build the final executable
all: $(OUTPUT)

# Compile Bison files
bison: $(BISON_C) $(BISON_H)

$(BISON_C) $(BISON_H): $(BISON_FILE)
	$(BISON) -d $(BISON_FILE)

# Compile Flex files
flex: $(LEX_C)

$(LEX_C): $(LEX_FILE)
	$(FLEX) $(LEX_FILE)

# Link and build the final executable
$(OUTPUT): $(BISON_C) $(LEX_C)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(BISON_C) $(LEX_C)

# Clean all generated files
clean:
	rm -f $(BISON_C) $(BISON_H) $(LEX_C) $(OUTPUT)
