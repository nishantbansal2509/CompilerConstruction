/*
 * First and Follow Sets Header
 *
 * This file defines functions for calculating FIRST and FOLLOW sets
 * for the grammar, which are essential for predictive parsing.
 *
 * Original Authors:
 * Batch No 11
 * Nishant Bansal	2014A7PS052P
 * Subham Kumar	2014A7PS121P
 */

#ifndef FIRSTANDFOLLOW_H_INCLUDED
#define FIRSTANDFOLLOW_H_INCLUDED

#include <stdio.h>

/**
 * Calculates the FIRST sets for all non-terminals in the grammar
 * and writes them to the specified file
 *
 * @param filename Path to the output file for FIRST sets
 */
void calculateFirst(const char* filename);

/**
 * Calculates the FOLLOW sets for all non-terminals in the grammar
 * and writes them to the specified file
 *
 * @param filename Path to the output file for FOLLOW sets
 */
void calculatefollow(const char* filename);

#endif /* FIRSTANDFOLLOW_H_INCLUDED */