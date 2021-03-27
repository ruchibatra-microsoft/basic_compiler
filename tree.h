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
#include <stdbool.h>
#include <string.h>
// #include "g.h"
#include "tok.h"

union typeExp{
    
    char* str; // if array or none type 
    int i;
    float f;
    bool b;
};

// Linked List of siblings
struct linkedlist{
	struct treenode* head;
	int no_siblings;
};
typedef struct linkedlist Children;

// parse tree node c 
typedef struct treenode{
    struct treenode * parent;
    struct treenode * next; // points to its siblings 
    int term_nonterm;
    Type_Node type; // Terminal or non Terminal 
    Token_s tok; // has line number, token name (Keyword, Op, Symbol) and lexeme (;, }, var, etc), anything that appears in the program
    // tok will be all zeroes and nulls if not a LEAF NODE  
    Children * child;
    int rule_no;
    int height; // handle the height
    union typeExp te;
}TreeNode;



typedef struct tree{
    TreeNode * root;
    TreeNode * next;
}ParseTree;

//initialise tree
ParseTree * iniatilizeTree();
// initialise tree node 
TreeNode* initialize_TreeNode(TreeNode * parent, int rule_no, int term_nonterm, Type_Node type);
// add child 
Children * makeChildList(TreeNode* parent, GrmRule* grm_rule);
// 
Children* initialize_children();

void printTreeNode(TreeNode *tn);
void printParseTree(ParseTree *t);

// TreeNode * TreeNodeLinkedList(GrmRule * grm_rule);
void deallocateChildren(Children * children);