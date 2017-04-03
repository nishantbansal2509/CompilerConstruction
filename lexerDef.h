/*
Batch No 11
Nishant Bansal	2014A7PS052P
Subham Kumar	2014A7PS121P
*/

//readSize is the default length of sourcecode read at a time to avoid IO intensity
#define readSize 11
//the code will malfunction if a lexeme's length is greater then this value
#define maxTokenLength 33
//maximum number of errors in the sourcecode compiler will report
#define errSize 100

#ifndef LEXERDEF_H_INCLUDED

#define LEXERDEF_H_INCLUDED

#include <stdlib.h>

int currentLine;

int state;

int rangeopFlag;

//readBuffer acts as temporary storage for the part of sourcecode read
char readBuffer[readSize];

int readBuffPointer;

struct tokenInfo{
	int tkId;
	char tkName[13];
	char lexeme[maxTokenLength];
	int lineNum;
};

typedef struct tokenInfo tokenInfo;


int errptr;								//for indexing in the following arrays
int errno[errSize];						//stores the error number of the corresponding index
int errline[errSize];					//stores the line number in which the error appears
char errsym[errSize];					//stores the error symbol if the error is because of an unknown character
char errstr[errSize][maxTokenLength];	//store the lexeme which has the error

#endif

