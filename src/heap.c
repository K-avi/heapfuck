#include "heap.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

/* heap allocation functions */

S_BIN_HEAP * initHeap(int heapsize){
    /*
    initialises a heap of heapisze size 

    doesn't chekc malloc succes ; for ret  maybe it should tbh
    DOES however check malloc succes for ret->heap cuz 
    ret->heap can be a BEEG boi
    */

    S_BIN_HEAP * ret= (S_BIN_HEAP*) malloc(sizeof(S_BIN_HEAP));

    ret->heap_size=heapsize;
    ret->currindex=1;
    ret->heap= (int*) malloc(heapsize* sizeof(int));

    if(!ret->heap){
        fprintf(stderr, "problem allocating memory for the heap in initHeap()\n");
        free(ret); 
        return NULL;
    }

    memset(ret->heap, INT_MIN, heapsize*sizeof(int));

    ret->heap[0]=0;

    return ret;
}//testes ; ok

void free_heap( S_BIN_HEAP * heap){
    /*
    frees a heap; check for NULL pointer 
    before freing to avoid errors
    */

    if(!heap) return;

    if(heap->heap) free(heap->heap);
    free(heap);
}//testes; ok


void realloc_heap (S_BIN_HEAP * heap){
    /*
    reallocates heap->heap to make it able to contain one more 
    level of nodes

    doesn't initialises heap or heap->heap if they're null
    */
    if(!heap) return;
    if(!heap->heap) return;
    
    heap->heap=realloc(heap->heap, sizeof(int)* _REALLOC_SIZE(heap->heap_size));
    heap->heap_size+= _REALLOC_SIZE(heap->heap_size);

}//not tested  but  seems ok


//heap manipulation function//

void swap( S_BIN_HEAP * heap, int index1, int index2 ){
    /*
    swaps the value contained at index1 and index2 in a heap; 
    doesn't do anything if :
    heap = NULL 
    heap->heap = NULL 
    (index1 or index2) > heap->heapsize
    */
    if(!heap) return;
    if(!heap->heap) return;
    if( (index1 > heap->heap[0]) || (index2 > heap->heap[0])) return;
    if(! (index1 && index2)) return;
    unsigned tmpVal= heap->heap[index1];

    heap->heap[index1]= heap->heap[index2];
    heap->heap[index2]= tmpVal;

  
}//tested; ok
//kinda stupid ; could prolly be a macro
//or pass int * as args.

void min_heapify( S_BIN_HEAP * heap , int i){
    /*
    */

    if(i>heap->heap[0]) return;

    int l = OP_LCHILD(i);
    int r = OP_RCHILD(i);
  //  printf("in min heapify l = %d r=%d i = %d\n", l , r ,i);
    int smallest = i;

    if (l <  heap->heap_size && heap->heap[l] < heap->heap[i])
        smallest = l;
    if (r < heap->heap_size && heap->heap[r] < heap->heap[smallest])
        smallest = r;

    if (smallest != i){
       // printf("in heapify , smolest");
        swap(heap, i, smallest);
        min_heapify(heap, smallest);
    }
}//testes; seems ok? something might be wrong idk

void decrease_key( S_BIN_HEAP * heap , int index , int decrement){
    /*
    exits if heap is badly initialised or 
    if index > heap_size
    */
    if(!heap) return;
    if(!heap->heap) return;
    if ( heap->heap_size<  index) return;

    heap->heap[index]-= decrement;

    if(index==0) return;

    while(heap->heap[index] < heap->heap[OP_PARENT(index)] && (OP_PARENT(index)>0)){
        swap(heap, index, OP_PARENT(index));
        index= OP_PARENT(index);
    }

}//testes; ok

void increase_key (S_BIN_HEAP * heap , int index, int increment ){
    /*
    exits if heap is badly initialised or 
    if index > heap_size
    */
    if(!heap) return;
    if(!heap->heap) return;
    if(  heap->heap_size<index) return;

    heap->heap[index]+= increment;

    

    min_heapify(heap, index);

}//tested; ok


void insert_key( S_BIN_HEAP * heap , int value){
    /*
    handles reallocation 
    but will exit if given NULL or a 
    heap badly initialised
    */
    if(!heap) return;
    if(!heap->heap) return;

    if( heap->heap_size<= heap->heap[0]) {
        realloc_heap(heap);
    }

    int i = ++heap->heap[0];
    heap->heap[i]=value;
   
    //printf("in insert key  value %c\n", value);
    while(i>0 &&  heap->heap[OP_PARENT(i)] > heap->heap[i]){

        swap(heap, i, OP_PARENT(i));
       // printf("swap\n");
        i=OP_PARENT(i);
    }

  


}//tested ; seems ok





int pop_root( S_BIN_HEAP * heap){
    /*
    checks for heap and heap-> heap allocation 

    checks for coherence of the heap. 

    returns root on succes ; INT_MIN on failure.
    */
    if(!heap) return INT_MIN;
    if(!heap->heap) return INT_MIN;;
    if(  heap->heap_size<= heap->heap[0]) return INT_MIN;
    
    if(heap->heap[0]==1){
         heap->heap[0]--;
        return heap->heap[1];
    }

    int root= heap->heap[1];

    heap->heap[1]= heap->heap[heap->heap[0]];
    heap->heap[0]--;

    min_heapify(heap,1);

    return root;
   

}// tested; seems ok


int pop_index ( S_BIN_HEAP * heap, int index){
    /*
    pops index passed as arg; 
    checks for NULL pointer in 
    heap 
    heap->heap 

    check for index<heapsize

    returns INT_MIN on failure
    */
    if(!heap ) return INT_MIN;
    if(!heap->heap) return INT_MIN;
    if(index >= heap->heap_size) return INT_MIN;

    decrease_key(heap, index, INT_MIN);
    int ret=pop_root(heap);
    return ret;
}//tested; seems ok


void print_heap( S_BIN_HEAP * heap){
    /*
    print every element currently in the heap 
    as the array representing the heap.
    
    doesnt do anything if
    heap || heap->heap are NULL 
    */
    if(!heap ) return;
    if(!heap->heap) return;
    printf("heap of size %d\n", heap->heap_size);
    printf("currently containing : %d elements\n", heap->heap[0]);
    printf("the cell pointer is currently pointing on the cell number %d\n", heap->currindex);
    for( int i=1; i<=heap->heap[0] ; i++){
        printf("%d ", heap->heap[i]);
    }
    printf("\n");
}//tested ; works