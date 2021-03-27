// =======================================================================================================
// PPL ASSIGNMENT 1 2020
// GROUP NUMBER 47
// ANUSHKA JAIN 2017B1A70975P
// KUMAR SAURABH 2017B3A70626P
// MANSI MITTAL 2017B1A70991P
// RUCHI BATRA 2017B3A70629P
// =======================================================================================================


#ifndef _PARSERDEF_
#define _PARSERDEF_

#include <stdio.h>
#include <stdlib.h>

#define TOKEN_TYPES 51

#define NUM_NON_TERMS 41

#define NUM_TERMS 40

#define MX_NODE_SIZE 40

typedef enum{
	PROGRAM, SZ, OP, CL, COP, CCL, SQOP, SQCL, DOTS, EPSILON, COLON, SEMICOLON, ID, IDB, NUM, INT, BOOLEAN, REAL, ARRAY, JAGGED, DEC, LIST, OF, VARIABLES, R, VALUES, EQUALS, PLUS, MINUS, MUL, DIV, AND, OR,DOLLAR 
}Terminal;


typedef enum{
program, stmts, stmt, more_stmts, decl, declaration, assign, var_list, type, primitive, array, rectangular, jagged, arr_dims, arr_dim, range, low, high, rows_dec_R1, rows_dec_jR1, op_dim, rowjj, rowj, expression, expression_arith, expression_bool, term, term_bool, factor, factor_bool, ind_list, more_ind_list, remaining_var, more_rowj, more_rowjj, array_op, op_no_op_or, op_no_op_and, op_plus_minus, op_mul_div, more_arr_dims
}NonTerminal;

typedef union{
	Terminal terminal;
	NonTerminal nonterminal;
}Type_Node;

struct type_sym_node{
	Type_Node type; 
	int term_or_nonterm; 
	struct type_sym_node* next; 
};

typedef struct type_sym_node Type_Sym_Node;

struct node_list{
	Type_Sym_Node* head;
	int length; 
};

typedef struct node_list Type_Node_list;


struct grm_rule{
	Type_Node_list* symbols; 
	struct grm_rule* next; 
	int rule_no;
};
typedef struct grm_rule GrmRule;


struct rules{
	GrmRule* head; 
	int length; 
};

typedef struct rules GrmRules;


//Grammar as an array of rules
struct grammar{
	int num_rules;
	GrmRules** rules; 	
};

typedef struct grammar Grammar;


#endif



