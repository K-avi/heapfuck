#include "ast.h"
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>


void free_instruct ( instruction * instruct){
    /*
    */
    if(!instruct) return;

    instruction * tmp1= instruct, * tmp2=instruct;
    while(tmp1){
        tmp2=tmp2->next; 
        free(tmp1);

        tmp1=tmp2;
    }
}//tested ;works


int bison_token_to_internal( int token){
    /*
    converts flex/bison generated token to internal rep; 
    
    returns -1 on invalid tokens

    */
 
    switch (token){

        case LCHILD : return INT_LCHILD; break;
        case RCHILD : return INT_RCHILD; break;
        case PARENT: return INT_PARENT; break;

        case PRINT: return INT_PRINT; break;
        case READ: return INT_READ; break;

        case PLUS: return INT_PLUS; break;
        case MINUS: return INT_MINUS; break;
        
        case LBRACKET: return INT_LBRACKET; break;
        case RBRACKET: return INT_RBRACKET; break;

        case HEAP_DUMP : return INT_HEAPD; break;
        case POP : return INT_POP; break; 

        case CREATE : return INT_CREATE ; break;
        case DPRINT : return INT_DPRINT; break;
      
        default: return -1; 
        
    }

    return -1;
}// tested; works




char token_to_char(int token){
    
    switch (token) {
    case INT_LCHILD : return '<'; break;
    case INT_RCHILD: return '>'; break;
    case INT_PARENT : return '^'; break;
 
    case INT_PLUS : return '+'; break;
    case INT_MINUS : return '-'; break;
   
    case INT_LBRACKET : return '['; break;
    case INT_RBRACKET : return ']'; break;
   
    case INT_READ: return ','; break;
    case INT_PRINT: return '.'; break;

    case INT_HEAPD : return '#'; break;

    case INT_POP : return '!'; break;

    case INT_CREATE : return '%'; break;

    case INT_DPRINT : return ':'; break;
 
    default : return 'x'; break;
    }

    return 'x';
}//not tested but should be ok

instruction * mkinstruction( token tok){
    /*
    */

  //  printf("reached mkinstr %d\n", tok);
    instruction * ret = (instruction*) malloc(sizeof(instruction));

    ret->tok= bison_token_to_internal(tok);
    ret->next=NULL;
    ret->prev=NULL; 

    ret->other=NULL;

    return ret;
}//changed;  tested ; ok

program* initProg(){
    /*
    called once at start of exec
    */

  //  printf("initProg check\n");
    program * ret= (program*) malloc(sizeof(program));

    ret->head=NULL; 
    ret->tail=NULL;

    return ret;
}//tested ok

void insertHead( program * prog,  instruction * newH){
    /*
    not used atm; might be relevant later?
    */
    if(! (newH && prog) ) return;
    newH->next= prog->head;
    newH->prev=NULL;

    if((prog->head)){
       prog->head->prev=newH;
    }else{
        
    }
    prog->head=newH;
}//tested ; ok 

void insertTail( program * prog, instruction * newT){
    /*
    not used atm ; might be relevant later?
    */
    if(! (newT && prog) ) return;
    newT->next=NULL;

    if(!(prog->head)){
        newT->prev=NULL;
        prog->head=newT;
    }else{
        prog->tail->next=newT;
    }
    prog->tail=newT;

}//tested; ok

void free_prog (program * prog){
    /*
    if error handler is set, will free the potential instruction * from a defun type statement.
    */

  //  printf("free_prog check\n");
    if(!prog) return;

    instruction * tmp1= prog->head, * tmp2=prog->head;

    while(tmp1){
        tmp2=tmp2->next; 

        free(tmp1);

        tmp1=tmp2;
    }

    free(prog);
}//tested; works


void printprgm( program* prgm){
    /*
    not used in prog but usefull when debugging
    */
    if(!prgm){

        printf("empty prog\n");
        return ;
    }
    instruction * cur=prgm->head; 

    while(cur){
        printf("%c", token_to_char(cur->tok));
        cur=cur->next;
    }
    printf("\n");
}//not tested


void mergeInstruction( instruction * list1, instruction * list2){
    /*
    adds list2 to the end of list1 
    used in parser
    */
    if (! (list1 && list2)) return;

    instruction * tmp=list1; 

    while(tmp->next){
        tmp=tmp->next;
    }   

    tmp->next=list2; 
    list2->prev= tmp;
}//tested; works


void progMerge (program * prog, instruction * list){
    /*
    used in parser ; works ; appends list to the tail of prog and sets it's new tail 
    to the end of list
    different cases : prog is empty or 
    prog has one or more elements 
    */
    if(! (prog && list)) return;

    
    if (! (prog->tail && prog->head)){ //case : progempty
        prog->head= list;

        instruction * tmp= list; 

        while(tmp->next){
            tmp=tmp->next; 
        }
        prog->tail= tmp;
    }else{ //at least one element in prog; tail has to be changed to become last element of list 

        instruction * oldTail= prog->tail;

        oldTail->next= list; 
        list->prev= oldTail;

        instruction * tmp= list; 

        while(tmp->next){
            tmp=tmp->next;
        }

        prog->tail=tmp;
    }
    
}//tested; seems ok