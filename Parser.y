
%{

	#include <iostream>
	using std::cout;
	using std::endl;
	extern int yylex();
	extern int yyerror(const char *);
	extern int lin,col;

%}

%token PROGRAM
%token VAR
%token REAL
%token INTEGER
%token STRING
%token CHAR

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
%token TRUEE
%token FALSEE
%token BOOLEANN


%nonassoc ELSE
%nonassoc IFPREC
%nonassoc Uoperator

%left '*' '.' '/' ',' DIV
%left '+' '-'
%left '>' '<'
%left '=' NEQ
%left NOT
%left AND
%left OR

%%

program:
	PROGRAM ID ';'
 	declarations
 	subprogram_declarations
 	compound_statement
 ;
identifier_list:
	 ID|
		identifier_list ',' ID
		;
declarations:
	declarations VAR identifier_list ':' type ';'
	|
	;
type:
		standard_type
		| ARRAY '[' INTNUM '.''.' INTNUM ']' OF
		standard_type
;	
standard_type:
		INTEGER
		|REAL
		|BOOLEANN
;
subprogram_declarations:
		subprogram_declarations subprogram_declaration ';'
		|
;	
subprogram_declaration:
		subprogram_head compound_statement
;
subprogram_head:
		FUNCTION ID arguments ':' standard_type ';'
			| PROCEDURE ID arguments ';'
			;
arguments:
		'(' parameter_list ')'
		|
		;
parameter_list:
		identifier_list ':' type
		| parameter_list ';' identifier_list ':' type
		;
compound_statement:
		BEGINN optional_statement END
		;
optional_statement:
		statement_list
		|
		;
statement_list:
		statement ';'
		|statement_list statement ';'
		;
statement:
		variable ':''=' expression 
		|procedure_statement
		|compound_statement
		|IF expression THEN statement %prec IFPREC
		|IF expression THEN statement ELSE statement
		|WHILE expression DO statement
		;
variable:
		ID
		|ID '[' expression ']'
		;
procedure_statement:
		ID|
		ID '(' expression_list ')'

expression_list:
		expression
		|expression_list ',' expression
		;
expression:
		ID
		|INTNUM
		|REALNUM
		|TRUEE
		|FALSEE
		|ID '(' expression_list ')' 
		|'(' expression ')'
		|expression unary_operator expression %prec Uoperator
		|NOT expression
		|STRING
		|CHAR
		;
unary_operator:
		'*'|'+'|'-'|'/'|DIV|'>'|'>''='|'<'|'<''='|'='|NEQ|NOT|OR|AND
		;




%%

int yyerror(const char * s){

//	cout << "Syntax Error.... " << endl;
	fprintf(stderr, "%s %d %s %d\n", "Syntax Error....",lin,"  ", col);
	return 1;

}

/* int main(){

	yyparse();
	system("pause");
	return 0;
} */