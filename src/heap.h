#ifndef HEAP_H
#define HEAP_H

typedef struct bin_heap{

    int * heap;  //heap size stored at heap->heap[0]
    int heap_size;

}S_BIN_HEAP;

#define _DEFAULT_HEAPSIZE 2047 //that's a lot

#define _REALLOC_SIZE(cur_size) ( (cur_size)+1) 
//allows increase the horizontal heap size by 1

/*heap allocation*/

extern S_BIN_HEAP * initHeap(int heapsize);
extern void free_heap( S_BIN_HEAP * heap);
extern void realloc_heap (S_BIN_HEAP * heap);


/* heap manipulation*/
extern void decrease_key( S_BIN_HEAP * heap , int index , int decrement);
extern void increase_key (S_BIN_HEAP * heap , int index ,int increment);
extern void min_heapify( S_BIN_HEAP * heap , int i);
extern void swap( S_BIN_HEAP * heap, int index1, int index2 );

void insert_key( S_BIN_HEAP * heap , int value);

extern int pop_index ( S_BIN_HEAP * heap, int index);


#define OP_PARENT(index) (((index))/2)
#define OP_LCHILD(index) (((index)*2))
#define OP_RCHILD(index) (((index)*2)+1)

#endif