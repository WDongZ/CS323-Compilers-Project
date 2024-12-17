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

OUTPUT = a

all: $(OUTPUT)

bison: $(BISON_C) $(BISON_H)

$(BISON_C) $(BISON_H): $(BISON_FILE)
	$(BISON) -d $(BISON_FILE)

flex: $(LEX_C)

$(LEX_C): $(LEX_FILE)
	$(FLEX) $(LEX_FILE)

$(OUTPUT): $(BISON_C) $(LEX_C)
	$(CXX) $(CXXFLAGS) -g -o $(OUTPUT) $(BISON_C) $(LEX_C) semantic.cpp symbol.cpp type.cpp ir_generate.cpp three_address_code.cpp

clean:
	rm -f $(BISON_C) $(BISON_H) $(LEX_C) $(OUTPUT)
