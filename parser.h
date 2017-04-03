/*
Batch No 11
Nishant Bansal	2014A7PS052P
Subham Kumar	2014A7PS121P
*/
#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "parserDef.h"

#include <stdio.h>

void parseInputSourceCode(char * file);

void pop();

void push(int n);

void print();

void populateFirst(char * file);

void populateFollow(char * file);

int getTokenId(char * s);

void idtotk(int n);

void createParseTable();

#endif