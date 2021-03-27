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
// #include "g.h"
#include "tree.h"

typedef struct main_stack_node{

    TreeNode * stack_tree_node;
    struct main_stack_node * next_node;
    
}MainStackNode;

typedef struct main_stack_list{
    MainStackNode* head;
}MainStackList;
 
struct main_stack{
    MainStackList* ms_list;
    int capacity;
    int height;
};
typedef struct main_stack MainStack;


typedef struct aux_stack_node{
    TreeNode * stack_tree_node_a;
    struct aux_stack_node * next_node_a;
}AuxStackNode;


typedef struct aux_stack_list{
    AuxStackNode* head;
}AuxStackList;

typedef struct aux_stack{
    AuxStackList * as_list;
    int size;
    // unsigned capacity;  maybe not, take something big 
}AuxStack;

// Initialize
MainStack* initialize_main_stack();
AuxStack* initilaize_aux_stack();

// isempty Main
bool stackisEmpty(MainStack * ms); 
bool auxstackisEmpty(AuxStack * as);

// create 
MainStackNode* create_main_stack_node();
AuxStackNode* create_aux_stack_node();
// push 
void push_ms(MainStack * ms, TreeNode * treenode);
void push_as(AuxStack * as, TreeNode * treenode);

// pop
TreeNode* pop_ms(MainStack * ms);
TreeNode* pop_as(AuxStack * as);

// pop n elements 
void pop_n(MainStack * ms, int poppin);
void pop_all_as(AuxStack * as);

// push from aux stack to main 
void push_rule_reverse(GrmRule * grm_rule, AuxStack * as, MainStack *ms);

// return top of stack;
TreeNode * topofMainStack(MainStack * ms);