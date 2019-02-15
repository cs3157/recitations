#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    // basic stack
    int stack;
    int *pstack = &stack;

    // basic heap
    int *pheap = malloc(sizeof(int));

    // basic text
    char *ptext = "read only section";

    // char array on stack
    char c1[5] = {'a','b','c','d','\0'};

    // string array on stack
    char *c2[5] = {"a","b","c","d", "\0"};

    // stack array of heap allocated chars
    char *c3[5];
    for(int i=0;i<5;i++){
	char *p = malloc(sizeof(char));
	*p = c1[i];
	c3[i] = p;
    }

    // heap array of string literals
    char **c4 = malloc(5*sizeof(char *));
    c4[0] = "so";
    c4[1] = "where";
    c4[2] = "does";
    c4[3] = "this";
    c4[4] = "point";

	
    // heap array of pointers to chars on the stack
    char a = 'a';
    char b = 'b';
    char c = 'c';
    char d = 'd';
    char n = '\0';
    
    char **c5 = malloc(5*sizeof(char *));
    
    c5[0] = &a;
    c5[1] = &b;
    c5[2] = &c;
    c5[3] = &d;
    c5[4] = &n;

    
    // free the goods
    free(pheap);
    
    for(int i=0;i<5;i++){
	free(c3[i]);
    }

    free(c4);
    free(c5);
}
