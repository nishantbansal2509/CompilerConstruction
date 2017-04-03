/*
Batch No 11
Nishant Bansal	2014A7PS052P
Subham Kumar	2014A7PS121P
*/

#ifndef PARSERDEF_H_INCLUDED
#define PARSERDEF_H_INCLUDED

#include <stdio.h>

#define rows 51
#define columns 57
#define fnflen 20
#define noofrules 94

int first[rows][fnflen];

int follow[rows][fnflen];

int parseTable[rows][columns];

struct treenode{
	int id;
	struct treenode * parent;
	struct treenode * child;
	struct treenode * sibling;
	char lexeme[33];
	int linenum;
};

int perrptr;
int perrline[100];
int perrtk[100];
int perrex[100];
char perrlex[100][30];

struct treenode * T;

int syntaxFlag;

struct Node
{
   int data;
   struct Node *next;
};

struct Node * head;

extern char grammar[noofrules][90];

#endif

// char grammar[noofrules][90] = {
// "program moduleDeclarations otherModules driverModule otherModules",
// "moduleDeclarations moduleDeclaration moduleDeclarations",
// "moduleDeclarations EMPTY",
// "moduleDeclaration DECLARE MODULE ID SEMICOL",
// "otherModules module otherModules",
// "otherModules EMPTY",
// "driverModule DRIVERDEF DRIVER PROGRAM DRIVERENDDEF moduleDef",
// "module DEF MODULE ID ENDDEF TAKES INPUT SQBO input_plist SQBC SEMICOL ret moduleDef",
// "ret RETURNS SQBO output_plist SQBC SEMICOL",
// "ret EMPTY",
// "input_plist ID COLON dataType N1",
// "N1 COMMA ID COLON dataType N1",
// "N1 EMPTY",
// "output_plist ID COLON type N2",
// "N2 COMMA ID COLON type N2",
// "N2 EMPTY",
// "dataType INTEGER",
// "dataType REAL",
// "dataType BOOLEAN",
// "dataType ARRAY SQBO range SQBC OF type",
// "type INTEGER",
// "type REAL",
// "type BOOLEAN",
// "moduleDef START statements END",
// "statements statement statements",
// "statements EMPTY",
// "statement ioStmt",
// "statement simpleStmt",
// "statement declareStmt",
// "statement conditionalStmt",
// "statement iterativeStmt",
// "ioStmt GET_VALUE BO ID BC SEMICOL",
// "ioStmt PRINT BO var BC SEMICOL",
// "var ID whichId",
// "var NUM",
// "var RNUM",
// "whichId SQBO ID SQBC",
// "whichId EMPTY",
// "simpleStmt assignmentStmt",
// "simpleStmt moduleReuseStmt",
// "assignmentStmt ID whichStmt",
// "whichStmt lvalueIDStmt",
// "whichStmt lvalueARRStmt",
// "lvalueIDStmt ASSIGNOP expression SEMICOL",
// "lvalueARRStmt SQBO index SQBC ASSIGNOP expression SEMICOL",
// "index NUM",
// "index ID",
// "moduleReuseStmt optional USE MODULE ID WITH PARAMETERS idList SEMICOL",
// "optional SQBO idList SQBC ASSIGNOP",
// "optional EMPTY",
// "idList ID N3",
// "N3 COMMA ID N3",
// "N3 EMPTY",
// "expression arithmeticOrBooleanExpr",
// "expression MINUS BO arithmeticExpr BC",
// "arithmeticOrBooleanExpr AnyTerm N7",
// "N7 logicalOp AnyTerm N7",
// "N7 EMPTY",
// "AnyTerm arithmeticExpr N8",
// "N8 relationalOp arithmeticExpr N8",
// "N8 EMPTY",
// "arithmeticOrBooleanExpr BO arithmeticOrBooleanExpr BC",
// "arithmeticExpr term N4",
// "N4 op1 term N4",
// "N4 EMPTY",
// "term factor N5",
// "N5 op2 factor N5",
// "N5 EMPTY",
// "factor var",
// "op1 PLUS",
// "op1 MINUS",
// "op2 MUL",
// "op2 DIV",
// "logicalOp AND",
// "logicalOp OR",
// "relationalOp LT",
// "relationalOp LE",
// "relationalOp GT",
// "relationalOp GE",
// "relationalOp EQ",
// "relationalOp NE",
// "declareStmt DECLARE idList COLON dataType SEMICOL",
// "conditionalStmt SWITCH BO ID BC START caseStmts default END",
// "caseStmts CASE value COLON statements BREAK SEMICOL N9",
// "N9 CASE value COLON statements BREAK SEMICOL N9",
// "N9 EMPTY",
// "value NUM ",
// "value TRUE",
// "value FALSE",
// "default DEFAULT COLON statements BREAK SEMICOL ",
// "default EMPTY",
// "iterativeStmt FOR BO ID IN range BC START statements END",
// "iterativeStmt WHILE BO arithmeticOrBooleanExpr BC START statements END",
// "range NUM RANGEOP NUM"
// };