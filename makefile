# Compiler Construction Makefile
#
# This makefile builds the compiler with proper warning flags and dependencies.
# It also provides targets for cleaning up build artifacts.

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99
LDFLAGS =

# Target executable
TARGET = stage1exe

# Source files and object files
SRCS = lexer.c parser.c utility.c firstandfollow.c driver.c
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(TARGET)

# Compile source files to object files
lexer.o: lexer.c lexer.h lexerDef.h
	$(CC) $(CFLAGS) -c lexer.c

parser.o: parser.c parser.h parserDef.h lexer.h lexerDef.h utility.h
	$(CC) $(CFLAGS) -c parser.c

utility.o: utility.c utility.h
	$(CC) $(CFLAGS) -c utility.c

firstandfollow.o: firstandfollow.c firstandfollow.h parserDef.h utility.h
	$(CC) $(CFLAGS) -c firstandfollow.c

driver.o: driver.c lexerDef.h lexer.h parser.h firstandfollow.h
	$(CC) $(CFLAGS) -c driver.c

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET) firstAutomated.txt followAutomated.txt cleanFile.txt

# Clean and rebuild
rebuild: clean all

# Run the compiler with a test case
test: $(TARGET)
	./$(TARGET) testcase1.txt out.txt

.PHONY: all clean rebuild test