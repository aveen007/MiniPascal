#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "hash_fun.h"
#include "hash_table.h"

using namespace std;
using std::cout;
using std::endl;
using std::ofstream ;
using std::ios ;



static ofstream vout ("code.txt" , ios::out) ;


class Symbol;
// typedef CHashTable<Symbol> HashTab;
// typedef _Cxx_hashtable_define_trivial_hash<Symbol> HashTab;

class Declarations;

class Statement;
class AssignmentIdStatement ;
class AssignmentArrayStatement ;
class Expression_list;

class Identifier_list;

class Id;

class IntNum;

class RealNum;

class String;

class Bool;

class Char;

class Expression;

class IdExpr;

class IntNumExpr;

class BoolExpr;

class RealNumExpr;

class StringExpr;

class CharExpr;

class ListWithExpr;

class UnaryExpr;

class NotExpr;

class BracketExpr;

class ExpressionWithExpr;

class Subprogram_declarations;

class Type;

class Compound_statement;

class Subprogram_head;

class Subprogram_variables;

class Arguments;

class Parameter_list;

class Statement_list;

class Optional_statement;

class Compound_statement;

class Variable;

class Procedure_statement;

class If;

class IfElse;

class While;

class For;

class Expression_list;

class Unary_operator;

class Visitor;

class PrintVisitor;
typedef CHashTable<Symbol> HashTab;

class Node
{
public:
    int line;
    int column;
    Node *father;

    Node(int, int);
    virtual void accept(Visitor *v);
};

/// subprogram_declarations
class Subprogram_declaration : public Node
{
public:
    Subprogram_head *subprogramHead;
    Subprogram_variables *subprogramVariables;
    Compound_statement *compoundStatement;

    Subprogram_declaration(Subprogram_head *,
                           Subprogram_variables *,
                           Compound_statement *, int, int);
    virtual void accept(Visitor *v);
};

class Subprogram_declarations : public Node
{
public:
    vector<Subprogram_declaration *> *subprogram_declarations;

    Subprogram_declarations(int, int);

    void AddSubprogramDeclaration(Subprogram_declaration *);
    virtual void accept(Visitor *v);
};

/// Type
class Type : public Node
{
public:
    Type(int, int, int);
    Type(int, int, int, int, int);
    int type; // 1 integer, 2 Real, 3 Boolean
    int first;
    int second;
    virtual void accept(Visitor *v);
};

class Standard_type : public Type
{
public:
    int type; // 1 integer, 2 Real, 3 Boolean
    Standard_type(int, int, int);
    virtual void accept(Visitor *v);
};

class Array_type : public Type
{
public:
    IntNum *first;
    IntNum *last;
    Standard_type *StandardType;

    Array_type(IntNum *, IntNum *, Standard_type *, int, int);
    virtual void accept(Visitor *v);
};

/// Program
class Program : public Node
{
public:
    Id *id;
    Declarations *declarations;
    Subprogram_declarations *subprogramDeclarations;
    Compound_statement *compoundStatement;

    Program(Id *, Declarations *, Subprogram_declarations *, Compound_statement *,
            int, int);
    virtual void accept(Visitor *v);
};

/// Declarations
class Declaration : public Node
{
public:
    Identifier_list *identifierList;

    Declaration(Identifier_list *, int, int);
    virtual void accept(Visitor *v);
};

class DeclarationVar : public Declaration
{
public:
    Type *type;

    DeclarationVar(Identifier_list *, Type *, int, int);
    virtual void accept(Visitor *v);
};

class Declarations : public Node
{
public:
    vector<Declaration *> *declarations;

    Declarations(int, int);

    void AddDeclaration(Declaration *);
    virtual void accept(Visitor *v);
};

// From Here----------------somar
/// INTNUM
// class IntNum :
/// Id
class Id : public Node
{
public:
    string name;
    Symbol *symbol;
    Id(string, int, int);
    virtual void accept(Visitor *v);
};

class IntNum : public Node
{
public:
    int value;

    IntNum(int, int, int);
    virtual void accept(Visitor *v);
};

class RealNum : public Node
{
public:
    double value;

    RealNum(double, int, int);
    virtual void accept(Visitor *v);
};

class String : public Node
{
public:
    string value;

    String(string, int, int);
    virtual void accept(Visitor *v);
};

class Char : public Node
{
public:
    char value;

    Char(char, int, int);
    virtual void accept(Visitor *v);
};

class Bool : public Node
{
public:
    bool value;

    Bool(bool, int, int);
    virtual void accept(Visitor *v);
};

class Identifier_list : public Node
{
public:
    vector<Id *> *Ids;

    Identifier_list(int, int);

    void AddId(Id *);
    virtual void accept(Visitor *v);
};

class Subprogram_variables : public Node
{
public:
    vector<pair<Identifier_list *, Type *>> *subprogramVariables;

    Subprogram_variables(int, int);

    void AddVar(Identifier_list *, Type *);
    virtual void accept(Visitor *v);
};

class Subprogram_head : public Node
{
public:
    Id *id;
    Arguments *arguments;
    bool CG_visited;
    Subprogram_head(Id *, Arguments *, int, int);
    virtual void accept(Visitor *v);
};

class Function_head : public Subprogram_head
{
public:
    Standard_type *standardType;

    Function_head(Id *, Arguments *, Standard_type *, int, int);
    virtual void accept(Visitor *v);
};

class Procedure_head : public Subprogram_head
{
public:
    Procedure_head(Id *, Arguments *, int, int);
    virtual void accept(Visitor *v);
};

class Arguments : public Node
{
public:
    Parameter_list *parameterList;

    Arguments(Parameter_list *, int, int);
    virtual void accept(Visitor *v);
};

class Parameter_list : public Node
{
public:
    vector<pair<Identifier_list *, Type *>> *parameters;

    Parameter_list(int, int);

    void AddParameter(Identifier_list *, Type *);
    virtual void accept(Visitor *v);
};

/// ---------------------------- Ghaffar
class Statement : public Node
{
public:
    Statement(int, int);
    virtual void accept(Visitor *v);
};
class Assignment_statement : public Statement
{
public:
    Assignment_statement(int , int) ;
};
class AssignmentIdStatement : public Assignment_statement
{
public:
    Id * id ;
    Expression * expression ;
    AssignmentIdStatement(Id* , Expression* , int , int);
};

class AssignmentArrayStatement : public Assignment_statement
{
public:
    Id * id ;
    Expression * index ;
    Expression * expression ;
    AssignmentArrayStatement(Id* , Expression* , Expression* , int , int);
};
class Compound_statement : public Statement
{
public:
    Optional_statement *optionalStatement;

    Compound_statement(Optional_statement *, int, int);
    virtual void accept(Visitor *v);
};
class Optional_statement : public Statement
{
public:
    Statement_list *statementList;

    Optional_statement(Statement_list *, int, int);
    virtual void accept(Visitor *v);
};
class Optional_statementNonEmpty : public Optional_statement
{
public:
    Statement_list *statementList;

    Optional_statementNonEmpty(Statement_list *, int, int);
    virtual void accept(Visitor *v);
};

class Empty_optional_statement : public Optional_statement
{
public:
    Empty_optional_statement(int, int);
    virtual void accept(Visitor *v);
};
class Variable_Expression : public Statement
{
public:
    Variable *variable;
    Expression *expression;

    Variable_Expression(Variable *, Expression *, int, int);
    virtual void accept(Visitor *v);
};

class Procedure_statement : public Statement
{
public:
    Id *id;
    Expression_list *expressionList;
    bool CG_visited;
    Procedure_statement(Expression_list *, Id *, int, int);
    virtual void accept(Visitor *v);
};
class Procedure_statementList : public Procedure_statement
{
public:
    Expression_list *expressionList;
    Procedure_statementList(Expression_list *, Id *, int, int);
    virtual void accept(Visitor *v);
};
class If : public Statement
{
public:
    Expression *expression;
    Statement *thenStatement;

    If(Expression *, Statement *, int, int);
    virtual void accept(Visitor *v);
};

class IfElse : public Statement
{
public:
    Expression *expression;
    Statement *thenStatement;
    Statement *elseStatement;

    IfElse(Expression *, Statement *, Statement *, int, int);
    virtual void accept(Visitor *v);
};

class While : public Statement
{
public:
    Expression *expression;
    Statement *doStatement;

    While(Expression *, Statement *, int, int);
    virtual void accept(Visitor *v);
};

class For : public Statement
{
public:
    Variable *variable;
    Expression * down;
    Expression * up ;
    Optional_statement *optionalStatement;

    For(Variable *, Expression *, Expression* , Optional_statement *, int, int);
    virtual void accept(Visitor *v);
};

class Statement_list : public Node
{
public:
    vector<Statement *> *statement_list;

    Statement_list(int, int);

    void AddStatement(Statement *);
    virtual void accept(Visitor *v);
};
/// Expression
/*
 * ID
        0|INTNUM
        1|REALNUM
        2|TRUEE
        3|FALSEE
        4|ID '(' expression_list ')'
        5|'(' expression ')'
        6|ID '[' expression ']'
        7|expression unary_operator expression %prec Uoperator
        8|NOT expression
        9|STRING
        10|CHAR
 */
class Expression : public Node
{
public:
    Expression(int, int);
    int type;
    virtual void accept(Visitor *v);
};

class IdExpr : public Expression
{
public:
    Id *id;

    IdExpr(Id *, int, int);
    virtual void accept(Visitor *v);
};

class IntNumExpr : public Expression
{
public:
    IntNum *intNum;

    IntNumExpr(IntNum *, int, int);
    virtual void accept(Visitor *v);
};

class RealNumExpr : public Expression
{
public:
    RealNum *realNum;

    RealNumExpr(RealNum *, int, int);
    virtual void accept(Visitor *v);
};

class BoolExpr : public Expression
{
public:
    Bool *aBool;

    BoolExpr(Bool *, int, int);
    virtual void accept(Visitor *v);
};

class StringExpr : public Expression
{
public:
    String *aString;

    StringExpr(String *, int, int);
    virtual void accept(Visitor *v);
};

class CharExpr : public Expression
{
public:
    Char *aChar;

    CharExpr(Char *, int, int);
    virtual void accept(Visitor *v);
};

class ListWithExpr : public Expression
{
public:
    Id *id;
    Expression_list *expressionList;

    ListWithExpr(Id *, Expression_list *, int, int);
    virtual void accept(Visitor *v);
};

class ExpressionWithExpr : public Expression
{
public:
    Expression *expression;

    ExpressionWithExpr(Expression *, int, int);
    virtual void accept(Visitor *v);
};

class UnaryExpr : public Expression
{
public:
    Expression *leftExpression;
    Unary_operator *unaryOperator;
    Expression *rightExpression;

    UnaryExpr(Expression *, Unary_operator *, Expression *, int, int);
    virtual void accept(Visitor *v);
};

class NotExpr : public Expression
{
public:
    Expression *expression;

    NotExpr(Expression *, int, int);
    virtual void accept(Visitor *v);
};

class BracketExpr : public Expression
{
public:
    Id *id;
    Expression *expression;

    BracketExpr(Id *, Expression *, int, int);
    virtual void accept(Visitor *v);
};

/// UOperator
class Unary_operator : public Node
{
public:
    int index;

    Unary_operator(int, int, int);
    virtual void accept(Visitor *v);
};

class Expression_list : public Node
{
public:
    vector<Expression *> *expressionList;

    Expression_list(int, int);

    void AddExpression(Expression *);
    virtual void accept(Visitor *v);
};

/// Var
class Variable : public Node
{
public:
    Id *id;

    Variable(Id *, int, int);
    virtual void accept(Visitor *v);
};

class VariableExpression : public Variable
{
public:
    Expression *expression;

    VariableExpression(Expression *, Id *, int, int);
    virtual void accept(Visitor *v);
};

/*****************************************************************************************/
class Visitor
{
public:
    virtual void Visit(Node *n) = 0;
    virtual void Visit(Program *n) = 0;
    virtual void Visit(Declarations *n) = 0;
    virtual void Visit(Declaration *n) = 0;
    virtual void Visit(DeclarationVar *n) =0 ;
    virtual void Visit(Subprogram_declarations *n) = 0;
    virtual void Visit(Subprogram_declaration *n) = 0;
    virtual void Visit(Statement *n) = 0;
    virtual void Visit(Identifier_list *n) = 0;
    virtual void Visit(Id *n) = 0;
    virtual void Visit(IntNum *n) = 0;
    virtual void Visit(RealNum *n) = 0;
    virtual void Visit(String *n) = 0;
    virtual void Visit(Bool *n) = 0;
    virtual void Visit(Char *n) = 0;
    virtual void Visit(Expression *n) = 0;
    virtual void Visit(IdExpr *n) = 0;
    virtual void Visit(IntNumExpr *n) = 0;
    virtual void Visit(BoolExpr *n) = 0;
    virtual void Visit(RealNumExpr *n) = 0;
    virtual void Visit(StringExpr *n) = 0;
    virtual void Visit(CharExpr *n) = 0;
    virtual void Visit(ListWithExpr *n) = 0;
    virtual void Visit(UnaryExpr *n) = 0;
    virtual void Visit(NotExpr *n) = 0;
    virtual void Visit(BracketExpr *n) = 0;
    virtual void Visit(ExpressionWithExpr *n) = 0;
    virtual void Visit(Type *n) = 0;
    virtual void Visit(Subprogram_head *n) = 0;
    virtual void Visit(Subprogram_variables *n) = 0;
    virtual void Visit(Arguments *n) = 0;
    virtual void Visit(Parameter_list *n) = 0;
    virtual void Visit(Statement_list *n) = 0;
    virtual void Visit(Optional_statement *n) = 0;
    virtual void Visit(VariableExpression *n)=0;
    virtual void Visit(Optional_statementNonEmpty *) = 0;
    virtual void Visit(Compound_statement *n) = 0;
    virtual void Visit(Variable *n) = 0;
    virtual void Visit(Procedure_statement *n) = 0;
    virtual void Visit(Procedure_statementList *n) = 0;
    virtual void Visit(If *n) = 0;
    virtual void Visit(IfElse *n) = 0;
    virtual void Visit(While *n) = 0;
    virtual void Visit(For *n) = 0;
    virtual void Visit(Expression_list *n) = 0;
    virtual void Visit(Unary_operator *n) = 0;
    virtual void Visit(Variable_Expression *n) = 0;
    virtual void Visit(Array_type *n) = 0;
};

class PrintVisitor : public Visitor
{

public:
    string types[8];
    string operators[16];
    PrintVisitor();
    virtual void Visit(Node *);
    virtual void Visit(Program *n);
    virtual void Visit(Declarations *);
    virtual void Visit(Declaration *);
    virtual void Visit(DeclarationVar *n) ;
    virtual void Visit(Array_type *);
    virtual void Visit(Statement *);
    virtual void Visit(Expression_list *);
    virtual void Visit(Identifier_list *);
    virtual void Visit(Id *);
    virtual void Visit(IntNum *);
    virtual void Visit(RealNum *);
    virtual void Visit(String *);
    virtual void Visit(Bool *);
    virtual void Visit(Char *);
    virtual void Visit(Expression *);
    virtual void Visit(IdExpr *);
    virtual void Visit(IntNumExpr *);
    virtual void Visit(BoolExpr *);
    virtual void Visit(RealNumExpr *);
    virtual void Visit(StringExpr *);
    virtual void Visit(CharExpr *);
    virtual void Visit(ListWithExpr *);
    virtual void Visit(UnaryExpr *);
    virtual void Visit(NotExpr *);
    virtual void Visit(BracketExpr *);
    virtual void Visit(ExpressionWithExpr *);
    virtual void Visit(Subprogram_declarations *);
    virtual void Visit(Subprogram_declaration *);
    virtual void Visit(Type *);
    virtual void Visit(Subprogram_head *);
    virtual void Visit(Subprogram_variables *);
    virtual void Visit(Arguments *);
    virtual void Visit(Parameter_list *);
    virtual void Visit(Statement_list *);
    virtual void Visit(Optional_statement *);
    virtual void Visit(Optional_statementNonEmpty *);
    virtual void Visit(Compound_statement *);
    virtual void Visit(Variable *);
    virtual void Visit(Procedure_statement *);
    virtual void Visit(If *);
    virtual void Visit(IfElse *);
    virtual void Visit(While *);
    virtual void Visit(For *);
    virtual void Visit(VariableExpression *n);
    virtual void Visit(Variable_Expression *);
    virtual void Visit(Unary_operator *);
    virtual void Visit(Procedure_statementList *);
};
//////////////////////////Type checker

class TypeChecker : public Visitor
{

public:
    string types[8];
    string operators[16];
    TypeChecker();
    vector<Subprogram_head *> *Subprogram_heads;
    virtual void Visit(Node *);
    virtual void Visit(Program *n);
    virtual void Visit(Declarations *);
    virtual void Visit(Declaration *);
    virtual void Visit(DeclarationVar *n) ;
    virtual void Visit(Subprogram_declarations *);
    virtual void Visit(Subprogram_declaration *);
    virtual void Visit(Statement *);
    virtual void Visit(Expression_list *);
    virtual void Visit(Identifier_list *);
    virtual void Visit(Id *);
    virtual void Visit(IntNum *);
    virtual void Visit(RealNum *);
    virtual void Visit(String *);
    virtual void Visit(Bool *);
    virtual void Visit(Char *);
    virtual void Visit(Expression *);
    virtual void Visit(IdExpr *);
    virtual void Visit(IntNumExpr *);
    virtual void Visit(BoolExpr *);
    virtual void Visit(RealNumExpr *);
    virtual void Visit(StringExpr *);
    virtual void Visit(CharExpr *);
    virtual void Visit(ListWithExpr *);
    virtual void Visit(UnaryExpr *);
    virtual void Visit(NotExpr *);
    virtual void Visit(BracketExpr *);
    virtual void Visit(ExpressionWithExpr *);
    virtual void Visit(Type *);
    virtual void Visit(Subprogram_head *);
    virtual void Visit(Subprogram_variables *);
    virtual void Visit(VariableExpression *n);
    virtual void Visit(Arguments *);
    virtual void Visit(Parameter_list *);
    virtual void Visit(Statement_list *);
    virtual void Visit(Optional_statement *);
    virtual void Visit(Optional_statementNonEmpty *);
    virtual void Visit(Compound_statement *);
    virtual void Visit(Variable *);
    virtual void Visit(Procedure_statement *);
    virtual void Visit(If *);
    virtual void Visit(IfElse *);
    virtual void Visit(While *);
    virtual void Visit(For *);
    virtual void Visit(Unary_operator *);
    virtual void Visit(Procedure_statementList *);
    virtual void Visit(Variable_Expression *);
    virtual void Visit(Array_type *);
};

//////////////////////////Symbol Table

class Symbol
{
public:
    string name;
    int type;
    int kind;
    int first;
    int second;
    int location;
    Subprogram_head *subprogram_head;
    Symbol(string, int, int);
    Symbol(string, int, int, Subprogram_head *);
    Symbol(string, int, int, int, int);
};

class Scope
{
public:
    HashTab *hashTab;
    Scope();
};

class SymbolTable
{
public:
    HashTab *hashTab;
    vector<Scope *> *scopes;
    string kindes[15];
    string types[15];
    Scope *current;
    // Errors *errors;
    SymbolTable();
    bool AddSymbol(Id *, int, Type *type);
    bool AddFunc(Id *id, int kind, Arguments *d, int type, Subprogram_head *);
    // bool AddArray(Id *id, int kind, int first, int second, int type);
    Symbol *LookUp(Id *);
    Symbol *LookUpArray(Id *, int);
    Symbol *LookupConstructor(Id *, Expression_list *);
    void CloseScope();
    void OpenScope();
};
//////////////////////////Code checker

 class CodeVisitor : public Visitor
 {

 public:
     int fp = 0;
     int gp = 1023;
     int cp = 512+1024-1 ;
     string types[8];
     string operators[16];
     vector<Symbol *> *functions;
     CodeVisitor();
     virtual void Visit(Node *);
     virtual void Visit(Program *n);
     virtual void Visit(Declarations *);
     virtual void Visit(Declaration *);
     virtual void Visit(DeclarationVar *n) ;
     virtual void Visit(VariableExpression *n);
     virtual void Visit(Subprogram_declarations *);
     virtual void Visit(Subprogram_declaration *);
     virtual void Visit(Statement *);
     virtual void Visit(Expression_list *);
     virtual void Visit(Identifier_list *);
     virtual void Visit(Id *);
     virtual void Visit(IntNum *);
     virtual void Visit(RealNum *);
     virtual void Visit(String *);
     virtual void Visit(Bool *);
     virtual void Visit(Char *);
     virtual void Visit(Expression *);
     virtual void Visit(IdExpr *);
     virtual void Visit(IntNumExpr *);
     virtual void Visit(BoolExpr *);
     virtual void Visit(RealNumExpr *);
     virtual void Visit(StringExpr *);
     virtual void Visit(CharExpr *);
     virtual void Visit(ListWithExpr *);
     virtual void Visit(UnaryExpr *);
     virtual void Visit(NotExpr *);
     virtual void Visit(BracketExpr *);
     virtual void Visit(ExpressionWithExpr *);
     virtual void Visit(Type *);
     virtual void Visit(Subprogram_head *);
     virtual void Visit(Subprogram_variables *);
     virtual void Visit(Arguments *);
     virtual void Visit(Parameter_list *);
     virtual void Visit(Statement_list *);
     virtual void Visit(Optional_statement *);
     virtual void Visit(Optional_statementNonEmpty *);
     virtual void Visit(Compound_statement *);
     virtual void Visit(Variable *);
     virtual void Visit(Procedure_statement *);
     virtual void Visit(If *);
     virtual void Visit(IfElse *);
     virtual void Visit(While *);
     virtual void Visit(For *);
     virtual void Visit(Unary_operator *);
     virtual void Visit(Procedure_statementList *);
     virtual void Visit(Variable_Expression *);
     virtual void Visit(Array_type *);
     void  generateReadWriteFunction();
 };
