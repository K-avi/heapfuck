TARGET := ../heapfuck

TEST := ../test
CC := gcc
CFLAGS := -O2  -g -Wall -Wextra -Wpedantic -Wno-unused-parameter
CLIBS := -lfl

LEX := flex
LFLAGS :=

YACC := bison
YFLAGS := -d 
SRCS := exec.c ast.c heap.c stack.c globals.c cmdline_interp.c

all: $(TARGET)

$(TARGET): lex.yy.c parser.tab.c $(SRCS) main.c
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(CLIBS)


$(TEST): lex.yy.c parser.tab.c $(SRCS) main_test.c
	$(CC) $(CFLAGS) $^ -o $(TEST) $(CLIBS)

lex.yy.c lex.yy.h: lexer.l parser.tab.h
	$(LEX) $(LFLAGS) $<


parser.tab.c parser.tab.h: parser.y
	$(YACC) $(YFLAGS) $<

clean:
	rm -f parser.tab.* parser.output lex.*.*  
	
.PHONY: clean
