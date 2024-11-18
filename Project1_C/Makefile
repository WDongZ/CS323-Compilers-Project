CC=gcc
GPP=g++
FLEX=flex
BISON=bison

splc:
	@mkdir -p bin
	$(BISON) -d syntax.y
	$(FLEX) lex.l
	$(GPP) -o bin/splc syntax.tab.c node.cpp yyerror_m.cpp -ll ## -lfl for linux
clean:
	@rm -rf bin lex.yy.c syntax.tab.c syntax.tab.h *.out output.txt
.PHONY: splc