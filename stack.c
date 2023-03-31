#include "stack.h"
#include "cells.h"
#include "ast.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

S_STACK * init_stack(unsigned size){
    if(size==0) return NULL;
    
    S_STACK * ret= (S_STACK*) malloc(sizeof(S_STACK));
   
    ret->stack= (instruction**) calloc( size, sizeof(instruction*) );
    ret->size=size;

    return ret;
}


void print_stack( S_STACK* stack){
    for( uint32_t i=0; i<stack->size; i++){
        if(stack->stack[i]){
            printf("%u : %c%c\t", i, token_to_char(stack->stack[i]->symbol), token_to_char(stack->stack[i]->symbol>>4) );
        }else{
            printf("%u : (null\t)", i);
        }
    }
    printf("\n");
}

void free_stack( S_STACK* stack){
    if(!stack) return;
    if(stack->stack) free(stack->stack); 
    free(stack);
}

