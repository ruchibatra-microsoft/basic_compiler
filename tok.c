// =======================================================================================================
// PPL ASSIGNMENT 1 2020
// GROUP NUMBER 47
// ANUSHKA JAIN 2017B1A70975P
// KUMAR SAURABH 2017B3A70626P
// MANSI MITTAL 2017B1A70991P
// RUCHI BATRA 2017B3A70629P
// =======================================================================================================


#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#include "tok.h"

#define TOTAL_NUM_TERMINALS 34


char* TerminalMapTok[] = {
	"PROGRAM", "SZ", "OP", "CL", "COP", "CCL", "SQOP", "SQCL", "DOTS", "EPSILON", "COLON", "SEMICOLON", "ID", "IDB", "NUM", "INT", "BOOLEAN", "REAL", "ARRAY", "JAGGED", "DEC", "LIST", "OF", "VARIABLES", "R", "VALUES", "EQUALS", "PLUS", "MINUS", "MUL", "DIV", "AND", "OR","DOLLAR"
};

// declared in gdef.h
char* TypeTok[] = {
	"program", "size", "(", ")", "{", "}", "[", "]", "..", "EPSILON", ":", ";", "ID", "IDB", "NUM", "integer", "boolean", "real", "array", "jagged", "declare", "list", "of", "variables", "R1", "values", "=", "+", "-", "*", "/", "&&&", "|||","$"
};

// 14 keywords
char KEYWORDS[][100]= { 
    "program","declare","list","of","integer","boolean","real","array","variables","jagged","size","values","integer","R1"  
    };

// 7 operators
char OPERATORS[][100]={
    "+","-","*","/","=","&&&","|||",
};

// 11 symbols 
char SYMBOLS[][100]={
    ":","[","]","(",")","{","}","...","()",";" // removed ;\n
};

int line_number=0;

void get_token(Token_s * temp ) 
{   
    // 14 keywords
    for(int i=0;i<14;++i)
    {
        if(strcmp(temp->lexeme,KEYWORDS[i])==0)
        {   
            strcpy(temp->token_name,"KEYWORDS");

            return ;
        }
    }
    // for symbols 
    for(int i=0;i<9;++i)
    {
        if(strcmp(temp->lexeme,SYMBOLS[i])==0)
        {
                strcpy(temp->token_name,"SYMBOLS");
                return ;
        }
    }

    // for operators
    for(int i=0;i<7;++i)
    {
        if(strcmp(temp->lexeme,OPERATORS[i])==0)
        {
            strcpy(temp->token_name,"OPERATORS");
            return;
        }
    }

    //  for constants 
    if(temp->lexeme[0]>='0' && temp->lexeme[0]<='9')
    {
        strcpy(temp->token_name,"CONSTANTS");
        return ;
    }
    else
    {
        strcpy(temp->token_name,"IDENTIFIERS");
        return ;
    }
    
}

int findfromTerminalMaptoTerminal(char* str){
	//Terminal
		for(int i=0;i<TOTAL_NUM_TERMINALS;i++){
            // printf("\n Inside term map i is %d : ",i);
			if(strcmp(str,TerminalMapTok[i])==0){
    
				return i;}
		}
}

void findmapping(Token_s * st){
    // removeChar(st->lexeme, '\n');
    for(int i = 0; i< TOTAL_NUM_TERMINALS; i++){
        // printf("\n Type[i] is : %s and lexeme is : %s \n", Type[i], st->lexeme);
        if(!strcmp(TypeTok[i], st->lexeme)){ // Type and lexeme will be of the same kind 
        
            int j = findfromTerminalMaptoTerminal(TerminalMapTok[i]);
            st->type = (Terminal)j;
            break;
            // printf("\n Terminal %d %d \n", j, st->type);
        }
        else{
            if(isInt(st->lexeme)){
            st->type = NUM;
        }
            else{
            st->type = ID;
        }
        }
    }

}


void removeChar(char *str, char garbage) {
    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}


int isEmpty(const char *str)
{
    char ch;
    do
    {
        ch = *(str++);
        // Check non whitespace character
        if(ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r' && ch != '\0')
            return 0;
    } while (ch != '\0');
    return 1;
}

void push(char *  str, tokenstream * s)
{
    printf("\n");
    printf("%d ",line_number);
    ++line_number;
    char delim[] = " ";
    char *ptr = strtok(str, delim);
    // printf("Pointer is : %s \n", ptr);
    while( ptr != NULL && *ptr!='\n')
	{
        if(isEmpty(ptr)){
            break;
        }
        if(s->head==NULL ) // token stream is just being initialised 
        {
            struct token_s * temp =  (struct token_s  *) malloc( sizeof(Token_s)) ;
            temp->line_number=line_number;
            temp->lexeme= (char * )malloc(strlen(ptr)+1);
            strcpy(temp->lexeme,ptr);
            removeChar(temp->lexeme, '\t');
            removeChar(temp->lexeme, '\n');
            removeChar(temp->lexeme, ' ');
            if(ptr != NULL){
                get_token(temp); // adds info to token name                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        ;
                temp->next=NULL;
                
                s->head=temp;
                s->tail=temp;
                findmapping(temp);}
        }

        else
        {
            if(isEmpty(ptr)){
            break;
        }
            struct token_s * temp =  (struct token_s*)malloc(sizeof(struct token_s));
            temp->line_number=line_number;
            temp->lexeme= (char *)malloc(strlen(ptr)+1);
            strcpy(temp->lexeme,ptr);
            removeChar(temp->lexeme, '\t');
            removeChar(temp->lexeme, '\n');
            removeChar(temp->lexeme, ' ');

            // printf(" \n SOMETHING $$$$$$$$$$$$$$$ %s", ptr);
            if(ptr!=NULL){
                get_token(temp);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       ;
                temp->next=NULL;
                findmapping(temp);
                
                s->tail->next=temp;    
                s->tail=s->tail->next;}
        }
    
        printf("%s ", ptr); 
    	ptr = strtok(NULL, delim);
    }
}

// New func for checking int 
int isInt(char* s)
{
	for(int i=0;s[i]!='\0';i++)
	{
		if (isdigit(s[i]) == 0) // check 
            		return 0;
	}
	return 1;
}

void printlinklist(struct token_s * temp)
{
	struct token_s * temp2=temp->next;
    printf("\n ====================Program Token Stream=====================\n");
    while(temp)
    {
        printf("\n");
        printf(" line number : %d ",temp->line_number);
        printf(" lexeme : %s ",temp->lexeme);
        printf(" Terminal : %s", TerminalMapTok[temp->type]);
        //printf(" Terminal : %d", temp->type);
        printf(" tokenname : %s \n ",temp->token_name);
	if(temp2->next==NULL)
		temp->next=NULL;
	temp=temp->next;
	temp2=temp2->next;
        

    }
    
    return ;
}

tokenstream * tokenizeSourceCode(char* sourceCode)
{
    //char * f = "Test_Cases/Sample_test1.txt";
    FILE * fileptr = fopen(sourceCode,"r");

    // struct linkedlist *head=(struct linkedlist*) malloc (sizeof(struct linkedlist));
    // head->first=NULL;
    tokenstream * s = (tokenstream *)malloc (sizeof(tokenstream));
    s->head=NULL;
    s->tail=NULL;

    if(fileptr)
    {
        while(!feof(fileptr))
        {
            char currline[5000];
            fgets(currline,5000,fileptr);
            push(currline,s);
        }

    }
    else
    {
        printf("\n The file location entered does not exist. ");
    }
        printf("\n Linklist starts here ");

        printlinklist(s->head);

    return s;
}


// int main(){
//     tokenstream * s = tokenizeSourceCode("Test_Cases/Sample_test1.txt");
// }
