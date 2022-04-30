%{
	#include <iostream>
	#include "Parser.h"
	using std::cout;
	using std::endl;

%}

%option noyywrap

%%
"int"		return INT;
if return IF;
else return ELSE;
[0-9]+ return NUMBER;
[a-z][a-z0-9]* return IDENT;
[=;\-()] return *yytext;


	
%%