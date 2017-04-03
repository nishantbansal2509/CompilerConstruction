/*
Batch No 11
Nishant Bansal	2014A7PS052P
Subham Kumar	2014A7PS121P
*/
#include <stdio.h>
#include "lexerDef.h"

#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

FILE * getStream (FILE * fp);
void removeComments(char * testCaseFile, char * cleanFile);
tokenInfo getNextToken(FILE * fp);

#endif