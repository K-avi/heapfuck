#include "stack.h"
#include "heap.h"
#include "ast.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

S_STACK * init_stack(unsigned size){
    /*
    */
    if(size==0) return NULL;
    
    S_STACK * ret= (S_STACK*) malloc(sizeof(S_STACK));
   
    ret->stack= (instruction**) calloc( size, sizeof(instruction*) );
    ret->size=size;

    return ret;
}//tested ;ok


void print_stack( S_STACK* stack){
    /*
    */

    //no clue why i declared i as uint32_t but it's really funny 
    //so I'll leave it there
    for( uint32_t i=0; i<stack->size; i++){
        if(stack->stack[i]){
            printf("%u : %c\t", i, token_to_char(stack->stack[i]->tok) );
        }else{
            printf("%u : (null\t)", i);
        }
    }
    printf("\n");
}//not tested but should be ok ?

void free_stack( S_STACK* stack){
    /*
    */
    if(!stack) return;
    if(stack->stack) free(stack->stack); 
    free(stack);
}//testes ; ok
