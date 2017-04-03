/*
Batch No 11
Nishant Bansal	2014A7PS052P
Subham Kumar	2014A7PS121P
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>	
#include "parserDef.h"
#include "lexer.h"
#include "utility.h"
#include "parser.h"

char grammar[noofrules][90] = {
	"program moduleDeclarations otherModules driverModule otherModules",
	"moduleDeclarations moduleDeclaration moduleDeclarations",
	"moduleDeclarations EMPTY",
	"moduleDeclaration DECLARE MODULE ID SEMICOL",
	"otherModules module otherModules",
	"otherModules EMPTY",
	"driverModule DRIVERDEF DRIVER PROGRAM DRIVERENDDEF moduleDef",
	"module DEF MODULE ID ENDDEF TAKES INPUT SQBO input_plist SQBC SEMICOL ret moduleDef",
	"ret RETURNS SQBO output_plist SQBC SEMICOL",
	"ret EMPTY",
	"input_plist ID COLON dataType N1",
	"N1 COMMA ID COLON dataType N1",
	"N1 EMPTY",
	"output_plist ID COLON type N2",
	"N2 COMMA ID COLON type N2",
	"N2 EMPTY",
	"dataType INTEGER",
	"dataType REAL",
	"dataType BOOLEAN",
	"dataType ARRAY SQBO range SQBC OF type",
	"type INTEGER",
	"type REAL",
	"type BOOLEAN",
	"moduleDef START statements END",
	"statements statement statements",
	"statements EMPTY",
	"statement ioStmt",
	"statement simpleStmt",
	"statement declareStmt",
	"statement conditionalStmt",
	"statement iterativeStmt",
	"ioStmt GET_VALUE BO ID BC SEMICOL",
	"ioStmt PRINT BO var BC SEMICOL",
	"var ID whichId",
	"var NUM",
	"var RNUM",
	"whichId SQBO ID SQBC",
	"whichId EMPTY",
	"simpleStmt assignmentStmt",
	"simpleStmt moduleReuseStmt",
	"assignmentStmt ID whichStmt",
	"whichStmt lvalueIDStmt",
	"whichStmt lvalueARRStmt",
	"lvalueIDStmt ASSIGNOP expression SEMICOL",
	"lvalueARRStmt SQBO index SQBC ASSIGNOP expression SEMICOL",
	"index NUM",
	"index ID",
	"moduleReuseStmt optional USE MODULE ID WITH PARAMETERS idList SEMICOL",
	"optional SQBO idList SQBC ASSIGNOP",
	"optional EMPTY",
	"idList ID N3",
	"N3 COMMA ID N3",
	"N3 EMPTY",
	"expression arithmeticOrBooleanExpr",
	"expression MINUS BO arithmeticExpr BC",
	"arithmeticOrBooleanExpr AnyTerm N7",
	"N7 logicalOp AnyTerm N7",
	"N7 EMPTY",
	"AnyTerm arithmeticExpr N8",
	"N8 relationalOp arithmeticExpr N8",
	"N8 EMPTY",
	"arithmeticExpr term N4",
	"N4 op1 term N4",
	"N4 EMPTY",
	"term factor N5",
	"N5 op2 factor N5",
	"N5 EMPTY",
	"factor var",
	"factor BO arithmeticOrBooleanExpr BC",
	"op1 PLUS",
	"op1 MINUS",
	"op2 MUL",
	"op2 DIV",
	"logicalOp AND",
	"logicalOp OR",
	"relationalOp LT",
	"relationalOp LE",
	"relationalOp GT",
	"relationalOp GE",
	"relationalOp EQ",
	"relationalOp NE",
	"declareStmt DECLARE idList COLON dataType SEMICOL",
	"conditionalStmt SWITCH BO ID BC START caseStmts default END",
	"caseStmts CASE value COLON statements BREAK SEMICOL N9",
	"N9 CASE value COLON statements BREAK SEMICOL N9",
	"N9 EMPTY",
	"value NUM",
	"value TRUE",
	"value FALSE",
	"default DEFAULT COLON statements BREAK SEMICOL",
	"default EMPTY",
	"iterativeStmt FOR BO ID IN range BC START statements END",
	"iterativeStmt WHILE BO arithmeticOrBooleanExpr BC START statements END",
	"range NUM RANGEOP NUM"
};

int readline(FILE *f, char *buffer, size_t len){
   char c; 
   int i;

   memset(buffer, 0, len);

   for (i = 0; i < len; i++)
   {   
      int c = fgetc(f); 

      if (!feof(f)) 
      {   
         if (c == '\r')
            buffer[i] = 0;
         else if (c == '\n')
         {   
            buffer[i] = 0;

            return i+1;
         }   
         else
            buffer[i] = c; 
      }   
      else
      {   
         //fprintf(stderr, "read_line(): recv returned %d\n", c);
         return -1; 
      }   
   }   

   return -1; 
}

void populateFirst(char * file){
	int l,m;
	for(l=0;l<rows;l++){
		for(m=0;m<fnflen;m++){
			first[l][m] = -1;
		}
	}
	FILE * fd = fopen(file,"r");
	int i;
	for(i=0;i<rows;i++)
	{
		char tbuff[100];
		readline(fd, tbuff, 100);
		int j = 0;
		char * pch;
		pch = strtok(tbuff," ");
		pch = strtok(NULL," ");
		while(pch != NULL){
			// printf("%s %d\n", pch, getTokenId("ID"));
			first[i][j] = getTokenId(pch);
			j++;
			pch = strtok(NULL," ");
		}
		// printf("%s\n", tbuff);
	}
	
	fclose(fd);
}

void populateFollow(char * file){
	int l,m;
	for(l=0;l<rows;l++){
		for(m=0;m<fnflen;m++){
			follow[l][m] = -1;
		}
	}
	FILE * fd = fopen(file,"r");
	int i;
	for(i=0;i<rows;i++)
	{
		char tbuff[100];
		readline(fd, tbuff, 100);
		int j = 0;
		char * pch;
		pch = strtok(tbuff," ");
		pch = strtok(NULL," ");
		while(pch != NULL){
			// printf("%s %d\n", pch, getTokenId("ID"));
			follow[i][j] = getTokenId(pch);
			j++;
			pch = strtok(NULL," ");
		}
		// printf("%s\n", tbuff);
	}
	
	fclose(fd);
}

void createParseTable(){
	int ruleNum = 0;
	for(ruleNum=0;ruleNum<94;ruleNum++){
		int rowNum; //row number of first follow and parseTable
		int NTid; //NTid : basically rowNum + 101
		int RHS[100] = {-1}; //array for storing rhs og grammar rule
		char rulebuff[90]; //temporary buffer for storing grammar rule
		strcpy(rulebuff,grammar[ruleNum]);
		int n = 0; //n is the number of elements in RHS of a grammar rule
		char * pch;
		pch = strtok(rulebuff," ");
		rowNum = getTokenId(pch)-101;
		// printf("%s\n", grammar[ruleNum]);
		NTid = getTokenId(pch);
		// printf("%d\n", NTid);
		pch = strtok(NULL," ");
		while(pch != NULL){
			// printf("%s %d\n", pch, getTokenId("ID"));
			RHS[n] = getTokenId(pch);
			pch = strtok(NULL," ");
			n++;
		}
		//int rhsFirst[columns] = {0};
		int i;
		// printf("%d %d\n", n,RHS[0]);
		if (n==1 && RHS[0] == 0)
		{
			int k;
			for(k=0;k<fnflen;k++){
				// printf("%d\n", follow[rowNum][k]);
				int c = follow[rowNum][k];
				if (c == -1)
				{
					break;
				}
				else
				{
					// printf("%d %d\n", rowNum, c-1);
					parseTable[rowNum][c-1] = ruleNum + 1;
				}
			}
		}
		for(i=0;i<n;i++){
			
			if (RHS[i] < 100 && RHS[i] > 0)
			{
				// printf("%d %d\n", rowNum, RHS[i]-1);
				parseTable[rowNum][RHS[i]-1] = ruleNum + 1;
				break;
			}
			else if (RHS[i] >= 100)
			{
				int flag = 0;
				int k = 0;
				for(k=0;k<fnflen;k++){
					if (first[RHS[i]-101][k] == -1)
					{
						break;
					}
					if (first[RHS[i]-101][k] == 0)
					{
						flag = 1;
					}
					else{
						// printf("%d %d\n", rowNum,first[RHS[i]-101][k]-1);
						parseTable[rowNum][first[RHS[i]-101][k]-1] = ruleNum+1;
					}
				}
				if (flag == 0)
				{
					break;
				}
			}
		}
		
		// printf("%d RHS:", n);
		// int z = 0;
		// for(z=0;z<n;z++){
		// 	printf("%d ", RHS[z]);
		// }
		// printf("\n");
	}
}

void print(){
	struct Node * temp = head;
	while(temp != NULL){
		idtotk(temp->data);
		printf(" -> ");
		temp = temp -> next;
	}
	printf("EOP\n");
}

void push(int Tkid){
	struct Node * newNode;
    newNode = (struct Node*) malloc (sizeof(struct Node));
    newNode->data = Tkid;
    if(head == NULL)
      newNode->next = NULL;
    else
      newNode->next = head;
    head = newNode;
}

void pop(){
	if(head == NULL){
    	//empty stack 
	}
    else
	{
		struct Node *temp = head;
		head = temp->next;
		free(temp);
	}
}

void parseInputSourceCode(char * file){
	state = 1;

	FILE * fd = fopen(file,"r");
	getStream(fd);
	int i;
	// for (i = 0; i < 100; ++i)
	// {
	// 	tokenInfo tk = getNextToken(fd);
	// 	printf("%s %s %d\n", tk.tkName, tk.lexeme, tk.lineNum);
	// }
	T = (struct treenode *) malloc (sizeof(struct treenode));
	T->id = 139;
	T->parent = NULL;
	T->child = NULL;
	T->sibling = NULL;
	strcpy(T->lexeme,"----");

	struct treenode * currentNode = T;
	struct treenode * endmarker = (struct treenode *) malloc (sizeof(struct treenode));
	endmarker->id = 200;
	endmarker->parent = NULL;
	endmarker->child = NULL;
	endmarker->sibling = NULL;
	// strcpy(T->,"----");
	T->sibling = endmarker;

	push(57);
	push(139);
	tokenInfo token;
	token = getNextToken(fd);
	// printf("%s\n", token.lexeme);
	// int x = 0;
	while(1){
		// printf("enter the while loop with current node at ");
		// idtotk(currentNode->id);
		// printf("\n");
		if (currentNode->id == 200)
		{
			break;
		}
		// print();
		if (token.tkId == 57 && head->data == 57)
		{
			break;
		}
		// if (head != NULL && token.tkId == 57 && head->data != 57)
		// {
		// 	syntaxFlag = 1;
		// 	break;
		// }
		if (token.tkId != 57 && head->data == 57)
		{
			syntaxFlag = 1;
			break;
		}
		if (token.tkId == head->data)
		{
			// printf("Popped "); idtotk(head->data); printf("\n");
			strcpy(currentNode->lexeme,token.lexeme);
			currentNode->linenum = token.lineNum;
			while(currentNode->sibling == NULL){
				currentNode = currentNode->parent;
			}
			// printf("yo ");
			// idtotk(currentNode->id);
			currentNode = currentNode->sibling;
			pop();
			// printf("   ");
			// idtotk(currentNode->id);
			// printf("\n");
			// printf("haila\n");
			token = getNextToken(fd);
			// printf("haila\n");
			continue;
		}
		else if (head->data < 100 && token.tkId != head->data)
		{
			syntaxFlag = 1;
			perrline[perrptr] = token.lineNum;
			perrtk[perrptr] = token.tkId;
			perrex[perrptr] = head->data;
			strcpy(perrlex[i],token.lexeme);
			perrptr++;
			break;
		}
		else if(head->data > 100)
		{

			int top = head->data;
			// printf("top %d ", top);
			// idtotk(top);
			// printf("tokenid %d",token.tkId);
			// idtotk(token.tkId);
			// printf("\n");
			int ruleApply = parseTable[top-101][(token.tkId)-1];
			// printf("ruleApply %d\n", ruleApply);
			if (ruleApply == 0)
			{
				syntaxFlag = 1;
				perrline[perrptr] = token.lineNum;
				perrtk[perrptr] = token.tkId;
				perrex[perrptr] = head->data;
				strcpy(perrlex[i],token.lexeme);
				perrptr++;
				break;
			}
			// printf("%d\n", parseTable[38][53]);
			pop();
			char rulebuff[90]; //temporary buffer for storing grammar rule
			strcpy(rulebuff,grammar[ruleApply-1]);
			int RHS[100] = {-1};
			int n = 0; //n is the number of elements in RHS of a grammar rule
			char * pch;
			pch = strtok(rulebuff," ");
			pch = strtok(NULL," ");
			while(pch != NULL){
				// printf("%s %d\n", pch, getTokenId("ID"));
				RHS[n] = getTokenId(pch);
				pch = strtok(NULL," ");
				n++;
			}
			int i;
			for(i=n-1;i>=0;i--){
				if(RHS[i] != 0)
					push(RHS[i]);
			}
			// print();
			// if (token.tkId == 57 && head->data == 57)
			// {
			// 	break;
			// }
			int j = 0;
			if (RHS[j] == 0)
			{
				struct treenode * temp = (struct treenode *) malloc (sizeof(struct treenode));
				currentNode->child = temp;
				temp->id = 0;
				temp->parent = currentNode;
				temp->child = NULL;
				temp->sibling = NULL;
				temp->linenum = token.lineNum;
				strcpy(temp->lexeme,"EMPTY");
				while(currentNode->sibling == NULL){
					currentNode = currentNode->parent;
				}
				currentNode = currentNode->sibling;
				continue;
			}
			struct treenode * temp = (struct treenode *) malloc (sizeof(struct treenode));
			currentNode->child = temp;
			temp->id = RHS[j];
			temp->parent = currentNode;
			temp->child = NULL;
			temp->sibling = NULL;
			temp->linenum = token.lineNum;
			strcpy(temp->lexeme,"----");
			
			struct treenode * ptr = currentNode->child;
			// struct treenode * temp = (struct treenode *) malloc (sizeof(struct treenode));
			for(j=1;j<n;j++){
				struct treenode * temp = (struct treenode *) malloc (sizeof(struct treenode));
				temp->id = RHS[j];
				ptr->sibling = temp;
				temp->parent = currentNode;
				temp->child = NULL;
				temp->sibling = NULL;
				temp->linenum = token.lineNum;
				strcpy(temp->lexeme,"----");
				ptr = ptr->sibling;
			}
			currentNode = currentNode->child;
			// x = 1;
			
		}
	}
	 
	if (syntaxFlag == 1)
	{
		printf("INCORRECT SYNTAX\n");
	}
	else if (token.tkId == 57 && head->data == 57)
	{
		printf("CORRECT SYNTAX\n");
		return;
	}
	else
	{
		printf("INCORRECT SYNTAX\n");
	}
	printf("Errors in parsing:\n");
	i = 0;
	for(i=0;i<perrptr;i++){
		// printf("perrex = %d\n");
		if (perrex[i] < 100)
		{
			printf("ERROR_5: The token %s for %s does not match at line %d. The expected token here is %s\n", idtotkstr(perrtk[i]), perrlex[i], perrline[i], idtotkstr(perrex[i]));
		}
		else
		{
			printf("ERROR_5: The token %s for %s does not match at line %d. The expected token here is ", idtotkstr(perrtk[i]), perrlex[i], perrline[i]);
			int j = 0;
			for(j=0;j<columns;j++){
				if (parseTable[perrex[i]-101][j] == 0)
				{
					continue;
				}
				else
				{
					printf("%s, ", idtotkstr(j+1));
				}
			}
			printf("\n");
		}
	}
}

void inorderT(struct treenode * curr, FILE * fd){
	if (curr == NULL)
	{
		return;
	}
	inorderT(curr->child,fd);
	fprintf(fd,"%15s ", curr->lexeme);
	if (curr->child == NULL)
	{
		fprintf(fd,"%5d ", curr->linenum);
	}
	else
	{
		fprintf(fd,"%5s ", "----");
	}
	if (curr->child == NULL)
	{
		fprintf(fd,"%15s ",idtotkstr(curr->id));
	}
	else
	{
		fprintf(fd,"%15s ", "-----");
	}
	fprintf(fd,"%25s ",idtotkstr(curr->id));
	if (curr->id == 21 || curr->id == 23)
	{
		fprintf(fd,"%20s ", curr->lexeme);
	}
	else
	{
		fprintf(fd,"%20s ", "-------");
	}
	if (curr->id == 139)
	{
		fprintf(fd,"%25s ", "ROOT");
	}
	else
	{
		fprintf(fd,"%25s ", idtotkstr(curr->parent->id));
	}
	if (curr->child == NULL)
	{
		fprintf(fd,"%5s ", "yes");
	}
	else
	{
		fprintf(fd,"%5s ", "no");
	}
	if (curr->child == NULL)
	{
		fprintf(fd,"%25s ", "-----");
	}
	else
	{
		fprintf(fd,"%25s ", idtotkstr(curr->id));
	}
	// idtotk(curr->id);
	// if (curr->child == NULL)
	// {
		// printf("%s\n", );
	// }
	fprintf(fd,"\n");
	struct treenode * temp = curr->child;
	if (temp == NULL)
	{
		return;
	}
	while(temp->sibling != NULL){
		inorderT(temp->sibling,fd);
		// idtotk(temp->sibling->id);
		// printf("\n");
		temp = temp->sibling;
	}
	// if (curr->child != NULL)
	// {
	// 	inorderT(curr->child);
	// 	idtotk(curr->id);
	// 	printf("\n");
	// 	// return;
	// }
	// else
	// {
	// 	idtotk(curr->id);
	// 	printf("\n");
	// 	return;
	// }
	// curr = curr->sibling;
	// if (curr != NULL)
	// {
	// 	inorderT(curr);
	// }
}