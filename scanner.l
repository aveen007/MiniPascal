%{
	#include <iostream>
	#include "Parser.h"
	using std::cout;
	using std::endl;
	int lin=1, col=1;
	int errorno=0;
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



[\t]*	{
						col += 4*yyleng;
						}
[ ]*	{
						col += yyleng;
						}
[\n]	{
						col =1;
						lin++;
						}
						 
(i?:program) {
		col += yyleng;
		return PROGRAM;
		}
(i?:var) {
		col += yyleng;
		return VAR;
		}
(i?:real) {
		col += yyleng;
		return REAL;
	}
(i?:integer) {
		col += yyleng;
		return INTEGER;
		}
(i?:function) {
		col += yyleng;
		return FUNCTION;
		}
(i?:procedure) {
		col += yyleng;
		return PROCEDURE;
		}		
(i?:while) {
		col += yyleng;
		return WHILE;
		}
(i?:do) {
		col += yyleng;
		return DO;
		}
(i?:begin) {
		col += yyleng;
		return BEGINN;
		}
(i?:end) {
		col += yyleng;
		return END;
		}
(i?:if) {
		col += yyleng;
		return IF;
		}
(i?:then) {
		col += yyleng;
		return THEN;
		}
(i?:else) {
		col += yyleng;
		return ELSE;
		}
(i?:array) {
		col += yyleng;
		return ARRAY;
		}
(i?:of) {
		col += yyleng;
		return OF;
		}
(i?:div) {
		col += yyleng;
		return DIV;
		}	
(i?:not) {
		col += yyleng;
		return NOT;
		}
(i?:and) {
		col += yyleng;
		return AND;
		}
(i?:or) {
		col += yyleng;
		return OR;
		}

[a-zA-Z] {
		col+=yyleng;
		return ALPHA;
		}												
[a-zA-Z_][_a-z0-9A-Z]* {
		col+=yyleng;
		return ID;
		}
0|[1-9][0-9]* {
	col+=yyleng;
	return INTNUM;
	}

(0|[1-9][0-9]*)"."[0-9]*([eE][-+]?(0|[1-9][0-9]*))? |
"."[0-9]+([eE][-+]?(0|[1-9][0-9]*))?				|
(0|[1-9][0-9]*)([eE][-+]?(0|[1-9][0-9]*)) {
	col+=yyleng;
	return REALNUM;
}
 
"<>" {

		col+=yyleng;
				return NEQ;
}

[-(),{}=;?:!+*/<>\[\]\%]  {
				col+=yyleng;
				return *yytext;
				}

. {
	col += yyleng;
	errorno++;
	cout<<"\n\n_________________________Parser Error_________________________"<<endl;
	cout<<"Error Number: " <<errorno<<" "<<*yytext<<endl;
	cout<<"input.txt, Line: "<<lin <<" , col: "<<col<<endl;
	cout<<"Lexical Error"<<endl;
	}


	
%%