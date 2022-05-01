%{
	#include "ast.h"
	#include "parser.h"

	 extern int lin, col;
%}

%option noyywrap
%%
"int"      return INT;

[0-9]+				{
						yylval.tNum = new Num(atoi(yytext), lin, col);
						return NUM;
					}
[a-z][a-z0-9]*       {						
						yylval.tIdent = new Ident(strdup(yytext), lin, col);
						return IDENT;
					}
[(){},\-+;=]		return *yytext;
[ \n\t]       /* IGNORE */
%%

