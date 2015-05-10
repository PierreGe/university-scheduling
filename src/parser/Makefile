parser: lex.yy.c parser.cpp
	cc -c lex.yy.c -o lex.yy.o
	c++ lex.yy.o parser.cpp -o parser
lex.yy.c: parser.cpp
	lex parser.l
parser.cpp:
	yacc --debug --verbose -d -o parser.cpp parser.y
clean:
	rm -f lex.yy.c
	rm -f parser.cpp
	rm -f lex.yy.o
	rm -f parser
	rm -f parser.h
