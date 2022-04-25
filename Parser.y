
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


%nonassoc ELSE
%nonassoc IFPREC

%left '-'
%left '*'
%left MINUS

%%

stmts: stmt | stmts stmt
;

stmt: IDENT '=' expr ';' | IF '(' expr ')' stmt %prec IFPREC | IF '(' expr ')' stmts ELSE stmts
;

expr: NUMBER | IDENT | expr '-' expr | expr '*' expr | '-' expr %prec MINUS
;


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