all: 
	gcc -o compiler driver.c tok.c g.c stack.c tree.c parse.c -lm
