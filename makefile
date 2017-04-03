main: lexer.o driver.o parser.o utility.o firstandfollow.o
	gcc lexer.o driver.o parser.o utility.o firstandfollow.o -o stage1exe

lexer.o: lexer.c lexer.h
	gcc -c -g -w lexer.c

parser.o: parser.c parser.h parserDef.h lexer.h lexerDef.h
	gcc -c -g -w parser.c

utility.o: utility.c utility.h
	gcc -c -g -w utility.c

firstandfollow.o: firstandfollow.c
	gcc -c -g -w firstandfollow.c

driver.o: driver.c lexerDef.h lexer.h firstandfollow.h
	gcc -c -g -w driver.c

clean:
	rm *.o
	rm stage1exe
	rm firstAutomated.txt
	rm followAutomated.txt