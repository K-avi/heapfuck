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
  /*
  executes progr given the context env and stack.

  printcheck is only usefull for cmdline_interp and not very important. 

  returns -1/-2 on error; 0 on succes.
  */
  if(! (progr && environment && stack )) {
    return -1;
  }
  instruction* curr = progr->head;
  
  unsigned short stack_ptr = 0;
 
  
  char safe_getchar[256]; //used in read function to pass stuff safely
 
  while (curr) {
    
    unsigned short instruction = curr->tok;
    int idx= environment->currindex; 
    
    switch (instruction) {
        
        case INT_LCHILD : 
            if(!idx) break;
            if(  OP_LCHILD(environment->currindex)<=(environment->heap[0])) 
              idx= OP_LCHILD(environment->currindex); 

        break;
        
        case INT_RCHILD :
            if(!idx) break;
            if( OP_RCHILD(environment->currindex)<=(environment->heap[0])) 
              idx= OP_RCHILD(environment->currindex); 
            
        break;

        case INT_PARENT : 
            if(!idx) break;
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
            if(!idx) break;
            printf("%c", environment->heap[idx]); 
            if(printcheck){*printcheck=1;}
        break;

        case INT_READ : 
            if(!idx) idx=1;
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
        continue;

        case INT_HEAPD : 
            print_heap(environment);
            if(printcheck){*printcheck=1;};
        break;

        case INT_POP: 
            if(environment->heap[0]==0){
                idx=0;
                break;
            }
            pop_index(environment, idx);
	    if(idx>environment->heap[0]) idx--;
        break;

        case INT_CREATE :
            if(!idx) idx=1;
            insert_key(environment, default_keyval);
        break;

        case INT_DPRINT: 
            printf("%d ", environment->heap[idx]);
            if(printcheck) *printcheck=1;
        break;

        default: return -2; break;
    }
    curr=curr->next;
    environment->currindex=idx;
  } 
  
  
  return 0;

}//testing; seems ok
//I strongly suspect that there are edge cases where the heap structure
//gets broken but I can't find em 
