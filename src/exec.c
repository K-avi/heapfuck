#include "exec.h"
#include "ast.h"
#include "globals.h"
#include "heap.h"
#include "stack.h"

#include <sys/types.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

int exec(program * progr , S_BIN_HEAP * environment , S_STACK * stack, unsigned char * printcheck){


  // printf("in exec \n");
 // printf("p %p e %p s %p\n", progr, environment,  stack);
  if(! (progr && environment && stack )) {
  
    return -1;
  }
  instruction* curr = progr->head;
  
  unsigned short stack_ptr = 0;
  
 // int length= environment->size;
 
 
  
  char safe_getchar[256]; //used in read function to pass stuff safely
 
  while (curr) {
    
    unsigned short instruction = curr->tok;
    int idx= environment->currindex; 
    printf("curr %p curr n %p curr o %p\n",(void*) curr,(void*) curr->next ,(void*) curr->other);
    switch (instruction) {
        
        case INT_LCHILD : 
        printf("reached lchild %d %d \n", OP_LCHILD(environment->currindex) , environment->currindex);
            if(  OP_LCHILD(environment->currindex)<=(environment->heap[0])) 
              idx= OP_LCHILD(environment->currindex); 

        break;
        
        case INT_RCHILD :
            if( OP_RCHILD(environment->currindex)<=(environment->heap[0])) 
              idx= OP_RCHILD(environment->currindex); 
            
        break;

        case INT_PARENT : 
            if( OP_PARENT(environment->currindex)>=1) 
             idx= OP_PARENT(environment->currindex); 
            
        break;

        case INT_PLUS: 
            if(environment->heap[0])
            increase_key(environment, idx, 1);
        break;

        case INT_MINUS: 
            if(environment->heap[0])
            decrease_key(environment, idx, 1);
        break; 

        case INT_PRINT: 
            printf("%c", environment->heap[idx]); 
            if(printcheck){*printcheck=1;}
        break;

        case INT_READ : 
            printf("reached read\n");
            fflush(stdin);
            if(fgets(safe_getchar, 255, stdin)){
              
              insert_key(environment,  safe_getchar[0]);
              
              fflush(stdin);

              memset(safe_getchar, 0, 256*sizeof(char));
            }
        break;

        case INT_LBRACKET : 
        
            if (environment->heap[idx] == 0) {
                curr = curr->other;
              } else {
                if (stack_ptr >= STACK_SIZE) {
                    return -1; //stack overflow
                }
                stack->stack[stack_ptr++] = curr;
              }
        break;

        case INT_RBRACKET : 
            curr = stack->stack[--stack_ptr];
        break;

        case INT_HEAPD : 
            print_heap(environment);
            if(printcheck){*printcheck=1;};
        break;

        case INT_POP: 
            pop_index(environment, idx);
        break;

        case INT_CREATE :
            insert_key(environment, default_keyval);
        break;

        default: return 0; break;
    }
    curr=curr->next;
    environment->currindex=idx;
  } 
  
  
  return 1;

}//testing; has problems w loop