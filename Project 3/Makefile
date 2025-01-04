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

OUTPUT = splc
TARGET_DIR = bin
TARGET = $(TARGET_DIR)/$(OUTPUT)

all: $(TARGET)

$(TARGET): $(BISON_C) $(LEX_C)
	mkdir -p $(TARGET_DIR)
	$(CXX) $(CXXFLAGS) -g -o $(TARGET) $(BISON_C) $(LEX_C) symbol.cpp type.cpp ir_generate.cpp three_address_code.cpp

$(BISON_C) $(BISON_H): $(BISON_FILE)
	$(BISON) -d $(BISON_FILE)

$(LEX_C): $(LEX_FILE)
	$(FLEX) $(LEX_FILE)

splc: $(TARGET)

clean:
	rm -f $(BISON_C) $(BISON_H) $(LEX_C) $(OUTPUT)
	rm -rf $(TARGET_DIR)
