// =======================================================================================================
// PPL ASSIGNMENT 1 2020
// GROUP NUMBER 47
// ANUSHKA JAIN 2017B1A70975P
// KUMAR SAURABH 2017B3A70626P
// MANSI MITTAL 2017B1A70991P
// RUCHI BATRA 2017B3A70629P
// =======================================================================================================



// Backtracking algo 
// Create parse tree 
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
// #include "tokenizer.h"
// #include "tree.h"
// #include "g.h"
// #include "stack.h"
#include "parse.h"

char* TerminalMapPar[] = {
	"PROGRAM", "SZ", "OP", "CL", "COP", "CCL", "SQOP", "SQCL", "DOTS", "EPSILON", "COLON", "SEMICOLON", "ID", "IDB", "NUM", "INT", "BOOLEAN", "REAL", "ARRAY", "JAGGED", "DEC", "LIST", "OF", "VARIABLES", "R", "VALUES", "EQUALS", "PLUS", "MINUS", "MUL", "DIV", "AND", "OR","DOLLAR"
};

char* NonTerminalMapPar[] = {
    "program", "stmts", "stmt", "more_stmts", "decl", "declaration", "assign", "var_list", "type", "primitive", "array", "rectangular", "jagged", "arr_dims", "arr_dim", "range", "low", "high", "rows_dec_R1", "rows_dec_jR1", "op_dim", "rowjj", "rowj", "expression", "expression_arith", "expression_bool", "term", "term_bool", "factor", "factor_bool", "ind_list", "more_ind_list", "remaining_var", "more_rowj", "more_rowjj", "array_op", "op_no_op_or", "op_no_op_and", "op_plus_minus", "op_mul_div", "more_arr_dims"
};


void push_rule_reverse_ruchi(GrmRule * grm_rule, AuxStack * as, MainStack * ms, Children * children )
    { 
        // printf("Inside push grm_rule reverse \n ");

        // printf("For aux stack \n");
        TreeNode*temp=children->head;
        if(temp==NULL)
        	return;
        // printf("No of siblings %d", children->no_siblings);
        while(!auxstackisEmpty(as))
        {
            TreeNode* temp1=pop_as(as);
        }
        while(temp!=NULL)
        {
            // push();
            // printf("Symbol is %s", temp->);
            push_as(as,temp);
            temp=temp->next;
        }
        // printf("For main stack \n");
        while(!auxstackisEmpty(as))
        {
            TreeNode * temp2=pop_as(as);
            // if(temp2->term_nonterm == 0){
            //     printf("%s \n", TerminalMapPar[temp2->type.terminal]);
            // }
            // else{
            //     printf("%s \n", NonTerminalMapPar[temp2->type.nonterminal]);
            // }
            push_ms(ms,temp2);
        }
        
    }	    


bool match(Token_s * lookahead , TreeNode * tos)
{

    if( lookahead->type==tos->type.terminal ) // only when terminal 
    {
        tos->tok = *lookahead;        
        tos->tok.lexeme=lookahead->lexeme;
        tos->tok.line_number=lookahead->line_number;
        strcpy(tos->tok.token_name, lookahead->token_name);
        tos->tok.type=lookahead->type;

        return true;
    }
    else {
    return false;}
}


TreeNode * createParseTree(char * testcaseaddress)
{
    char* grammar_file = "grammar.txt";
	Grammar* grm = readGrammar(grammar_file);
	print_grammar( grm);
    tokenstream * s = tokenizeSourceCode(testcaseaddress);
    
    Token_s * token_stream_pointer = s->head; // points to current location in the token stream 
    
    Type_Node start_type;
    start_type.terminal = DOLLAR;

    Type_Node program_start;
    program_start.nonterminal= program;

    TreeNode* start = initialize_TreeNode(NULL,1, 0, start_type); // Pushed dollar, a terminal
    TreeNode* program = initialize_TreeNode(NULL, 1, 1, program_start); // Push program, a non terminal 
    program->height = 0;
    //stacks init 
    MainStack* MS = initialize_main_stack();
    AuxStack* AS = initilaize_aux_stack();
    
    // Let the pushing and popping begin 
    push_ms(MS, start);
    push_ms(MS,program);

    // printf("I am here");

    parsing(MS, AS, grm, token_stream_pointer);
    // if(program->child==NULL)
    // 	printf("It is NULL");
    // preordertraversal(program);
    return program;
}

bool parsing(MainStack * ms, AuxStack * as, Grammar * grm, Token_s * lookahead)
{
    while(!stackisEmpty(ms))
    {
    	
    	TreeNode * tos = topofMainStack(ms);
    	// if(tos->term_nonterm==0)
        // 	printf("\n Top of the stack is %s",TerminalMapPar[tos->type.terminal]);
        // else
        // 	printf("\nTop of the stack is %s",NonTerminalMapPar[tos->type.nonterminal]);
        TreeNode * temp;
        

        if(tos->term_nonterm == 0 )
        {
        if(tos->type.terminal!=DOLLAR)
		{
		    if(match(lookahead,tos))
		    {
			// printf("\n lookahead %s", lookahead->lexeme);
		        lookahead=lookahead->next;
		        temp = pop_ms(ms);
		        

		    }
		    else
		    {

		        return false;

		    }
		}
		else
		{
			
			printf("DOLLAR FOUND \n");
			if(lookahead==NULL)
			{
				printf("RETURN \n");
				return true;
			}
			else
			{
				printf("ERROR: Check input source code");
                    		return false;
			}
		}

        }


        else
        {
		    // printf("\n Enter parsing");
            int i = tos->type.nonterminal; // will always be a non terminal CHECK &&&&&&&&&&&&&&&&&&&&&&&&&&&&
            GrmRules * rules = grm->rules[i];
            // traverse all rules.
            GrmRule * grm_rule = rules->head;


    	    for(int j = 0; j<rules->length; j++)
            {
		    TreeNode * parent =tos;
		    TreeNode * nothing = pop_ms(ms);
        	TreeNode * popUntil= topofMainStack(ms);
		    Children * children = makeChildList(parent, grm_rule);
		    Token_s* temp_look=lookahead;
		    push_rule_reverse_ruchi(grm_rule, as, ms, children);
		
            bool ruleWorks = parsing(ms, as, grm, temp_look);
            if(!ruleWorks)
            { 
                while(popUntil != topofMainStack(ms)){
                    TreeNode * nothing1 = pop_ms(ms);
                }
                push_ms(ms, parent);
                deallocateChildren(children);
                
            }
            else{
			    parent->child = children;
		        // printf("RULE WORKED \n");
                // printf("    PARENT : %s \n ", NonTerminalMapPar[parent->type.nonterminal]);
                // if(parent->child != NULL){
                //     if(parent->child->head != NULL){
                //     TreeNode * fc = parent->child->head;
                //     fc->term_nonterm == 0? printf("     FC : %s \n ",TerminalMapPar[fc->type.terminal]) : printf("     FC : %s \n ",NonTerminalMapPar[fc->type.nonterminal]);
                //     } }
		    return true;
		}
		//move grm_rule 
		grm_rule = grm_rule->next;

	    }
	    return false;

    	}
    	if(lookahead==NULL)
    	{
    		printf("======================END OF TOKENSTREAM================= \n");
    		return true;
    	}

    //we will reach here when top of the stack is DOLLAR;

}
return true;
}

// preorder(ptreee->root);


void preordertraversal(TreeNode * root)
{
    if(root==NULL)
    return;
    // print the actual node 
    if(root->term_nonterm==0)
    {
        printf("\n TERMINAL");
        printf("\n  1. Symbol name : %s",TerminalMapPar[root->type.terminal]);
        printf("\n  2. Terminal or NonTerminal :  Terminal");
        printf("\n  3. Lexeme : %s", root->tok.lexeme); // problem 
        printf("\n  4. Line No. : %d ", root->tok.line_number);
        printf("\n  5. Depth : %d \n", root->height);
    }
    else
    {
        printf("\n NON TERMINAL");
        printf("\n  1. Symbol name : %s",NonTerminalMapPar[root->type.nonterminal]);
        printf("\n  2. Terminal or NonTerminal :  NonTerminal ");
        printf("\n  3. GrammarRuleNo : %d ",root->rule_no);
        printf("\n  4. Depth : %d \n ",root->height);
        TreeNode*temp = NULL ;
        if(root->child!= NULL){
        temp= root->child->head;}
	    while(temp!=NULL)
	    {
		preordertraversal(temp);
		// printf(" \n In the while");
		temp=temp->next;  
	    }
    }

    // printf("\n Depth of the tree node : %d ", root->height);
    return;


   	
}

void preordertraversal1(TreeNode * root)
{
    if(!root)
    return;
    // print the actual node 
    if(root->term_nonterm==0)
    {
        printf("\n TERMINAL");
        printf("\n  The symbol name : %s",TerminalMapPar[root->type.terminal]);
        printf("\n  Terminal or NonTerminal :  Terminal ");
        printf("\n  %s ", root->tok.lexeme); // problem 
        printf("\n  %d ", root->tok.line_number);
    }
    else
    {
        printf("\n NON TERMINAL");
        printf("\n  The symbol name : %s",NonTerminalMapPar[root->type.nonterminal]);
        printf("\n  Terminal or NonTerminal :  NonTerminal ");
        printf("\n  GrammarRuleNo : %d ",root->rule_no);
    }


   	TreeNode * temp;
    // if root has a child         
    TreeNode * mover;
    // if root has a child   

    if(root->child!=NULL && root->child->head !=NULL){
        mover = root->child->head;
        while(mover!= NULL){
        // travel all its children 
        // printf("Has child \n ");
        // while(root->child)
        preordertraversal(mover);
        mover = mover->next;
        }
    }
    // if(root->child!=NULL){
    // // if(root->child!=NULL && root->child->head !=NULL){
    //     // printf("Has child \n ");
    //     preordertraversal(root->child->head);
    // }
    // has no child then check its siblings 
    else if(root->child == NULL && root->next){
        // printf("Has siblings \n");
        // go to its sibling 
        // printf("Is term or non term ? %d \n", root->next->term_nonterm);
        // root->next->term_nonterm == 1 ? printf("First sibling is : %s \n", NonTerminalMapPar[root->next->type.terminal]) : printf("First sibling is : %s \n", TerminalMapPar[root->next->type.terminal]);
        preordertraversal(root->next);
    }
    // if it has no siblings or children
    else{
        printf("Parse Tree finished gg \n ");
        return;
    }

    // while(temp)
    // {
    //     preordertraversal(temp);
    //     temp=temp->next;  
    // }
}

// int main(){

//     int a = createParseTree();
//     return 0;

// }
