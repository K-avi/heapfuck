#ifndef HEAP_H
#define HEAP_H

typedef struct bin_heap{

    int * heap; 
    unsigned heap_size;
    unsigned curindex;

}S_BIN_HEAP;

#define _DEFAULT_HEAPSIZE 2047 //that's a lot

#define _REALLOC_SIZE(cur_size) ( (cur_size)+1) 
//allows increase the horizontal heap size by 1

#define PARENT(index) (((index)-1)/2)
#define CHILD1(index) (((index)*2)+1)
#define CHILD2(index) (((index)*2)+2)

#endif