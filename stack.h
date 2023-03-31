#ifndef STACK_H 
#define STACK_H 

#include "ast.h"
typedef struct stack{
    instruction ** stack; 
    unsigned size; 
    
}S_STACK;


extern S_STACK * init_stack(unsigned size);
extern void print_stack( S_STACK* stack);
extern void free_stack( S_STACK* stack);

#define STACK_SIZE 256

#endif