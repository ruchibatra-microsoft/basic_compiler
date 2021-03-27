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
#include <string.h>
#include <ctype.h>
#include <math.h>

#include"g.h"



//Mappings of ENUM to String for all tokens in same order as enum def 
char* TerminalMap[] = {
	"PROGRAM", "SZ", "OP", "CL", "COP", "CCL", "SQOP", "SQCL", "DOTS", "EPSILON", "COLON", "SEMICOLON", "ID", "IDB", "NUM", "INT", "BOOLEAN", "REAL", "ARRAY", "JAGGED", "DEC", "LIST", "OF", "VARIABLES", "R", "VALUES", "EQUALS", "PLUS", "MINUS", "MUL", "DIV", "AND", "OR","DOLLAR"
};

char* NonTerminalMap[] = {
    "program", "stmts", "stmt", "more_stmts", "decl", "declaration", "assign", "var_list", "type", "primitive", "array", "rectangular", "jagged", "arr_dims", "arr_dim", "range", "low", "high", "rows_dec_R1", "rows_dec_jR1", "op_dim", "rowjj", "rowj", "expression", "expression_arith", "expression_bool", "term", "term_bool", "factor", "factor_bool", "ind_list", "more_ind_list", "remaining_var", "more_rowj", "more_rowjj", "array_op", "op_no_op_or", "op_no_op_and", "op_plus_minus", "op_mul_div", "more_arr_dims"
};


//Loads grammar from text file 
// Grammar in grammar.txt 
Grammar* readGrammar(char* grammar_text_file){

	FILE* grammarfile = fopen(grammar_text_file, "r");
    // printf("Loaded from grammar.txt \n");
	if(grammarfile==NULL){
		printf("ERROR: Cannot open Grammar file \n");
		return NULL;
	}

	int next_rule_no = 1;
	int eof = 0;

	//Initialising grammar data structure 
	Grammar* grm = init_grm();
    // printf("\n Init");
	
	char c;

	while(!eof){

		//Getting LHS of a grm_rule
		while((c = fgetc(grammarfile))!='<'){
			//If no new grm_rule is available
			if(c==EOF){
				return grm;
			}
		}
		
        // printf("\n Loading grm_rule %d", i);
		char* lhs_grm_rule = (char*)malloc(sizeof(char)*MX_NODE_SIZE);
		int i = 0;
		c = fgetc(grammarfile);
		while(c!='>'){
			lhs_grm_rule[i] = c;
			c = fgetc(grammarfile);
			i++;
		}
		lhs_grm_rule[i] = '\0';


		//Load LHS of the grm_rule 
		NonTerminal non_term  =  assign_sym(lhs_grm_rule,1); // assign_sym maps enum to its string using NonTerminalMap
		//Find corresponding RHS for non terminal 
		GrmRule* new_rule = init_rule(&next_rule_no);
		Type_Node_list* list = init_type_node_list();
		Type_Sym_Node* curr_node = list->head;

		while(!eof){

			c = fgetc(grammarfile);
			
			// Ignore these characters 
			while(1){
			if(c!=' '&& c!= '=' &&  c != '\t' && c!= '>'){
				break;	
			}
			else
			{
				c = fgetc(grammarfile);
			}
			
			}

			// New line, new rule
			if(c == '\n')
				break;

			//Break if EOF
			else if(c == EOF){
				eof = 1;
				break;
			}
			else if (isalpha(c) && !(c>='a' && c<='z')){
			
				// Reading terminals 
				char* terms = (char*)malloc(sizeof(char)*MX_NODE_SIZE);
				int i = 0;
				terms[i] = c;
				i++;
				c = fgetc(grammarfile);
				while(isalpha(c) && !(c>='a' && c<='z')){
					terms[i] = c;
					i++;
					c = fgetc(grammarfile);
				}
				terms[i] = '\0';
								
				Type_Sym_Node* sym_node = create_type_node(assign_sym(terms,0), 0);

				//Adding type_node to the list
				curr_node = add_node_to_list(list, sym_node, curr_node);

				if(c == EOF){
					eof = 1;
					break;
				}
				else if(c == '\n'){
					break;
				}
				
			}

			else if(c=='<'){
				
				char* lhs_grm_rule = (char*)malloc(sizeof(char)*MX_NODE_SIZE);
				int i = 0;
				c = fgetc(grammarfile);
				while(c!='>'){
					lhs_grm_rule[i++] = c;
					c = fgetc(grammarfile);
				}
				lhs_grm_rule[i] = '\0';
				
				Type_Sym_Node* sym_node = create_type_node(assign_sym(lhs_grm_rule,1), 1);

				//Adding type node to the list
				curr_node = add_node_to_list(list, sym_node, curr_node);
				
			}
		}
		
		//Assigning the list to the new grm_rule
		new_rule->symbols = list;
		
		//Add new grm_rule to the grammar
		add_rule_to_grm(grm,non_term,new_rule);		
	}
	return grm;
} 


Grammar* init_grm(){
	Grammar* grm = (Grammar*)malloc(sizeof(struct grammar));
	grm -> num_rules = 0;

	//Total non-terminals will be equal to total number of rules
	grm -> rules = (GrmRules**)malloc(sizeof(GrmRules*)*NUM_NON_TERMS);
	int i =0; 
	while(i<NUM_NON_TERMS){
		grm->rules[i] = (GrmRules*)malloc(sizeof(struct rules));
		grm->rules[i]->head = NULL;
		grm->rules[i]->length = 0;		
		i++;
	}

	return grm;
}

// Add rule to grammar 
void add_rule_to_grm(Grammar* grm, NonTerminal non_term, GrmRule* new_rule){

	new_rule->next = grm->rules[non_term]->head;
	grm->rules[non_term]->head = new_rule;

	//Rule added to grammar, increase rule len 
	grm->rules[non_term]->length++;

	grm->num_rules++;
}

// Initialise the grammar 
GrmRule* init_rule(int* next_rule_no){
	GrmRule* new_rule = (GrmRule*)malloc(sizeof(GrmRule));
	new_rule->symbols = NULL;
	new_rule->next = NULL;
	
	new_rule->rule_no = *next_rule_no; 
	*next_rule_no = *next_rule_no+1;

	return new_rule;
}


Type_Node_list* init_type_node_list(){
	Type_Node_list* list = (Type_Node_list*)malloc(sizeof(Type_Node_list));
	list->head = NULL;
	list->length = 0;

	return list;
}

Type_Sym_Node* add_node_to_list(Type_Node_list* list, Type_Sym_Node* sym_node, Type_Sym_Node* curr_node){
	
	//If initially the list is empty
	if(!curr_node){
		sym_node->next = list->head;
		list->head = sym_node;
		curr_node = list->head;
	}
	else{
		curr_node->next = sym_node;
		curr_node = curr_node->next;
	}

	list->length++;

	return curr_node;
}

Type_Sym_Node* create_type_node(int vale, int term_or_nonterm){
	Type_Sym_Node* sym_node = (Type_Sym_Node*)malloc(sizeof(Type_Sym_Node));
	sym_node->next=NULL;
	Type_Node type;
	if(term_or_nonterm){
		type.nonterminal = (NonTerminal)vale;
	}
	else{
		type.terminal = (Terminal)vale;
	}
	sym_node->type = type;
	sym_node->term_or_nonterm = term_or_nonterm;

	return sym_node;

}

int assign_sym(char* str, int term_or_nonterm){
	
	//For Terminals
	if(!term_or_nonterm){
		int i=0;
		while(i<TOKEN_TYPES){
			if(strcmp(str,TerminalMap[i])==0)
				return i;
			i++;
		}
	}

	//For Non terminals
	else{
		int i =0;
		while(i<NUM_NON_TERMS){
			if(strcmp(str,NonTerminalMap[i])==0)
				return i;
			i++;
		}
	}
}


void print_grammar(Grammar* grm){
	printf("\n============================Printing Grammar===========================\n\n");

	int i=0;
	while(i<NUM_NON_TERMS){		
		printf("%d.  <%s> ---> ",(i+1), NonTerminalMap[i]);

		GrmRules* rules = grm->rules[i];
		GrmRule* temp_rule = rules->head;
		int j=0;
		while(j<rules->length){
			if(j!=0)
				printf("| ");

			Type_Node_list* nodes = temp_rule->symbols;
			Type_Sym_Node* temp_node = nodes->head;

			for(int k=0;k<nodes->length;k++){
				if(!temp_node->term_or_nonterm)
					printf("<%s> ", NonTerminalMap[temp_node->type.nonterminal]);
				else
					printf("%s ", TerminalMap[temp_node->type.terminal]);

				temp_node = temp_node->next;
			}
			temp_rule = temp_rule->next;
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n========================End of Grammar====================\n");
	
}
