#ifndef EXEC_H 
#define EXEC_H

#include "ast.h"
#include "heap.h"
#include "stack.h"

extern int exec_prgm( program* progr,  S_BIN_HEAP* environment, S_STACK* stack);



#endif