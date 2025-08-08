/*
 * Lexer Definitions Header
 * 
 * This file contains definitions for the lexical analyzer component
 * of the compiler, including token structures and error handling.
 *
 * Original Authors:
 * Batch No 11
 * Nishant Bansal	2014A7PS052P
 * Subham Kumar	2014A7PS121P
 */

#ifndef LEXERDEF_H_INCLUDED
#define LEXERDEF_H_INCLUDED

#include <stdlib.h>

/* Configuration constants */
// Default length of source code read at a time to reduce I/O operations
#define READ_SIZE 11
// Maximum length of a token lexeme - tokens longer than this will cause errors
#define MAX_TOKEN_LENGTH 33
// Maximum number of errors the compiler will report
#define ERROR_SIZE 100

/* Token structure definition */
typedef struct {
    int tkId;                       // Token identifier
    char tkName[13];                // Token name
    char lexeme[MAX_TOKEN_LENGTH];  // Actual lexeme text
    int lineNum;                    // Line number where token appears
} TokenInfo;

/* Global variables - consider refactoring to reduce globals */
// Current line being processed
extern int currentLine;
// Current state of the lexer state machine
extern int state;
// Flag for range operator detection
extern int rangeopFlag;
// Buffer for reading source code
extern char readBuffer[READ_SIZE];
// Current position in the read buffer
extern int readBuffPointer;

/* Error tracking */
// Current error count
extern int errptr;
// Error type codes
extern int errno[ERROR_SIZE];
// Line numbers where errors occurred
extern int errline[ERROR_SIZE];
// Error symbols for unknown character errors
extern char errsym[ERROR_SIZE];
// Error lexemes
extern char errstr[ERROR_SIZE][MAX_TOKEN_LENGTH];

#endif /* LEXERDEF_H_INCLUDED */
