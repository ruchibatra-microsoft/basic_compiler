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
#include <stdbool.h>
// #include "tokenizer.h"
// #include "tree.h"
// #include "g.h"
#include "stack.h"

void push_rule_reverse_ruchi(GrmRule * grm_rule, AuxStack * as, MainStack * ms, Children * children );
bool match(Token_s * lookahead , TreeNode * tos);
bool traverseGrammarRules(MainStack * ms, AuxStack * as, TreeNode * tn, Grammar * grm, Token_s * looakahead);
TreeNode * createParseTree(char * address);
bool parsing(MainStack * ms, AuxStack * as, Grammar * grm, Token_s * lookahead );
void preordertraversal(TreeNode * root);




