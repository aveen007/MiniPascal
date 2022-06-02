
%{

	#include <iostream>
	using std::cout;
	using std::endl;

	include "ast.h";

	extern int yylex();
	extern int yyerror(const char *);
	extern int lin,col;

%}
%union
{
	Program *tProgram ;
	Declarations *tDeclarations ;
	Identifier_list *tIdentifier_list ;
	Id *tId ;
	Subprogram_declarations *tSubprogram_declarations ;
	Compound_statement *tCompound_statement ;
	Standard_type *tStandard_type;
	Array_type *tArray_type;
	Type *tType;
}

%type <tProgram> program 
%type <tDeclarations> declarations
%type <tIdentifier_list> identifier_list
%type <tSubprogram_declarations> subprogram_declarations
%type <tCompound_statement> compound_statement
%type <tStandard_type> standard_type
%type <tType> type;

%token PROGRAM
%token VAR
%token USES

%token REAL
%token INTEGER
%token STRING
%token CHAR

%token FUNCTION
%token PROCEDURE
%token WHILE
%token DO
%token FOR
%token TO


%token BEGINN
%token END
%token IF
%token THEN
%token ELSE
%token ARRAY
%token TWODOTS

%token OF
%token DIV
%token NOT
%token AND
%token OR

/* %token ALPHA */
%token <tId> ID
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
%left '>' '<' GREATEREQ LESSEREQ
%left '=' NEQ
%left NOT
%left AND
%left OR

%%

program:
	PROGRAM ID ';'
 	declarations
 	subprogram_declarations
 	compound_statement '.'
	 {
		 $$ = new Program($2 , $4 , $5 , $6 , lin , col) ;
	 }
 ;
identifier_list:
	 ID|
		identifier_list ',' ID
		;
declarations:
	declarations VAR identifier_list ':' type ';'
	{
		$$ = $1 ;
		$$->AddDeclaration( new DeclarationVar($3 , $5 , lin , col)) ;
	}
	|declarations USES identifier_list ';'
	{
		$$ = $1 ;
		$$->AddDeclaration( new Declaration($3 , lin , col)) ;
	}
	|
	{
		$$ = new Declarations(lin , col) ;
	}
	;
type:
		standard_type
		| ARRAY '[' INTNUM TWODOTS INTNUM ']' OF standard_type
		{
			$$ = new Array_type($3 ,$5 ,$8 ,lin ,col);
		}
;	
standard_type:
		INTEGER
		{
			$$ = new Standard_type(1,lin,col);
		}
		|REAL
		{
			$$ = new Standard_type(2,lin,col);
		}
		|BOOLEANN
		{
			$$ = new Standard_type(3,lin,col);
		}
;
/// From here /////////////////////////////////////////////////////
subprogram_declarations:
		subprogram_declarations subprogram_declaration ';'
		{
			$$ = $1 ;
			$$->AddSubprogramDeclaration($2) ;
		}
		|
		{
			$$ =  new Subprogram_declarations(lin , col);
		}

;	
subprogram_declaration:
		subprogram_head subprogram_variables compound_statement
		{
			$$ = new Subprogram_declaration($1 , $2 , $3 , lin , col) ;
		}

;
subprogram_variables:	subprogram_variables VAR identifier_list ':' type ';'

						|
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
		|FOR variable ':''=' expression  TO INTNUM DO  BEGINN optional_statement END
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
		|ID '[' expression ']'
		|expression unary_operator expression %prec Uoperator
		|NOT expression
		|STRING
		|CHAR
		;
unary_operator:
		'*'|'+'|'-'|'/'|DIV|'>'|LESSEREQ|'<'|GREATEREQ|'='|NEQ|NOT|OR|AND
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