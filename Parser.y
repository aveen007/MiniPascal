
%{

	#include <iostream>
	using std::cout;
	using std::endl;
	extern int yylex();
	extern int yyerror(const char *);

%}

%token NUMBER
%token IDENT
%token IF
%token INT

%nonassoc ELSE
%nonassoc IFPREC


/* %left '-' */
/* %left '*' */
%left '+'
%left '='
/* %left MINUS */

%%
func:
type IDENT '(' args_e ')' '{' stmts '}' 
					{ 
						cout<<"parsing is done correctly! \n";
						
						 }		
;
arg :
type IDENT
;
args:
		arg
		| args ',' arg 
;
args_e:
		/* empty */
		| args
;
type:
		INT 
;

expr:
		NUMBER
		| IDENT 
		| IDENT '=' expr 
		| expr '+' expr
;
stmt:
		expr ';'
		| type
		expr ';'
		| IF '(' expr ')' stmt %prec IFPREC
		| IF '(' expr ')' stmt ELSE stmt
		| '{' stmts '}' 
;
stmts:
		/* Empty */
		|stmts stmt
;

/* stmts: stmt | stmts stmt
;

stmt: IDENT '=' expr ';' | IF '(' expr ')' stmt %prec IFPREC | IF '(' expr ')' stmts ELSE stmts
;

expr: NUMBER | IDENT | expr '-' expr | expr '*' expr | '-' expr %prec MINUS
; */


%%

int yyerror(const char * s){

	cout << "Syntax Error.... " << endl;
	return 1;

}

/* int main(){

	yyparse();
	system("pause");
	return 0;
} */