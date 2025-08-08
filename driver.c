/*
 * Compiler Driver
 *
 * This file contains the main driver program for the compiler,
 * providing a command-line interface for various compiler operations.
 *
 * Original Authors:
 * Batch No 11
 * Nishant Bansal	2014A7PS052P
 * Subham Kumar	2014A7PS121P
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "firstandfollow.h"

/* Global variables - defined here to match extern declarations */
int currentLine;
int state;
int rangeopFlag;
char readBuffer[READ_SIZE];
int readBuffPointer;
int errptr;
int errno[ERROR_SIZE];
int errline[ERROR_SIZE];
char errsym[ERROR_SIZE];
char errstr[ERROR_SIZE][MAX_TOKEN_LENGTH];

/**
 * Prints the clean code (after comment removal) to the console
 */
void printCode() {
    char c;
    FILE* fd = fopen("cleanFile.txt", "r");
    
    if (fd == NULL) {
        printf("Error: Could not open clean file.\n");
        return;
    }
    
    c = fgetc(fd);
    while (c != EOF) {
        printf("%c", c);
        c = fgetc(fd);
    }
    printf("\n");
    fclose(fd);
}

/**
 * Prints the list of tokens extracted from the source code
 * along with any lexical errors encountered
 */
void printTokenList() {
    FILE* fp2 = fopen("cleanFile.txt", "r");
    
    if (fp2 == NULL) {
        printf("Error: Could not open clean file.\n");
        return;
    }
    
    getStream(fp2);
    currentLine = 1;
    TokenInfo token = getNextToken(fp2);
    
    printf("%20s%20s%20s\n", "TOKEN", "lexeme", "LineNumber");
    
    while (token.tkId != 57) {
        printf("%20s%20s%20d\n", token.tkName, token.lexeme, token.lineNum);
        token = getNextToken(fp2);
    }
    
    printf("%20s%20s%20d\n", token.tkName, token.lexeme, token.lineNum);
    fclose(fp2);
    
    // Print any lexical errors
    for (int i = 0; i < errptr; i++) {
        if (errno[i] == 1) {
            printf("ERROR_1: Identifier at line %d is longer than the prescribed length\n", 
                   errline[i]);
        } else if (errno[i] == 2) {
            printf("ERROR_2: Unknown Symbol %c at line %d\n", 
                   errsym[i], errline[i]);
        } else if (errno[i] == 3) {
            printf("ERROR_3: Unknown pattern %s at line %d\n", 
                   errstr[i], errline[i]);
        }
    }
}

/**
 * Displays the menu of available compiler operations
 */
void displayMenu() {
    printf("--------------------------------------------------------------\n");
    printf("| NOTE :: Please run option 1 once before running 2, 3 and 4 |\n");
    printf("--------------------------------------------------------------\n");
    printf("Enter 1 to print the comment free code on the console\n");
    printf("Enter 2 for printing the token list\n");
    printf("Enter 3 for parsing to verify the syntactic correctness of the input source code\n");
    printf("Enter 4 for creating the parse tree and printing it appropriately\n");
    printf("Enter 5 to exit\n");
    printf("---------------------------------------------------------\n");
    printf("Enter the desired option: ");
}

/**
 * Main function - entry point for the compiler
 *
 * @param argc Number of command-line arguments
 * @param argv Array of command-line arguments
 * @return Exit status code
 */
int main(int argc, char* argv[]) {
    // Check for correct number of arguments
    if (argc != 3) {
        printf("Usage: %s <source_file> <output_file>\n", argv[0]);
        return 1;
    }
    
    // Check if input file exists
    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error: Could not open source file %s\n", argv[1]);
        return 1;
    }
    fclose(fp);
    
    printf("Both LEXICAL and PARSER modules developed.\n");
    printf("FIRST and FOLLOW sets AUTOMATED.\n");

    // Initialize the compiler
    removeComments(argv[1], "cleanFile.txt");
    calculateFirst("firstAutomated.txt");
    calculatefollow("followAutomated.txt");
    populateFirst("firstAutomated.txt");
    populateFollow("followAutomated.txt");
    createParseTable();

    // Main menu loop
    while (1) {
        int option;
        displayMenu();
        
        if (scanf("%d", &option) != 1) {
            // Clear input buffer on invalid input
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        
        switch (option) {
            case 1:
                printCode();
                break;
                
            case 2:
                printTokenList();
                break;
                
            case 3:
                // Reset state before parsing
                currentLine = 1;
                readBuffPointer = 0;
                errptr = 0;
                parseInputSourceCode("cleanFile.txt");
                break;
                
            case 4:
                if (errptr != 0) {
                    printf("Warning: There were errors in parsing. The parse tree might be incorrect.\n");
                }
                
                FILE* fdn = fopen(argv[2], "w");
                if (fdn == NULL) {
                    printf("Error: Could not open output file %s\n", argv[2]);
                    break;
                }
                
                inorderT(T, fdn);
                fclose(fdn);
                printf("Parse Tree has been printed to %s.\n\n", argv[2]);
                break;
                
            case 5:
                printf("Goodbye!\n");
                return 0;
                
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
    
    return 0;
}