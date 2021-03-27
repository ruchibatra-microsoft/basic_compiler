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
#include "parse.h"
int main(int argc, char *argv[]){

    int option;

	TreeNode * root = NULL;

	while(1)
	{

		printf("* \n Please Enter Option \n Input the option number corresponding to the desired input: \n\n");

		printf("0: Exit\n");
		printf("1: Create parse tree \n");
		printf("2: Traverse the parse tree to construct typeExpressionTable \n");
		printf("3: Print parse tree \n");
		printf("4: Print typeExpressionTable \n");
		scanf("%d", &option);

        // Add functions corresponding to each option
		if(option ==1 ){
			printf("=================Beginning process to create parse Tree=========================\n");
			char *filename;
			printf("Enter file path - ");
			scanf("%s",filename);
			root = createParseTree(filename);
			continue;
		}
		else if(option == 2){
			printf("================Traversing Parse Tree================================\n");
		}
		else if(option == 3){
			printf("====================Printing the parse tree===========================\n");
			if(root != NULL){
				preordertraversal(root);}
			else{
				printf("Create Parse Tree first, try option 1 \n");
			}
		}
		else if(option == 4){
			printf("====================Printing typeExpression Table=========================\n");
		}
		else if(option == 0){
			break;
			printf("=============================Exiting the program=========================================\n");
			printf("=============================Thank you! Bye!!=========================================\n");
		}
		else{
			printf("=============================Please enter only 0 1 2 3 or 4========================================\n");
		}
    }
    // while(option !=0);

    return 0;
}
