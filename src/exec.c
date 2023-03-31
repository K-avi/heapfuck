#include "exec.h"
#include "ast.h"
#include "heap.h"
#include "stack.h"

#include <sys/types.h>
#include <unistd.h>

int exec(program * progr , S_BIN_HEAP * environment , S_STACK * stack){


  if(! (progr && environment && stack )) {
    //("%p %p %p %p\n", progr, environment, stack, table);
    return -1;
  }
  instruction* curr = progr->head;
  
  unsigned short stack_ptr = 0;
  
 // int length= environment->size;
  int idx= environment->curindex; 

  int exec_direction= 1 ; //used when changing sense of execution from "right to left" to "left to right"
//modified when calling the "?>" and "?<" symbols.
 
  
  char safe_getchar[256]; //used in read function to pass stuff safely
  
  unsigned int  size= environment->heap_size;

  while (curr) {
    
    unsigned short instruction = curr->tok;

    switch (instruction) {
        
        case INT_LCHILD : break;
        
        case INT_RCHILD : break;

        case INT_PARENT : break;

        case INT_PLUS: break;

        case INT_MINUS: break; 

        case INT_PRINT: break;

        case INT_READ : break;

        case INT_LBRACKET : break;

        case INT_RBRACKET :  break;

        default: return 0; break;
    }
    curr=curr->next;
  } 
  
  return 1;

}