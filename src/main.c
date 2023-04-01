#include "heap.h"
#include "stack.h"
#include "globals.h"
#include "exec.h"
#include "ast.h"

#include "parser.tab.h"
#include "lex.yy.h"

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <ctype.h>

extern program  * prog;



#include <signal.h>

extern program * prog;


void sigint_handler( int sig){
    if(!progempty) {
        free_prog(prog);
    }
    if(environment) free_heap(environment);
    if(stack) free_stack(stack);


    yylex_destroy();
    printf("\n");
    exit (SIGINT);

    return;
}

int main(int argc, char ** argv){  

    signal(SIGINT, *sigint_handler );

    unsigned char cmdline_mode=1, file_mode=0;

    unsigned char helpset=0;

    char* filename = NULL;
    int c;

    printf("(SIASL)² Copyright (C) 2023  Ivan MULOT-RADOJCIC\nThis program comes with ABSOLUTELY NO WARRANTY;\nfor details see the GPLv3 documentation.\nThis is free software, and you are welcome to redistribute it under certain conditions\n\n");

    while ((c = getopt(argc, argv, "hcf:")) != -1) {
        
        switch (c) {
      
        case 'h':
            helpset=1;;
            break;
        
        case 'f':
            filename = optarg;
            cmdline_mode=0;
            file_mode=1;
            break;
        case 'c':
            
            cmdline_mode=1;
            file_mode=0;
            break;
      
        case '?':
            if (optopt == 'f')
            fprintf(stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint(optopt))
            fprintf(stderr, "Unknown option `-%c'.\n", optopt);
            else
            fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
       
            exit(-2);
        default:
            abort();
        }
    }

    if(helpset){

        printf("heapfuck is a brainfuck like esolang; the options available are:\n-f to read a file\n-c to use the command line interactive interpret\nmore informations on the heapfuck language can be found in the README.txt and docu/docu.html files.\n"); 

        exit(0);

    }

    
    /*initialising environment and stack ; prog is initialised by parser.tab.c*/
    environment= initHeap(_DEFAULT_HEAPSIZE);
    stack= init_stack(STACK_SIZE);
 
    

    if (cmdline_mode) {

         cmdline_interp();

         return 0;
         
    }else if(file_mode){

         yyin = fopen(filename, "r");
        if (!yyin) {
            perror("Could not open file");
            exit(-1);
        }
        yyparse();
        progempty=0;
        fclose(yyin);

        exec_prgm(prog, environment, stack);

        /*freeing everything after exec*/
        free_heap(environment);
        free_stack(stack);
        free_prog(prog);
        
        progempty=1;

        yylex_destroy();
    }
    printf("\n");
    return 0;
}