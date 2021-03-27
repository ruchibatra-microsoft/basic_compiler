// =======================================================================================================
// PPL ASSIGNMENT 1 2020
// GROUP NUMBER 47
// ANUSHKA JAIN 2017B1A70975P
// KUMAR SAURABH 2017B3A70626P
// MANSI MITTAL 2017B1A70991P
// RUCHI BATRA 2017B3A70629P
// =======================================================================================================


#include "stack.h"

char* TerminalMapP[] = {
	"PROGRAM", "SZ", "OP", "CL", "COP", "CCL", "SQOP", "SQCL", "DOTS", "EPSILON", "COLON", "SEMICOLON", "ID", "IDB", "NUM", "INT", "BOOLEAN", "REAL", "ARRAY", "JAGGED", "DEC", "LIST", "OF", "VARIABLES", "R", "VALUES", "EQUALS", "PLUS", "MINUS", "MUL", "DIV", "AND", "OR","DOLLAR"
};

char* NonTerminalMapP[] = {
    "program", "stmts", "stmt", "more_stmts", "decl", "declaration", "assign", "var_list", "type", "primitive", "array", "rectangular", "jagged", "arr_dims", "arr_dim", "range", "low", "high", "rows_dec_R1", "rows_dec_jR1", "op_dim", "rowjj", "rowj", "expression", "expression_arith", "expression_bool", "term", "term_bool", "factor", "factor_bool", "ind_list", "more_ind_list", "remaining_var", "more_rowj", "more_rowjj", "array_op", "op_no_op_or", "op_no_op_and", "op_plus_minus", "op_mul_div", "more_arr_dims"
};

// Initialize
MainStack* initialize_main_stack(){
    MainStack * ms = (MainStack *)malloc(sizeof(MainStack));
    MainStackList * ls = (MainStackList *)malloc(sizeof(MainStackList));
    ls->head = NULL;
    ms->ms_list = ls;
    ms->capacity = 500;
    ms->height = 0;
    return ms;
}

AuxStack* initilaize_aux_stack(){
    AuxStack * as = (AuxStack *)malloc(sizeof(AuxStack));
    AuxStackList * ls = (AuxStackList *)malloc(sizeof(AuxStackList));
    ls->head = NULL;
    as->as_list = ls;
    as->size = 0;
    return as;
}

// Empty stack 
bool stackisEmpty(MainStack * ms)
{
    if(ms->ms_list->head == NULL){
        return true;
    }
    else{
        return false;}
}

bool auxstackisEmpty(AuxStack * as)
{
    if(as->as_list->head == NULL){
        return true;
    }
    else return false;
}


// create 
MainStackNode* create_main_stack_node(TreeNode * tree_node){
    // printf("Inside create main stack node ");
    MainStackNode * main_stack_node = (MainStackNode *)malloc(sizeof(MainStackNode));
    main_stack_node->stack_tree_node = tree_node;
    main_stack_node->next_node = NULL;
    // printf("Exited main stack node \n ");
    return main_stack_node;
}

AuxStackNode* create_aux_stack_node(TreeNode * tree_node){
    AuxStackNode * aux_stack_node = (AuxStackNode *)malloc(sizeof(AuxStackNode));
    aux_stack_node->stack_tree_node_a = tree_node;
    aux_stack_node->next_node_a = NULL;
    return aux_stack_node;
}
// push 
void push_ms(MainStack* ms, TreeNode * treenode){
    // printf("Inside main stack push \n ");
    
    MainStackNode* ms_node = create_main_stack_node(treenode);
    if(ms->ms_list !=NULL){
    ms_node->next_node = ms->ms_list->head; // accessing NUll pointer
    }
    ms->ms_list->head = ms_node;
    ms->height++;
}

void push_as(AuxStack * as, TreeNode * treenode){
    // printf("Inside auxilliary stack push \n");
    AuxStackNode* as_node = create_aux_stack_node(treenode);
    as_node->next_node_a = as->as_list->head;
    as->as_list->head = as_node;
    as->size++;
    // printf("AS pushed \n");
}

// pop, modify, check if empty

TreeNode* pop_ms(MainStack * ms){
    if(ms->height ==0){
        printf("ERROR: Sorry, main stack is empty \n");
        return NULL;
    }
    else{
        TreeNode* tem = ms->ms_list->head->stack_tree_node;
        ms->ms_list->head = ms->ms_list->head->next_node;
        ms->height--;
        return tem;
    }
}
TreeNode* pop_as(AuxStack * as){
    if(as->size ==0){
        printf("ERROR: Sorry, aux stack is empty \n");
        return NULL;
    }
    else{
        TreeNode* tem = as->as_list->head->stack_tree_node_a;
        as->as_list->head = as->as_list->head->next_node_a;
        as->size--;
        return tem;
    }
}

void pop_all_as(AuxStack * as){
    TreeNode * temp;
    for(int i=0; i< as->size; i++){
        temp = pop_as(as);
    }
}


// return top of main stack
TreeNode * topofMainStack(MainStack * ms){
    // printf("HERE \n");
    TreeNode * tn = ms->ms_list->head->stack_tree_node; // points to a treenode which is the top of the stack 
    // printf("ALL GOOD \n");
    return tn;
}

void push_rule_reverse(GrmRule * grm_rule, AuxStack * as, MainStack *ms){

    Type_Node_list* symbols = grm_rule->symbols;
	Type_Sym_Node* temp2 = symbols->head;

	for(int k=0; k<symbols->length ;k++){
	
        TreeNode * tn;
		if(temp2->term_or_nonterm==0 && temp2->type.terminal!=EPSILON) {
		// if terminal 
            tn = initialize_TreeNode(NULL, grm_rule->rule_no, 0, temp2->type);
            
			// initialise tree node with term 
            push_as(as,tn);
            } // push in aux stack
		else if(temp2->term_or_nonterm==1){
            tn = initialize_TreeNode(NULL, grm_rule->rule_no, 1, temp2->type);
            // initialise tree non with non term 
            push_as(as,tn);
           }
            else
            	printf("Epsilon is thereeeee");
            // push into aux stack
			
	temp2 = temp2->next; // move ahead temp2 points to all symbol nodes in a grm_rule 
	}

    while(!auxstackisEmpty(as)){
        TreeNode * tnm = pop_as(as);
        // if(tnm->term_nonterm==0)
        // 	printf("\n%s",TerminalMapP[tnm->type.terminal]);
        // else
        // 	printf("\n%s",NonTerminalMapP[tnm->type.nonterminal]);
        push_ms(ms,tnm);
    }
    
}
