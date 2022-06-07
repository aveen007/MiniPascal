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
%option case-insensitive

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
".."	{
					col += 2;
					
					return TWODOTS;
						}
"program" {
		col += yyleng;
		return PROGRAM;
		}						 

"var" {
		col += yyleng;
		return VAR;
		}
"uses" {
		col += yyleng;
		return USES;

}
"real" {
		col += yyleng;
		return REAL;
	}
"integer" {
		col += yyleng;
		return INTEGER;
		}
"function" {
		col += yyleng;
		return FUNCTION;
		}
"procedure" {
		col += yyleng;
		return PROCEDURE;
		}		
"while" {
		col += yyleng;
		return WHILE;
		}
"do" {
		col += yyleng;
		return DO;
		}
"for" {
		col += yyleng;
		return FOR;
}
"to" {
		col += yyleng;
		return TO;
}

"begin" {
		col += yyleng;
		return BEGINN;
		}
"end" {
		col += yyleng;
		return END;
		}
"if" {
		col += yyleng;
		return IF;
		}
"then" {
		col += yyleng;
		return THEN;
		}
"else" {
		col += yyleng;
		return ELSE;
		}
"array" {
		col += yyleng;
		return ARRAY;
		}
"of" {
		col += yyleng;
		return OF;
		}
"div" {
		col += yyleng;
		return DIV;
		}	
"not" {
		col += yyleng;
		return NOT;
		}
"and" {
		col += yyleng;
		return AND;
		}
"or" {
		col += yyleng;
		return OR;
		}
"true" {
		col += yyleng;
		return TRUEE;
		}
"false" {
		col += yyleng;
		return FALSEE;
		}
"boolean" {
		col += yyleng;
		return BOOLEANN;
		}
"\'"[^\t]"\'" {
		yylval.tChar = new Char(strdup(yytext), lin, col);
		return CHAR;
	}
"\""[^\n\t]*"\""|"\'"[^\n\t]*"\'" {
		yylval.tString = new String(strdup(yytext), lin, col);
		return STRING;
	}
[a-zA-Z_][_a-z0-9A-Z]* {
		col+=yyleng;
		yylval.tId = new Id(strdup(yytext), lin, col);
		return ID;
		}

0|[1-9][0-9]* {
	col+=yyleng;
	yylval.tIntNum = new IntNum(atoi(yytext), lin, col);
	return INTNUM;
	}

(0|[1-9][0-9]*)"."[0-9]*([eE][-+]?(0|[1-9][0-9]*))? |
"."[0-9]+([eE][-+]?(0|[1-9][0-9]*))?				|
(0|[1-9][0-9]*)([eE][-+]?(0|[1-9][0-9]*)) {
	col+=yyleng;
	yylval.tRealNum = new RealNum(atof(yytext), lin, col);
	return REALNUM;
}
 
"<>" {

		col+=yyleng;
				return NEQ;
}
"<=" {

		col+=yyleng;
				return GREATEREQ;
}
">=" {

		col+=yyleng;
				return LESSEREQ;
}
[-(),{}=;?:!+*/<>\[\]\%\.]  {
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