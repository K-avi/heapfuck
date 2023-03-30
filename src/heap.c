#include "heap.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

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
    ret->curindex=0;

    ret->heap= (int*) calloc(heapsize, sizeof(int));
    
    if(!ret->heap){
        fprintf(stderr, "problem allocating memory for the heap in initHeap()\n");
        free(ret); 
        return NULL;
    }

    return ret;
}//not tested 

void free_heap( S_BIN_HEAP * heap){
    /*
    frees a heap; check for NULL pointer 
    before freing to avoid errors
    */

    if(!heap) return;

    if(heap->heap) free(heap->heap);
    free(heap);
}//should be ok


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

}//not tested


//heap manipulation function//

void swap( S_BIN_HEAP * heap, unsigned index1, unsigned index2 ){
    /*
    swaps the value contained at index1 and index2 in a heap; 
    doesn't do anything if :
    heap = NULL 
    heap->heap = NULL 
    (index1 or index2) > heap->heapsize
    */
    if(!heap) return;
    if(!heap->heap) return;
    if( (index1 > heap->heap_size) || (index2 > heap->heap_size)) return;

    unsigned tmpVal= heap->heap[index1];

    heap->heap[index1]= heap->heap[index2];
    heap->heap[index2]= tmpVal;

}//not tested 
//kinda stupid ; could prolly be a macro
//or pass int * as args.


void decrease_key( S_BIN_HEAP * heap , int index , int newval){
    if(!heap) return;
    if(!heap->heap) return;
    if(heap->heap_size< index) return;

    heap->heap[index]= newval;

    while(heap->heap[index] > PARENT(index)){
        swap(heap, index, PARENT(index));
    }
}//not tested

void increment_key (S_BIN_HEAP * heap , int index){
    if(!heap) return;
    if(!heap->heap) return;
    if(heap->heap_size< index) return;

    while(heap->heap[index] < LCHILD(index)){
        swap(heap, index, PARENT(index));
    }
}//not done

void insert_key( S_BIN_HEAP * heap , int value){
    if(!heap) return;
    if(!heap->heap) return;
    if(heap->heap_size<= heap->curindex) return;

    int i = heap->heap_size;
    heap->heap[i]=value;
    heap->heap_size++;

    while(i>0 &&  heap->heap[PARENT(i)] > heap->heap[i]){

        swap(heap, i, PARENT(i));

        i=PARENT(i);
    }


}//not tested


void min_heapify( S_BIN_HEAP * heap , int i){
    int l = heap->heap[LCHILD(i)];
    int r = heap->heap[LCHILD(i)];
    int smallest = i;
    if (l < heap->heap_size && heap->heap[l] < heap->heap[i])
        smallest = l;
    if (r < heap->heap_size && heap->heap[r] < heap->heap[smallest])
        smallest = r;
    if (smallest != i)
    {
        swap(heap, i, smallest);

        min_heapify(heap, smallest);
    }
}//pas teste 
//peut etre faire avc pointeurs jsp ??


int pop_root( S_BIN_HEAP * heap){
    if(!heap) return 0;
    if(!heap->heap) return 0;;
    if(heap->heap_size<= heap->curindex) return 0;
    
    if(heap->heap[0]==1){
         heap->heap[0]--;
        return heap->heap[1];
    }

    int root= heap->heap[1];

    heap->heap[1]= heap->heap[heap->heap[0]];
    heap->heap[0]--;

    min_heapify(heap,0);

    return root;
   

}//not tested


int pop_index ( S_BIN_HEAP * heap, int index){
    decrease_key(heap, index, INT_MIN);
    pop_root(heap);
    return 0;
}//not tested