/*
 * Parser Definitions Header
 *
 * This file contains definitions for the parser component of the compiler,
 * including parse table structures, tree nodes, and grammar rules.
 *
 * Original Authors:
 * Batch No 11
 * Nishant Bansal	2014A7PS052P
 * Subham Kumar	2014A7PS121P
 */

#ifndef PARSERDEF_H_INCLUDED
#define PARSERDEF_H_INCLUDED

#include <stdio.h>

/* Configuration constants */
// Number of non-terminals in the grammar
#define ROWS 51
// Number of terminals in the grammar (excluding EOF)
#define COLUMNS 57
// Maximum length of FIRST/FOLLOW sets
#define FNF_LEN 20
// Number of grammar rules
#define NUM_RULES 94
// Maximum error count
#define MAX_PARSER_ERRORS 100
// Maximum lexeme length
#define MAX_LEXEME_LENGTH 33

/* Parse table and sets */
// FIRST sets for all non-terminals
extern int first[ROWS][FNF_LEN];
// FOLLOW sets for all non-terminals
extern int follow[ROWS][FNF_LEN];
// LL(1) parse table
extern int parseTable[ROWS][COLUMNS];

/**
 * Parse tree node structure
 */
typedef struct TreeNode {
    int id;                      // Node identifier
    struct TreeNode* parent;     // Parent node
    struct TreeNode* child;      // First child node
    struct TreeNode* sibling;    // Next sibling node
    char lexeme[MAX_LEXEME_LENGTH]; // Lexeme text
    int linenum;                 // Line number
} TreeNode;

/* Error tracking for parser */
// Current parser error count
extern int perrptr;
// Line numbers where parser errors occurred
extern int perrline[MAX_PARSER_ERRORS];
// Expected tokens at error points
extern int perrtk[MAX_PARSER_ERRORS];
// Actual tokens at error points
extern int perrex[MAX_PARSER_ERRORS];
// Lexemes at error points
extern char perrlex[MAX_PARSER_ERRORS][30];

/* Global parse tree root */
extern TreeNode* T;

/* Flag for syntax correctness */
extern int syntaxFlag;

/**
 * Stack node structure for parser stack
 */
typedef struct StackNode {
    int data;                // Node data (token/non-terminal ID)
    struct StackNode* next;  // Next node in stack
} StackNode;

/* Stack head pointer */
extern StackNode* head;

/* Grammar rules */
extern char grammar[NUM_RULES][90];

#endif /* PARSERDEF_H_INCLUDED */

/*
 * Grammar rules (commented out to avoid duplication)
 * These are now defined in parser.c
 */