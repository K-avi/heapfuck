%option header-file="lex.yy.h"
%option noinput nounput noyywrap


%{
  #include "parser.tab.h"
  #define TOKEN(t) yylval.token = (t)
%}

%%

[ \t\n]+    { ; }
"."         { return TOKEN(PRINT); }
","         { return TOKEN(READ); }
">"         { return TOKEN(RCHILD); }
"<"         { return TOKEN(LCHILD); }
"^"         { return TOKEN(PARENT); }
"+"         { return TOKEN(PLUS); }
"-"         { return TOKEN(MINUS); }
"["         { return TOKEN(LBRACKET); }
"]"         { return TOKEN(RBRACKET); }

.           { ; }

%%