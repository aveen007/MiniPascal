
%{

	#include <iostream>
	#include "ast.h"
	#include "ast.cpp"

	using std::cout;
	using std::endl;

	extern int yylex(void);
	extern int yyerror(const char *);
	Program *root ;
	extern int lin ,col;
	int current_kind = 2;
	
	 SymbolTable *symbolTable =new SymbolTable();

%}
%union
{
	class Id *tId ;
	class Program *tProgram ;
	class Declarations *tDeclarations ;
	class Identifier_list *tIdentifier_list ;
	class Subprogram_declarations *tSubprogram_declarations ;
	class Subprogram_declaration *tSubprogram_declaration;
	class Compound_statement *tCompound_statement ;
	class Standard_type *tStandard_type;
	class Type *tType;
	class Subprogram_variables *tSubprogram_variables;
	class Subprogram_head *tSubprogram_head;
	class Arguments *tArguments;
	class Parameter_list *tParameter_list;
	class Optional_statement *tOptional_statement;
	class Statement_list *tStatement_list;
	class Statement *tStatement;
	class Expression *tExpression;
	class Expression_list *tExpression_list ;
	class IntNum *tIntNum;
	class RealNum *tRealNum;
	class String *tString;
	class Char *tChar;
	class Bool *tBool;
	class Unary_operator *tUnary_operator;
	class Variable *tVariable ;
	class Procedure_statement *tProcedure_statement ;
}

%type <tProgram> program 
%type <tDeclarations> declarations
%type <tIdentifier_list> identifier_list
%type <tSubprogram_declarations> subprogram_declarations
%type <tSubprogram_declaration> subprogram_declaration
%type <tCompound_statement> compound_statement
%type <tStandard_type> standard_type
%type <tType> type
%type <tSubprogram_variables> subprogram_variables
%type <tSubprogram_head> subprogram_head
%type <tArguments> arguments
%type <tParameter_list> parameter_list
%type <tOptional_statement> optional_statement
%type <tStatement_list> statement_list
%type <tStatement> statement
%type <tExpression> expression
%type <tUnary_operator> unary_operator
%type <tVariable> variable
%type <tProcedure_statement> procedure_statement 
%type <tExpression_list> expression_list 

%token PROGRAM
%token VAR
%token USES

%token REAL
%token INTEGER
%token <tString> STRING
%token <tChar> CHAR

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
%token <tIntNum> INTNUM
%token <tRealNum> REALNUM
%token NEQ
%token <tBool> TRUEE
%token <tBool> FALSEE
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
	PROGRAM 
	{
				symbolTable->OpenScope();

	} ID {
				symbolTable->AddSymbol($3,4,1);

	}';' declarations
 	subprogram_declarations
 	compound_statement '.'
	 {
		 $$ = new Program($3 , $6 , $7 , $8 , lin , col) ;
		 root = $$ ;
				// symbolTable->AddSymbol($2,1,1);
// symbolTable->AddSymbol($2,4,6);
		 cout<<"Somaaaaaaaaaar Avooooooooooooooo DONNNNNNNNNE"<<endl;
			//	symbolTable->CloseScope();


	 }
 ;
identifier_list:
	 ID
	 {
		 $$ = new Identifier_list(lin , col);
		 $$->AddId($1);
		// cout<<sizeof($$->Ids);


	 }
	 |identifier_list ',' ID
	 {
		 $$=$1; 


		 $$->AddId($3);
		// cout<<sizeof($$->Ids[2]);
	 }
	;
declarations:
	declarations VAR identifier_list ':' type ';'
	{
		$$ = $1 ;
		$$->AddDeclaration( new DeclarationVar($3 , $5 , lin , col)) ;

			for(int i=0; i<$3->Ids->size();i++)
			{

	
	
				symbolTable->AddSymbol($3->Ids[0][i],current_kind,$5->type);
			
			}
	

	}
	|declarations USES identifier_list ';'
	{
		$$ = $1 ;
		$$->AddDeclaration( new Declaration($3 , lin , col)) ;
			for(int i=0; i<$3->Ids->size();i++)
			{

	
	
				symbolTable->AddSymbol($3->Ids[0][i],current_kind,6);
			
			}				

	}
	|
	{
		$$ = new Declarations(lin , col) ;
	}
	;
type:
		standard_type
		{
			$$ = $1 ;
		}
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

subprogram_variables:	subprogram_variables VAR identifier_list ':' type ';'
			{
				$$ = $1;
				$$->AddVar($3 , $5);
						for(int i=0; i<$3->Ids->size();i++)
			{

	
	
				symbolTable->AddSymbol($3->Ids[0][i],current_kind,$5->type);
			
			}
			}
			|
			{
				$$ = new Subprogram_variables(lin, col);
			}
;
subprogram_head:
		FUNCTION {
	symbolTable->OpenScope();
							current_kind = 3;
							
		} ID
		{

		} arguments ':' standard_type ';'
		{
			$$ = new Function_head($3, $5, $7, lin, col);
			symbolTable->AddFunc($3 , 1 , $5 , $7->type , $$ );


		}
		| PROCEDURE {
	symbolTable->OpenScope();
							current_kind = 3;
							
		}
		ID
		{

		} arguments ';'
		{
			$$ = new Procedure_head($3, $5, lin, col);
			symbolTable->AddFunc($3 , 5 , $5 , 6 , $$ );
	
		}
;

arguments:
		'(' parameter_list ')'
		{
			$$ = new Arguments($2, lin ,col);
		}
		;
parameter_list:
		identifier_list ':' type
		{
			$$ = new Parameter_list(lin, col);
			$$->AddParameter($1, $3);
					for(int i=0; i<$1->Ids->size();i++)
			{

	
	
				symbolTable->AddSymbol($1->Ids[0][i],current_kind,$3->type);
			
			}
		}
		| parameter_list ';' identifier_list ':' type
		{
			$$ = $1;
			$$->AddParameter($3, $5);
					for(int i=0; i<$3->Ids->size();i++)
			{

				symbolTable->AddSymbol($3->Ids[0][i],current_kind,$5->type);
			
			}
		}
;
compound_statement:
		BEGINN optional_statement END
		{
			$$ = new Compound_statement($2, lin, col);
			symbolTable->CloseScope();
			current_kind = 2;
		}
		;
optional_statement:
		statement_list
		{
			$$ = new Optional_statementNonEmpty($1, lin, col);
		}
		|
		{
			$$ = new Optional_statement( lin, col);
		}
;
statement_list:
		statement ';'
		{
			$$ = new Statement_list(lin, col);
			$$->AddStatement($1);
		}
		|statement_list statement ';'
		{
			$$ = $1;
			$$->AddStatement($2);
		}
;
statement:
		variable ':''=' expression
		{
			$$ = new Variable_Expression($1, $4 ,lin, col);
		}
		|procedure_statement
		{
			$$ = $1;
		}
		|compound_statement
		{
			$$ = $1 ;
		}
		|IF expression THEN statement %prec IFPREC
		{
			$$ = new If($2, $4 ,lin, col);
		}
		|IF expression THEN statement ELSE statement
		{
			$$ = new IfElse($2, $4 , $6, lin, col);
		}
		|WHILE expression DO statement
		{
			$$ = new While($2, $4 ,lin, col);
		}
		|FOR
		{
		//	symbolTable->OpenScope();
		} variable ':''=' expression  TO INTNUM DO  BEGINN optional_statement END
		{
			$$ = new For($3, $6, $11, lin, col);
		}
		;
variable:
		ID
		{
			$$ = new Variable($1 , lin , col) ;
				 symbolTable->LookUp($1);

		}
		|ID '[' expression ']'
		{
			$$ = new VariableExpression($3 , $1 , lin , col) ;
				 symbolTable->LookUp($1);

				// symbolTable->AddSymbol($1,1,1);

		}
		;
procedure_statement:
		ID
		{
			$$ = new Procedure_statement($1 , lin , col) ;
			//	symbolTable->LookupConstructor($1 );

		}
		|
		ID '(' expression_list ')'
		{
			$$ = new Procedure_statementList($3 , $1 , lin , col) ; 
			//	symbolTable->LookupConstructor($1 );

		}

expression_list:
		expression
		{
			$$ = new Expression_list(lin , col); 
			$$->AddExpression($1) ;
		}
		|expression_list ',' expression
		{
			$$ = $1 ;
			$$->AddExpression($3 ) ;
		}
		;
expression:
		ID
		{
			$$ = new IdExpr($1 ,lin, col);
			

		}
		|INTNUM
		{
			$$ = new IntNumExpr($1, lin, col);
		}
		|REALNUM
		{
			$$ = new RealNumExpr($1, lin, col);
		}
		|TRUEE
		{
			$$ = new BoolExpr($1, lin, col);
		}
		|FALSEE
		{
			$$ = new BoolExpr($1, lin, col);
		}
		|ID '(' expression_list ')' 
		{
			$$ = new ListWithExpr($1 ,$3, lin, col);
		}
		|'(' expression ')'
		{
			$$ = new ExpressionWithExpr($2 ,lin, col);
		}
		|ID '[' expression ']'
		{
			$$ = new BracketExpr($1 ,$3 ,lin, col);
		}
		|expression unary_operator expression %prec Uoperator /// What is Uoperator // By Ghaffar
		{
			$$ = new UnaryExpr($1 ,$2, $3 ,lin, col);
		}
		|NOT expression
		{
			$$ = new NotExpr($2 ,lin, col);
		}
		|STRING
		{
			$$ = new StringExpr($1, lin, col);
		}
		|CHAR
		{
			$$ = new CharExpr($1, lin, col);
		}
		;
unary_operator:
		'*'
		{
			$$ = new Unary_operator(1, lin, col);
		}
		|'+'
		{
			$$ = new Unary_operator(2, lin, col);
		}
		|'-'
		{
			$$ = new Unary_operator(3, lin, col);
		}
		|'/'
		{
			$$ = new Unary_operator(4, lin, col);
		}
		|DIV
		{
			$$ = new Unary_operator(5, lin, col);
		}
		|'>'
		{
			$$ = new Unary_operator(6, lin, col);
		}
		|LESSEREQ
		{
			$$ = new Unary_operator(7, lin, col);
		}
		|'<'
		{
			$$ = new Unary_operator(8, lin, col);
		}
		|GREATEREQ
		{
			$$ = new Unary_operator(9, lin, col);
		}
		|'='
		{
			$$ = new Unary_operator(10, lin, col);
		}
		|NEQ
		{
			$$ = new Unary_operator(11, lin, col);
		}
		|NOT
		{
			$$ = new Unary_operator(12, lin, col);
		}
		|OR
		{
			$$ = new Unary_operator(13, lin, col);
		}
		|AND
		{
			$$ = new Unary_operator(14, lin, col);
		}
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