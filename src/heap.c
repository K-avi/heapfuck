#include "heap.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
    ret->heap= (int*) malloc(heapsize* sizeof(int));

    if(!ret->heap){
        fprintf(stderr, "problem allocating memory for the heap in initHeap()\n");
        free(ret); 
        return NULL;
    }

    memset(ret->heap, INT_MIN, heapsize*sizeof(int));

    ret->heap[0]=0;

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
    if ( (int)heap->heap_size<  index) return;

    heap->heap[index]= newval;

    while(heap->heap[index] > OP_PARENT(index)){
        swap(heap, index, OP_PARENT(index));
    }
}//not tested

void increment_key (S_BIN_HEAP * heap , int index){
    if(!heap) return;
    if(!heap->heap) return;
    if(  (int)heap->heap_size<index) return;

    while(heap->heap[index] < OP_LCHILD(index)){
        swap(heap, index, OP_PARENT(index));
    }
}//not done

void insert_key( S_BIN_HEAP * heap , int value){
    if(!heap) return;
    if(!heap->heap) return;
    if( (int)heap->heap_size<= heap->heap[0]) return;

    int i = heap->heap_size;
    heap->heap[i]=value;
    heap->heap_size++;

    while(i>0 &&  heap->heap[OP_PARENT(i)] > heap->heap[i]){

        swap(heap, i, OP_PARENT(i));

        i=OP_PARENT(i);
    }


}//not tested


void min_heapify( S_BIN_HEAP * heap , int i){
    int l = heap->heap[OP_LCHILD(i)];
    int r = heap->heap[OP_LCHILD(i)];
    int smallest = i;
    if (l <  (int)heap->heap_size && heap->heap[l] < heap->heap[i])
        smallest = l;
    if (r < (int) heap->heap_size && heap->heap[r] < heap->heap[smallest])
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
    if(  (int)heap->heap_size<= heap->heap[0]) return 0;
    
    if(heap->heap[0]==1){
         heap->heap[0]--;
        return heap->heap[1];
    }

    int root= heap->heap[1];

    heap->heap[1]= heap->heap[heap->heap[0]];
    heap->heap[0]--;

    min_heapify(heap,1);

    return root;
   

}//not tested


int pop_index ( S_BIN_HEAP * heap, int index){
    if(!heap ) return INT_MIN;
    decrease_key(heap, index, INT_MIN);
    int ret=pop_root(heap);
    return ret;
}//not tested


void print_heap( S_BIN_HEAP * heap){
    if(!heap ) return;
    if(!heap->heap) return;
    printf("heap of size %d\n", heap->heap_size);
    printf("currently containing : %d elements\n", heap->heap[0]);

    for( int i=1; i<heap->heap[0] ; i++){
        printf("%d ", heap->heap[i]);
    }
    printf("\n");
}