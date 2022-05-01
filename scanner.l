%{
	#include <iostream>
	#include "Parser.h"
	using std::cout;
	using std::endl;
	int lin=1, col=1;
%}

%x comment
%x commentOneLiner

%option noyywrap

%%
"{"								{BEGIN(comment); col += yyleng;}
<comment>"}"						{BEGIN(0); col += yyleng;}
<comment>[^\n\t]?					{col+=yyleng;}
<comment>\n							{lin++; col = 1;}
<comment>\t							{col+=4*yyleng;}

"/"								{BEGIN(commentOneLiner); col += yyleng;}
<commentOneLiner>[\n]						{BEGIN(0); lin++; col = 1;}
<commentOneLiner>[^\n\t]?					{col+=yyleng;}
<commentOneLiner>\t							{col+=4*yyleng;}



"int"		return INT;
if return IF;
else return ELSE;
[0-9]+ return NUMBER;
[a-z][a-z0-9]* return IDENT;
[=;\-{}(),+] return *yytext;
[ \n\t]			/*IGNORE*/;


	
%%