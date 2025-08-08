/*
 * Utility Functions Header
 *
 * This file defines utility functions used throughout the compiler,
 * primarily for token manipulation and conversion.
 *
 * Original Authors:
 * Batch No 11
 * Nishant Bansal	2014A7PS052P
 * Subham Kumar	2014A7PS121P
 */

#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <stdio.h>

/**
 * Gets the token ID for a given token string
 *
 * @param s The token string
 * @return The corresponding token ID
 */
int getTokenId(const char* s);

/**
 * Prints the token name for a given token ID
 *
 * @param n The token ID
 */
void idtotk(int n);

/**
 * Returns the token name string for a given token ID
 *
 * @param n The token ID
 * @return The token name string
 */
char* idtotkstr(int n);

#endif /* UTILITY_H_INCLUDED */