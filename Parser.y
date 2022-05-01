
%{

	#include <iostream>
	using std::cout;
	using std::endl;
	extern int yylex();
	extern int yyerror(const char *);

%}

%token PROGRAM
%token VAR
%token REAL
%token INTEGER
%token FUNCTION
%token PROCEDURE
%token WHILE
%token DO
%token BEGINN
%token END
%token IF
%token THEN
%token ELSE
%token ARRAY
%token OF
%token DIV
%token NOT
%token AND
%token OR

%token ALPHA
%token ID
%token INTNUM
%token REALNUM
%token NEQ



%token NUMBER
%token IDENT
%token INT

%nonassoc ELSE
%nonassoc IFPREC


%left DIV
%left ','
%left '/'
%left '.'
%left '*'
%left '-'
%left '+'
%left '='
%left NEQ
%left '>'
%left '<'
%left NOT
%left AND
%left OR

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