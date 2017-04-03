/*
Batch No 11
Nishant Bansal	2014A7PS052P
Subham Kumar	2014A7PS121P
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "firstandfollow.h"

void printCode(){
	char c;
	FILE * fd = fopen("cleanFile.txt","r");
	c = fgetc(fd);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fd);
    }
    printf("\n");
	fclose(fd);
}

void printTokenList(){
	FILE * fp2 = fopen("cleanFile.txt","r");
	getStream(fp2);
	currentLine = 1;
	tokenInfo token = getNextToken(fp2);
	printf("%20s%20s%20s\n", "TOKEN", "lexeme", "LineNumber");
	while(token.tkId != 57){
		printf("%20s%20s%20d\n", token.tkName, token.lexeme, token.lineNum);
		token = getNextToken(fp2);
	}
	printf("%20s%20s%20d\n", token.tkName, token.lexeme, token.lineNum);
	fclose(fp2);
	int i = 0;
	for(i=0;i<errptr;i++){
		if (errno[i] == 1)
		{
			printf("ERROR_1 : Identifier at line %d is longer than the prescribed length \n", errline[i]);
		}
		else if (errno[i] == 2)
		{
			printf("ERROR_2: Unknown Symbol %c at line %d\n", errsym[i], errline[i]);
		}
		else if (errno[i] == 3)
		{
			printf("ERROR_3: Unknown pattern %s at line %d\n",errstr[i],errline[i]);
		}
	}
}

void verifySyntax(){

}

int main(int argc, char * argv[]){
	if (argc != 3)
	{
		printf("Wrong number of arguments. The number of arguments should be 2.\n");
		return 0;
	}
	FILE * fp = fopen(argv[1],"r");
	printf("Both LEXICAL and PARSER modules developed.\n");
	printf("FIRST and FOLLOW sets AUTOMATED.\n");

	removeComments(argv[1],"cleanFile.txt");
	calculateFirst("firstAutomated.txt");
	calculatefollow("followAutomated.txt");
	populateFirst("firstAutomated.txt");
	populateFollow("followAutomated.txt");
	createParseTable();

	while(1){
		printf("--------------------------------------------------------------\n");
		printf("| NOTE :: Please run option 1 once before running 2, 3 and 4 |\n");
		printf("--------------------------------------------------------------\n");
		printf("Enter 1 to print the comment free code on the console\n");
		printf("Enter 2 for printing the token list\n");
		printf("Enter 3 for parsing to verify the syntactic correctness of the input source code\n");
		printf("Enter 4 for creating the parse tree and printing it appropriately\n");
		printf("Enter 5 to exit\n");
		printf("---------------------------------------------------------\n");
		printf("Enter the desired option:\n");
		int n;
		scanf("%d",&n);
		if (n==1) printCode();
		else if (n==2) printTokenList();
		else if (n==3)
		{

			currentLine = 1;
			readBuffPointer = 0;
			errptr = 0;
			parseInputSourceCode("cleanFile.txt");
		}
		else if (n==4)
		{
			if (errptr != 0)
			{
				printf("There were errors in parsing Thus tree mighht be incorrect.\n");
			}
			FILE * fdn = fopen(argv[2],"w");
			inorderT(T, fdn);
			fclose(fdn);
			printf("Parse Tree has been printed to %s.\n\n\n", argv[2]);
		}
		else if (n==5)
		{
			printf("GoodBye !!\n");
			break;
		}
		else printf("Invalid Option. Please try again.\n");
	}
	
}