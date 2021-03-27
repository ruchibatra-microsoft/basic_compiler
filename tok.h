// =======================================================================================================
// PPL ASSIGNMENT 1 2020
// GROUP NUMBER 47
// ANUSHKA JAIN 2017B1A70975P
// KUMAR SAURABH 2017B3A70626P
// MANSI MITTAL 2017B1A70991P
// RUCHI BATRA 2017B3A70629P
// =======================================================================================================


#include <stdlib.h>
#include <stdio.h>
#include "g.h"

// declared in gdef.h
// typedef enum{
// 	PROGRAM, SZ, OP, CL, COP, CCL, SQOP, SQCL, DOTS, EPSILON, COLON, SEMICOLON, ID, IDB, NUM, INT, BOOLEAN, REAL, ARRAY, JAGGED, DEC, LIST, OF, VARIABLES, R, VALUES, EQUALS, PLUS, MINUS, MUL, DIV, AND, OR,DOLLAR 
// }Terminal;


struct token_s 
{
    int line_number;
    char token_name[50];
    char * lexeme;
    Terminal type;
    struct token_s * next;
}; 
typedef struct token_s Token_s;

typedef struct
{
    struct token_s * head;
    struct token_s *tail;
}tokenstream;

void get_token(Token_s * temp );
void push(char *  str, tokenstream * s);
void printlinklist(Token_s * temp);
int isInt(char*s);
void findmapping(Token_s * st);
char * findnewline(char *s);
void removeChar(char *str, char garbage);
tokenstream * tokenizeSourceCode(char* sourceCode);


