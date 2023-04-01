/* based on siasl2 parser.y file https://github.com/K-avi/siasl2/blob/master/src/parser.y */
%{
  #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>
  #include <ctype.h>
  #include <unistd.h>

  #include "ast.h"
  #include "globals.h"

  extern FILE* yyin;
  extern int yylex(void);
  extern int yyparse(void);
  void yyerror(const char *s);

  struct program * prog;
  
%}


%union {
  struct instruction* instruction;
  
  unsigned int token;

  struct program * prog;
}

%token <token> PRINT READ LCHILD RCHILD PARENT PLUS MINUS HEAP_DUMP POP CREATE DPRINT
%token <token> LBRACKET RBRACKET


%type <instruction> stmts stmt loop 
%type <prog> program

%type <token> op

%start program



%destructor { ; } <instruction>

%%



program
  : stmts { prog=initProg();  progMerge(prog, $1); }
  | %empty { ; }
;




stmts
  : stmt    { $$ = $1; }
  | stmts stmt  { mergeInstruction($$ = $1, $2); }
  | stmts error { free_instruct($1) ; $$=NULL; yyerror("stmts error"); YYABORT; }


;



stmt
  : loop { $$ = $1; }
  | op  {  $$ = mkinstruction($1);  }

;

loop
  : LBRACKET stmts RBRACKET {
      $$ = mkinstruction($1);
      $$->next = $2;
      $$->other = mkinstruction($3);
      mergeInstruction($$->next, $$->other);
      $$->other->other = $$;
    }
  | LBRACKET RBRACKET{
      $$ = mkinstruction($1);
      $$->next = mkinstruction($2);
      $$->other = $$->next;
      $$->other->other = $$;
    }
  
;



op
  : PRINT
  | READ
  | LCHILD
  | RCHILD
  | PARENT
  | PLUS
  | MINUS
  | HEAP_DUMP 
  | POP 
  | CREATE
  | DPRINT

;

%%


void yyerror(const char* s) {

  fprintf(stderr, "error: %s", s);
}