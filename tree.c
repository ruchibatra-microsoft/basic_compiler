// =======================================================================================================
// PPL ASSIGNMENT 1 2020
// GROUP NUMBER 47
// ANUSHKA JAIN 2017B1A70975P
// KUMAR SAURABH 2017B3A70626P
// MANSI MITTAL 2017B1A70991P
// RUCHI BATRA 2017B3A70629P
// =======================================================================================================


#include "tree.h"
#include "g.h"

char* TerminalMapTree[] = {
	"PROGRAM", "SZ", "OP", "CL", "COP", "CCL", "SQOP", "SQCL", "DOTS", "EPSILON", "COLON", "SEMICOLON", "ID", "IDB", "NUM", "INT", "BOOLEAN", "REAL", "ARRAY", "JAGGED", "DEC", "LIST", "OF", "VARIABLES", "R", "VALUES", "EQUALS", "PLUS", "MINUS", "MUL", "DIV", "AND", "OR","DOLLAR"
};

char* NonTerminalMapTree[] = {
    "program", "stmts", "stmt", "more_stmts", "decl", "declaration", "assign", "var_list", "type", "primitive", "array", "rectangular", "jagged", "arr_dims", "arr_dim", "range", "low", "high", "rows_dec_R1", "rows_dec_jR1", "op_dim", "rowjj", "rowj", "expression", "expression_arith", "expression_bool", "term", "term_bool", "factor", "factor_bool", "ind_list", "more_ind_list", "remaining_var", "more_rowj", "more_rowjj", "array_op", "op_no_op_or", "op_no_op_and", "op_plus_minus", "op_mul_div", "more_arr_dims"
};


//initialise tree
ParseTree * iniatilizeTree(){
    // printf("Inside Tree init \n");
    ParseTree * parsetree = (ParseTree *)malloc(sizeof(ParseTree));
    //parsetree->root = NULL;
    parsetree->next = NULL;

    // alt
    Type_Node t;
    t.nonterminal = program;
    parsetree->root = initialize_TreeNode(NULL, 1, 1, t);
    parsetree->root->height = 0;
    return parsetree;    
}

// initialise tree node 
TreeNode* initialize_TreeNode(TreeNode * parent, int rule_no, int term_nonterm, Type_Node type){
    // printf("Tree Node init \n");
    TreeNode * treenode = (TreeNode *)malloc(sizeof(TreeNode));
    treenode->parent = parent;
    treenode->child = NULL;
    treenode->next = NULL;
    treenode->rule_no =rule_no; // 
    treenode->term_nonterm = term_nonterm;
    if(term_nonterm ==0){
        treenode->type.terminal = type.terminal;
    }
    else{
        treenode->type.nonterminal = type.nonterminal;
    }
    if(parent != NULL){
    treenode->height = parent->height + 1;}

    // printf("initialize_TreeNode exiting %d \n", type);
    return treenode;
    
}
// add child 
// push the symbols corresponding to the entire grm_rule once it is decided that it fits
Children * makeChildList(TreeNode* parent, GrmRule* grm_rule){
    
    // printf("\n PARENT FOR WHICH CHILDREN LIST CREATED : \n ");
    // printf("%s \n", NonTerminalMapTree[parent->type.nonterminal]);
    parent->rule_no = grm_rule->rule_no;

    Type_Node_list* symbols = grm_rule->symbols;
	Type_Sym_Node* temp = symbols->head;

    Children* ch = malloc(sizeof(Children));
    // ch->head = parent->child->head;
    ch->head = NULL;
    ch->no_siblings =0;

    TreeNode* prev; // traverses children 
    //i = ch->head;

    // all sumbols in grm_rule have to be pushed 
    for(int k = 0; k < symbols->length; k++){
        // printf("Inside for loop of make child  \n");
        TreeNode * to_be_added;
        if(temp->term_or_nonterm == 0 ){
        	if(temp->type.terminal==EPSILON)
        		return ch;
            Type_Node type;
            type = temp->type;
            to_be_added = initialize_TreeNode(parent, parent->rule_no,0, type);
        }
        else{
            
            Type_Node type;
            type = temp->type;
            to_be_added = initialize_TreeNode(parent, parent->rule_no,1, type);
            // printf("CHILD : %s \n", NonTerminalMapTree[to_be_added->type.nonterminal]);
        }

        if( ch->head == NULL){ // if first child 
        
           ch->head=to_be_added;
           prev=ch->head;

        }
        else{
           prev->next=to_be_added;
           prev=prev->next;
        }


        temp = temp->next;
    }

    // parent->child = ch;
    // term or non term 
    //printf("Children List Created \n");
    return ch;
}

void deallocateChildren(Children * children){
    TreeNode * curr, * prev;
    // prev = children->head;
    curr = children->head;
    while(curr != NULL){
        prev = curr;
        curr = curr->next;
        free(prev);
    }
    
}




void printTreeNode(TreeNode * tn){
    printf("\n $$ TREENODE  \n");
    // Symbol name from terminal map
    int term_nonterm = tn->term_nonterm;
    term_nonterm == 0 ? printf("1.  Symbol Name : %s \n", TerminalMapTree[tn->tok.type]) : printf("1.  Symbol Name : %s \n", NonTerminalMapTree[tn->tok.type]);
    term_nonterm == 0 ? printf("2.  TreeNode : Terminal \n") : printf("2.  TreeNode : Non Terminal \n");
    // int leaf;
    // if (tn->child == NULL){
    //     printf("Treenode has no child, check program :( \n ");
    //     return;
    // }
    // if(tn->child->head == NULL){
    //     leaf =1;
    // }
    // else leaf =0;
    if(!term_nonterm){
        union typeExp typeexp = tn->te;
        printf("3.  Type Exp of Leaf : \n");
        printf("4.  Line Number : \n");
        printf("5.  Grammar Rule : None \n");
    }
    else{
        printf("3.  Type Exp : None \n");
        printf("4.  Line Number : None \n ");
        printf("5.  Grammar Rule is: %d \n", tn->rule_no);
    }
    // printf("Depth of node : %d \n", tn->height);
    
    
}

/*
 Symbol name
 Whether terminal or non terminal
 Type expression stored in the corresponding node (if non-leaf)
 Name of lexeme (if leaf node)
 Line number (if leaf node)
 Grammar grm_rule applied for expansion of this node while parsing (if non leaf)
 Depth of node (root of the parse tree at depth 0)
*/
void printParseTree(ParseTree *t){

}

