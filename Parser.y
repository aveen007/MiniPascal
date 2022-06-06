
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
	Subprogram_declaration *tSubprogram_declaration;
	Compound_statement *tCompound_statement ;
	Standard_type *tStandard_type;
	Array_type *tArray_type;
	Type *tType;
	Subprogram_variables Parameter_list*tSubprogram_variables;
	Subprogram_head *tSubprogram_head;
	Arguments *tArguments;
	 *tParameter_list;
}

%type <tProgram> program 
%type <tDeclarations> declarations
%type <tIdentifier_list> identifier_list
%type <tSubprogram_declarations> subprogram_declarations
%type <tSubprogram_declaration> subprogram_declaration
%type <tCompound_statement> compound_statement
%type <tStandard_type> standard_type
%type <tType> type;
%type <tSubprogram_variables> subprogram_variables;
%type <tSubprogram_head> subprogram_head;
%type <tArguments> arguments;
%type <tParameter_list> parameter_list;


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
	 ID
	 {
		 $$ = new Identifier_list(lin , col);
		 $$->AddId($1);
	 }
	 |identifier_list ',' ID
	 {
		 $$=$1;
		 $$->AddId($3);
	 }
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

//From Here--------------------------------------------somar
subprogram_variables:	subprogram_variables VAR identifier_list ':' type ';'
			{
				$$ = $1;
				$$->Add($3 , $5);
			}
			|
			{
				$$ = new Subprogram_variables(lin, col);
			}
;
subprogram_head:
		FUNCTION ID arguments ':' standard_type ';'
		{
			$$ = new Function_head($2, $3, $5, lin, col);
		}
		| PROCEDURE ID arguments ';'
		{
			$$ = new Procedure_head($2, $3, lin, col);
		}
;

arguments:
		'(' parameter_list ')'
		{
			$$ = new Arguments($3, lin ,col);
		}
		;
parameter_list:
		identifier_list ':' type
		{
			$$ = new Parameter_list(lin, col);
			$$->AddParameter($1, $3);
		}
		| parameter_list ';' identifier_list ':' type
		{
			$$ = $1;
			$$->AddParameter($3, $5);
		}
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
		|expression unary_operator expression %prec Uoperator /// What is Uoperator // By Ghaffar
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