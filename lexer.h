/*
 * Lexer Interface Header
 *
 * This file defines the public interface for the lexical analyzer component
 * of the compiler, providing functions for token extraction and preprocessing.
 *
 * Original Authors:
 * Batch No 11
 * Nishant Bansal	2014A7PS052P
 * Subham Kumar	2014A7PS121P
 */

#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

#include <stdio.h>
#include "lexerDef.h"

/**
 * Reads a chunk of characters from the input file into the buffer
 *
 * @param fp File pointer to the source code file
 * @return The same file pointer, advanced by the number of characters read
 */
FILE* getStream(FILE* fp);

/**
 * Removes comments from the source code and writes clean code to a new file
 *
 * @param testCaseFile Path to the input source code file
 * @param cleanFile Path to the output file for clean code
 */
void removeComments(const char* testCaseFile, const char* cleanFile);

/**
 * Extracts and returns the next token from the input stream
 *
 * @param fp File pointer to the source code file
 * @return The next token found in the input
 */
TokenInfo getNextToken(FILE* fp);

#endif /* LEXER_H_INCLUDED */