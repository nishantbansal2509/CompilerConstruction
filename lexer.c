/*
Batch No 11
Nishant Bansal	2014A7PS052P
Subham Kumar	2014A7PS121P
*/

#include "lexerDef.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"


//getStream takes the file pointer and populates the global
//readBuffer which contains readSize number of charaacters
//at a time and returns the same file pointer which has now 
//advanced by the number of characters read
FILE * getStream (FILE * fp){
	int charRead;
	int i;
	for(i=0;i<readSize;i++){
		readBuffer[i] = '\0';
		//padding the readBuffer
	}
	if(feof(fp)==0 && ferror(fp)==0){
		charRead = fread(readBuffer, sizeof(char), readSize-1, fp);
		// printf("%d\n", charRead);
	}
	readBuffer[charRead] = '$';
	return fp;
}


//remove comments and generate the clean code in cleanFile.txt
//which will be used for all later stages of compiler
//needs changes
void removeComments(char * testCaseFile, char * cleanFile){
	FILE * fd1 = fopen(testCaseFile,"r");
	FILE * fd2 = fopen(cleanFile,"w");
	int c;
	while(!feof(fd1)){
		c = fgetc(fd1);
		if (c != 42 && !feof(fd1))
		{
			fputc(c,fd2);
			continue;
		}
		else if(!feof(fd1))
		{
			c = fgetc(fd1);
			if (c != 42)
			{
				fputc(42,fd2);
				fputc(c,fd2);
				continue;
			}
			else
			{
				while(!feof(fd1))
				{
					c = fgetc(fd1);
					if (c != 42)
					{
						continue;
					}
					else
					{
						c = fgetc(fd1);
						if (c != 42)
						{
							continue;
						}
						else
						{
							break;
						}
					}
				}
			}
		}
	}
	fclose(fd2);
	fclose(fd1);
}


//utility function which increase the global pointer readBuffPointer
//if increasing it will result in buffer overflow then it calls
//getStream method to get the next stream of characters in the buffer
int incrementReadBuffPointer(int readBuffPointer, FILE * fp){
	if (readBuffPointer < readSize-2)
	{
		readBuffPointer++;
		return readBuffPointer;
	}
	else
	{
		getStream(fp);
		return 0;
	}
}


//get next token returns the next token from cleaned source code
//if there exist any lexical errors then it also stores the corresponding
//information into global arrays for storing errors
//the following types of errors are detected by the lexer
//1. if identifier length is longer than the prescribed limit
//2. unknown symbol is found in the source code
//3. unknown pattern found in the code
tokenInfo getNextToken(FILE * fp){
	state = 1;		//initialize to state 1 of DFA
	//localBuffer remembers the lexeme while readBufferPointer incrrements for lookahead
	char localBuffer[maxTokenLength];
	int localBuffPointer = 0;
	memset(localBuffer,'\0',maxTokenLength);
	tokenInfo tk;
	while(1){
		char c = readBuffer[readBuffPointer];
		// printf("%c state %d\n", c, state);
		if (c == '$' && strlen(localBuffer) <= 1)
		{
			// printf("%s\n", readBuffer);
			tk.tkId = 57;
			strcpy(tk.tkName, "$");
			strcpy(tk.lexeme, "$");
			tk.lineNum = currentLine;
			return tk;
		}
		localBuffer[localBuffPointer] = c;
		switch(state){
			case 1:
				switch(c){
					case ' ':
						state = 1;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						break;
					case '\t':
						state = 1;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						break;
					case '\r':
						state = 1;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						break;
					case '\n':
						state = 1;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						currentLine++;
						// printf("%d\n", readBuffPointer);
						break;
					case '+':
						state = 1;
						// printf("%d\n", readBuffPointer);
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						// printf("%d\n", readBuffPointer);
						tk.tkId = 1;
						strcpy(tk.tkName, "PLUS");
						strcpy(tk.lexeme, "+");
						tk.lineNum = currentLine;
						return tk;
					case '-':
						state = 1;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						tk.tkId = 2;
						strcpy(tk.tkName, "MINUS");
						strcpy(tk.lexeme, "-");
						tk.lineNum = currentLine;
						return tk;
					case '*':
						state = 1;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						tk.tkId = 3;
						strcpy(tk.tkName, "MUL");
						strcpy(tk.lexeme, "*");
						tk.lineNum = currentLine;
						return tk;
					case '/':
						state = 1;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						tk.tkId = 4;
						strcpy(tk.tkName, "DIV");
						strcpy(tk.lexeme, "/");
						tk.lineNum = currentLine;
						return tk;
					case ',':
						state = 1;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						tk.tkId = 5;
						strcpy(tk.tkName, "COMMA");
						strcpy(tk.lexeme, ",");
						tk.lineNum = currentLine;
						return tk;
					case ';':
						state = 1;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						tk.tkId = 6;
						strcpy(tk.tkName, "SEMICOL");
						strcpy(tk.lexeme, ";");
						tk.lineNum = currentLine;
						// printf("%d\n", readBuffPointer);
						return tk;
					case '[':
						state = 1;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						tk.tkId = 7;
						strcpy(tk.tkName, "SQBO");
						strcpy(tk.lexeme, "[");
						tk.lineNum = currentLine;
						return tk;
					case ']':
						state = 1;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						tk.tkId = 8;
						strcpy(tk.tkName, "SQBC");
						strcpy(tk.lexeme, "]");
						tk.lineNum = currentLine;
						return tk;
					case '(':
						state = 1;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						tk.tkId = 9;
						strcpy(tk.tkName, "BO");
						strcpy(tk.lexeme, "(");
						tk.lineNum = currentLine;
						return tk;
					case ')':
						state = 1;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						tk.tkId = 10;
						strcpy(tk.tkName, "BC");
						strcpy(tk.lexeme, ")");
						tk.lineNum = currentLine;
						return tk;
					case '=':
						state = 2;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						localBuffPointer++;
						break;
					case '!':
						state = 3;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						localBuffPointer++;
						break;
					case ':':
						state = 4;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						localBuffPointer++;
						break;
					case '<':
						state = 5;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						localBuffPointer++;
						break;
					case '>':
						state = 6;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						localBuffPointer++;
						break;
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						state = 7;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						localBuffPointer++;
						break;
					case '.':
						if (rangeopFlag == 1)
						{
							state = 1;
							readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
							tk.tkId = 22;
							strcpy(tk.tkName, "RANGEOP");
							strcpy(tk.lexeme, "..");
							tk.lineNum = currentLine;
							rangeopFlag = 0;
							return tk;
						}
						else
						{
							state = 1;
							readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
							localBuffPointer = 0;
							break;
						}
					case 'a':
					case 'b':
					case 'c':
					case 'd':
					case 'e':
					case 'f':
					case 'g':
					case 'h':
					case 'i':
					case 'j':
					case 'k':
					case 'l':
					case 'm':
					case 'n':
					case 'o':
					case 'p':
					case 'q':
					case 'r':
					case 's':
					case 't':
					case 'u':
					case 'v':
					case 'w':
					case 'x':
					case 'y':
					case 'z':
					case 'A':
					case 'B':
					case 'C':
					case 'D':
					case 'E':
					case 'F':
					case 'G':
					case 'H':
					case 'I':
					case 'J':
					case 'K':
					case 'L':
					case 'M':
					case 'N':
					case 'O':
					case 'P':
					case 'Q':
					case 'R':
					case 'S':
					case 'T':
					case 'U':
					case 'V':
					case 'W':
					case 'X':
					case 'Y':
					case 'Z':
						state = 13;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						localBuffPointer++;
						break;
					default:
						state = 1;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						errno[errptr] = 2;
						errline[errptr] = currentLine;
						errsym[errptr] = c;
						errptr++;
						localBuffPointer = 0;
						break;
				}
				break;
			case 2:
				switch(c){
					case '=':
						state = 1;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						tk.tkId = 11;
						strcpy(tk.tkName, "EQ");
						strcpy(tk.lexeme, "==");
						tk.lineNum = currentLine;
						return tk;
					default :
						state = 1;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						errno[errptr] = 3;
						errline[errptr] = currentLine;
						strcpy(errstr[errptr],localBuffer);
						errptr++;
						localBuffPointer = 0;
						continue;
				}
				break;
			case 3:
				switch(c){
					case '=':
						state = 1;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						tk.tkId = 12;
						strcpy(tk.tkName, "NE");
						strcpy(tk.lexeme, "!=");
						tk.lineNum = currentLine;
						return tk;
					default :
						state = 1;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						errno[errptr] = 3;
						errline[errptr] = currentLine;
						strcpy(errstr[errptr],localBuffer);
						errptr++;
						continue;
				}
				break;
			case 4:
				switch(c){
					case '=':
						state = 1;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						tk.tkId = 13;
						strcpy(tk.tkName, "ASSIGNOP");
						strcpy(tk.lexeme, ":=");
						tk.lineNum = currentLine;
						return tk;
					default :
						state = 1;
						tk.tkId = 14;
						strcpy(tk.tkName, "COLON");
						strcpy(tk.lexeme, ":");
						tk.lineNum = currentLine;
						return tk;
				}
				break;
			case 5:
				switch(c){
					case '=':
						state = 1;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						tk.tkId = 15;
						strcpy(tk.tkName, "LE");
						strcpy(tk.lexeme, "<=");
						tk.lineNum = currentLine;
						return tk;
					case '<':
						state = 14;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						localBuffPointer++;
						break;
					default :
						state = 1;
						tk.tkId = 17;
						strcpy(tk.tkName, "LT");
						strcpy(tk.lexeme, "<");
						tk.lineNum = currentLine;
						return tk;
				}
				break;
			case 6:
				switch(c){
					case '=':
						state = 1;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						tk.tkId = 18;
						strcpy(tk.tkName, "GE");
						strcpy(tk.lexeme, ">=");
						tk.lineNum = currentLine;
						return tk;
					case '>':
						state = 15;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						localBuffPointer++;
						break;
					default :
						state = 1;
						tk.tkId = 20;
						strcpy(tk.tkName, "GT");
						strcpy(tk.lexeme, ">");
						tk.lineNum = currentLine;
						return tk;
				}
				break;
			case 7:
				switch(c){
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						state = 7;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						localBuffPointer++;
						break;
					case '.':
						state = 8;//RNUM OR RANGEOP
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						localBuffPointer++;
						break;
					case 'a':
					case 'b':
					case 'c':
					case 'd':
					case 'e':
					case 'f':
					case 'g':
					case 'h':
					case 'i':
					case 'j':
					case 'k':
					case 'l':
					case 'm':
					case 'n':
					case 'o':
					case 'p':
					case 'q':
					case 'r':
					case 's':
					case 't':
					case 'u':
					case 'v':
					case 'w':
					case 'x':
					case 'y':
					case 'z':
					case 'A':
					case 'B':
					case 'C':
					case 'D':
					case 'E':
					case 'F':
					case 'G':
					case 'H':
					case 'I':
					case 'J':
					case 'K':
					case 'L':
					case 'M':
					case 'N':
					case 'O':
					case 'P':
					case 'Q':
					case 'R':
					case 'S':
					case 'T':
					case 'U':
					case 'V':
					case 'W':
					case 'X':
					case 'Y':
					case 'Z':
					case '_':
						state = 1;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						errno[errptr] = 3;
						errline[errptr] = currentLine;
						strcpy(errstr[errptr],localBuffer);
						localBuffPointer = 0;
						errptr++;
						break;
					default :
						state = 1;
						tk.tkId = 21;
						strcpy(tk.tkName, "NUM");
						int i = 0;
						memset(tk.lexeme,'\0',maxTokenLength);
						for(i=0;i<localBuffPointer;i++){
							tk.lexeme[i] = localBuffer[i];
						}
						tk.lineNum = currentLine;
						return tk;
				}
				break;
			case 8:
				switch(c){
					case '.':
						state = 1;
						tk.tkId = 21;
						strcpy(tk.tkName, "NUM");
						int i = 0;
						memset(tk.lexeme,'\0',maxTokenLength);
						for(i=0;i<localBuffPointer-1;i++){
							tk.lexeme[i] = localBuffer[i];
						}
						tk.lineNum = currentLine;
						rangeopFlag = 1;
						return tk;
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						state = 9;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						localBuffPointer++;
						break;
				}
				break;
			case 9:
				switch(c){
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						state = 9;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						localBuffPointer++;
						break;
					case 'e':
					case 'E':
						state = 10;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						localBuffPointer++;
						break;
					default :
						state = 1;
						tk.tkId = 23;
						strcpy(tk.tkName, "RNUM");
						int i = 0;
						memset(tk.lexeme,'\0',maxTokenLength);
						for(i=0;i<localBuffPointer;i++){
							tk.lexeme[i] = localBuffer[i];
						}
						tk.lineNum = currentLine;
						return tk;
				}
				break;
			case 10:
				switch(c){
					case '+':
					case '-':
						state = 11;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						localBuffPointer++;
						break;
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						state = 12;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						localBuffPointer++;
						break;
				}
				break;
			case 11:
				switch(c) {
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						state = 12;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						localBuffPointer++;
						break;
				}
				break;
			case 12:
				switch(c) {
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						state = 12;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						localBuffPointer++;
						break;
					default :
						state = 1;
						tk.tkId = 23;
						strcpy(tk.tkName, "RNUM");
						int i = 0;
						memset(tk.lexeme,'\0',maxTokenLength);
						for(i=0;i<localBuffPointer;i++){
							tk.lexeme[i] = localBuffer[i];
						}
						tk.lineNum = currentLine;
						return tk;
				}
				break;
			case 13:
				switch(c){
					case 'a':
					case 'b':
					case 'c':
					case 'd':
					case 'e':
					case 'f':
					case 'g':
					case 'h':
					case 'i':
					case 'j':
					case 'k':
					case 'l':
					case 'm':
					case 'n':
					case 'o':
					case 'p':
					case 'q':
					case 'r':
					case 's':
					case 't':
					case 'u':
					case 'v':
					case 'w':
					case 'x':
					case 'y':
					case 'z':
					case 'A':
					case 'B':
					case 'C':
					case 'D':
					case 'E':
					case 'F':
					case 'G':
					case 'H':
					case 'I':
					case 'J':
					case 'K':
					case 'L':
					case 'M':
					case 'N':
					case 'O':
					case 'P':
					case 'Q':
					case 'R':
					case 'S':
					case 'T':
					case 'U':
					case 'V':
					case 'W':
					case 'X':
					case 'Y':
					case 'Z':
					case '_':
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						state = 13;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						localBuffPointer++;
						break;
					default:
						state = 1;
						char string[maxTokenLength];
						memset(string, '\0', maxTokenLength);
						int i;
						for(i=0;i<localBuffPointer;i++){
							string[i] = localBuffer[i];
						}
						if (!strcmp(string,"integer"))
						{
							tk.tkId = 24;
							strcpy(tk.tkName,"INTEGER");
							strcpy(tk.lexeme,"integer");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"real"))
						{
							tk.tkId = 25;
							strcpy(tk.tkName,"REAL");
							strcpy(tk.lexeme,"real");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"boolean"))
						{
							tk.tkId = 26;
							strcpy(tk.tkName,"BOOLEAN");
							strcpy(tk.lexeme,"boolean");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"of"))
						{
							tk.tkId = 27;
							strcpy(tk.tkName,"OF");
							strcpy(tk.lexeme,"of");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"array"))
						{
							tk.tkId = 28;
							strcpy(tk.tkName,"ARRAY");
							strcpy(tk.lexeme,"array");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"start"))
						{
							tk.tkId = 29;
							strcpy(tk.tkName,"START");
							strcpy(tk.lexeme,"start");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"end"))
						{
							tk.tkId = 30;
							strcpy(tk.tkName,"END");
							strcpy(tk.lexeme,"end");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"declare"))
						{
							tk.tkId = 31;
							strcpy(tk.tkName,"DECLARE");
							strcpy(tk.lexeme,"declare");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"module"))
						{
							tk.tkId = 32;
							strcpy(tk.tkName,"MODULE");
							strcpy(tk.lexeme,"module");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"driver"))
						{
							tk.tkId = 33;
							strcpy(tk.tkName,"DRIVER");
							strcpy(tk.lexeme,"driver");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"program"))
						{
							tk.tkId = 34;
							strcpy(tk.tkName,"PROGRAM");
							strcpy(tk.lexeme,"program");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"get_value"))
						{
							tk.tkId = 35;
							strcpy(tk.tkName,"GET_VALUE");
							strcpy(tk.lexeme,"get_value");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"print"))
						{
							tk.tkId = 36;
							strcpy(tk.tkName,"PRINT");
							strcpy(tk.lexeme,"print");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"use"))
						{
							tk.tkId = 37;
							strcpy(tk.tkName,"USE");
							strcpy(tk.lexeme,"use");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"with"))
						{
							tk.tkId = 38;
							strcpy(tk.tkName,"WITH");
							strcpy(tk.lexeme,"with");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"parameters"))
						{
							tk.tkId = 39;
							strcpy(tk.tkName,"PARAMETERS");
							strcpy(tk.lexeme,"parameters");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"true"))
						{
							tk.tkId = 40;
							strcpy(tk.tkName,"TRUE");
							strcpy(tk.lexeme,"true");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"false"))
						{
							tk.tkId = 41;
							strcpy(tk.tkName,"FALSE");
							strcpy(tk.lexeme,"false");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"takes"))
						{
							tk.tkId = 42;
							strcpy(tk.tkName,"TAKES");
							strcpy(tk.lexeme,"takes");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"input"))
						{
							tk.tkId = 43;
							strcpy(tk.tkName,"INPUT");
							strcpy(tk.lexeme,"input");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"returns"))
						{
							tk.tkId = 44;
							strcpy(tk.tkName,"RETURNS");
							strcpy(tk.lexeme,"returns");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"AND"))
						{
							tk.tkId = 45;
							strcpy(tk.tkName,"AND");
							strcpy(tk.lexeme,"AND");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"OR"))
						{
							tk.tkId = 46;
							strcpy(tk.tkName,"OR");
							strcpy(tk.lexeme,"OR");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"for"))
						{
							tk.tkId = 47;
							strcpy(tk.tkName,"FOR");
							strcpy(tk.lexeme,"for");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"in"))
						{
							tk.tkId = 48;
							strcpy(tk.tkName,"IN");
							strcpy(tk.lexeme,"in");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"switch"))
						{
							tk.tkId = 49;
							strcpy(tk.tkName,"SWITCH");
							strcpy(tk.lexeme,"switch");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"case"))
						{
							tk.tkId = 50;
							strcpy(tk.tkName,"CASE");
							strcpy(tk.lexeme,"case");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"break"))
						{
							tk.tkId = 51;
							strcpy(tk.tkName,"BREAK");
							strcpy(tk.lexeme,"break");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"default"))
						{
							tk.tkId = 52;
							strcpy(tk.tkName,"DEFAULT");
							strcpy(tk.lexeme,"default");
							tk.lineNum = currentLine;
							return tk;
						}
						if (!strcmp(string,"while"))
						{
							tk.tkId = 53;
							strcpy(tk.tkName,"WHILE");
							strcpy(tk.lexeme,"while");
							tk.lineNum = currentLine;
							return tk;
						}
						if (strlen(string) <= 8)
						{
							tk.tkId = 54;
							strcpy(tk.tkName,"ID");
							strcpy(tk.lexeme,string);
							tk.lineNum = currentLine;
							return tk;
						}
						else
						{
							errno[errptr] = 1;
							errline[errptr] = currentLine;
							errptr++;
							tk.tkId = 54;
							strcpy(tk.tkName,"ID");
							strcpy(tk.lexeme,string);
							tk.lineNum = currentLine;
							return tk;
							// printf("ERROR_1 : Identifier at line %d is longer than the prescribed length.\n", currentLine);
						}
				}
				break;
			case 14:
				switch(c){
					case '<':
						state = 1;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						tk.tkId = 55;
						strcpy(tk.tkName, "DRIVERDEF");
						strcpy(tk.lexeme, "<<<");
						tk.lineNum = currentLine;
						return tk;
					default:
						state = 1;
						tk.tkId = 16;
						strcpy(tk.tkName, "DEF");
						strcpy(tk.lexeme, "<<");
						tk.lineNum = currentLine;
						return tk;
				}
				break;
			case 15:
				switch(c){
					case '>':
						state = 1;
						readBuffPointer = incrementReadBuffPointer(readBuffPointer,fp);
						tk.tkId = 56;
						strcpy(tk.tkName, "DRIVERENDDEF");
						strcpy(tk.lexeme, ">>>");
						tk.lineNum = currentLine;
						return tk;
					default:
						state = 1;
						tk.tkId = 19;
						strcpy(tk.tkName, "ENDDEF");
						strcpy(tk.lexeme, ">>");
						tk.lineNum = currentLine;
						return tk;
				}
				break;
		}
	}
}