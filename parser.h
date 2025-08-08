/*
 * Parser Interface Header
 *
 * This file defines the public interface for the parser component
 * of the compiler, providing functions for syntax analysis.
 *
 * Original Authors:
 * Batch No 11
 * Nishant Bansal	2014A7PS052P
 * Subham Kumar	2014A7PS121P
 */

#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <stdio.h>
#include "parserDef.h"

/**
 * Parses the input source code file and verifies its syntactic correctness
 *
 * @param file Path to the clean source code file
 */
void parseInputSourceCode(const char* file);

/**
 * Removes the top element from the parser stack
 */
void pop();

/**
 * Pushes a new element onto the parser stack
 *
 * @param n The element to push onto the stack
 */
void push(int n);

/**
 * Prints the current contents of the parser stack
 */
void print();

/**
 * Populates the FIRST sets from a file
 *
 * @param file Path to the file containing FIRST set information
 */
void populateFirst(const char* file);

/**
 * Populates the FOLLOW sets from a file
 *
 * @param file Path to the file containing FOLLOW set information
 */
void populateFollow(const char* file);

/**
 * Gets the token ID for a given token string
 *
 * @param s The token string
 * @return The corresponding token ID
 */
int getTokenId(const char* s);

/**
 * Converts a token ID to its string representation
 *
 * @param n The token ID
 */
void idtotk(int n);

/**
 * Creates the parse table for predictive parsing
 */
void createParseTable();

/**
 * Performs an inorder traversal of the parse tree and writes it to a file
 *
 * @param node The current tree node
 * @param file File pointer to write the tree to
 */
void inorderT(TreeNode* node, FILE* file);

#endif /* PARSER_H_INCLUDED */