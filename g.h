// =======================================================================================================
// PPL ASSIGNMENT 1 2020
// GROUP NUMBER 47
// ANUSHKA JAIN 2017B1A70975P
// KUMAR SAURABH 2017B3A70626P
// MANSI MITTAL 2017B1A70991P
// RUCHI BATRA 2017B3A70629P
// =======================================================================================================


#include <stdio.h>
#include <stdlib.h>
#include "gdef.h"


Grammar* readGrammar(char* grammar_text_file);

Grammar* init_grm();
GrmRule* init_rule(int* next_rule_no);
Type_Node_list* init_type_node_list();
Type_Sym_Node* create_type_node(int enum_int, int term_or_nonterm);
Type_Sym_Node* add_node_to_list(Type_Node_list* list, Type_Sym_Node* sym_node, Type_Sym_Node* curr_node);
void add_rule_to_grm(Grammar* grm, NonTerminal non_term, GrmRule* new_rule);
int assign_sym(char* str, int term_or_nonterm);
void print_grammar(Grammar* grm);
