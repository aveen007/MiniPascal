#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using std::cout;
using std::endl;

class Declarations;

class Statement;

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

class Node
{
public:
    int line;
    int column;
    Node *father;

    Node(int, int);
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
};

class Subprogram_declarations : public Node
{
public:
    vector<Subprogram_declaration *> *subprogram_declarations;

    Subprogram_declarations(int, int);

    void AddSubprogramDeclaration(Subprogram_declaration *);
};

/// Type
class Type : public Node
{
public:
    Type(int, int);
};

class Standard_type : public Type
{
public:
    int type; // 1 integer, 2 Real, 3 Boolean
    Standard_type(int, int, int);
};

class Array_type : public Type
{
public:
    IntNum *first;
    IntNum *last;
    Standard_type *StandardType;

    Array_type(IntNum *, IntNum *, Standard_type *, int, int);
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
};

/// Declarations
class Declaration : public Node
{
public:
    Identifier_list *identifierList;

    Declaration(Identifier_list *, int, int);
};

class DeclarationVar : public Declaration
{
public:
    Type *type;

    DeclarationVar(Identifier_list *, Type *, int, int);
};

class Declarations : public Node
{
public:
    vector<Declaration *> *declarations;

    Declarations(int, int);

    void AddDeclaration(Declaration *);
};

// From Here----------------somar
/// INTNUM
// class IntNum :
/// Id
class Id : public Node
{
public:
    string name;

    Id(string, int, int);
};

class IntNum : public Node
{
public:
    int value;

    IntNum(int, int, int);
};

class RealNum : public Node
{
public:
    double value;

    RealNum(double, int, int);
};

class String : public Node
{
public:
    string value;

    String(string, int, int);
};

class Char : public Node
{
public:
    char value;

    Char(char, int, int);
};

class Bool : public Node
{
public:
    bool value;

    Bool(bool, int, int);
};

class Identifier_list : public Node
{
public:
    vector<Id *> *Ids;

    Identifier_list(int, int);

    void AddId(Id *);
};

class Subprogram_variables : public Node
{
public:
    vector<pair<Identifier_list *, Type *>> *subprogramVariables;

    Subprogram_variables(int, int);

    void AddVar(Identifier_list *, Type *);
};

class Subprogram_head : public Node
{
public:
    Id *id;
    Arguments *arguments;

    Subprogram_head(Id *, Arguments *, int, int);
};

class Function_head : public Subprogram_head
{
public:
    Standard_type *standardType;

    Function_head(Id *, Arguments *, Standard_type *, int, int);
};

class Procedure_head : public Subprogram_head
{
public:
    Procedure_head(Id *, Arguments *, int, int);
};

class Arguments : public Node
{
public:
    Parameter_list *parameterList;

    Arguments(Parameter_list *, int, int);
};

class Parameter_list : public Node
{
public:
    vector<pair<Identifier_list *, Type *>> *parameters;

    Parameter_list(int, int);

    void AddParameter(Identifier_list *, Type *);
};

/// ---------------------------- Ghaffar
class Statement : public Node
{
public:
    Statement(int, int);
};

class Compound_statement : public Statement
{
public:
    Optional_statement *optionalStatement;

    Compound_statement(Optional_statement *, int, int);
};
class Optional_statement : public Statement
{
public:
    Optional_statement(int, int);
};
class Optional_statementNonEmpty : public Optional_statement
{
public:
    Statement_list *statementList;

    Optional_statementNonEmpty(Statement_list *, int, int);
};


class Empty_optional_statement : public Optional_statement
{
public:
    Empty_optional_statement(int, int);
};

class Variable_Expression : public Statement
{
public:
    Variable *variable;
    Expression *expression;

    Variable_Expression(Variable *, Expression *, int, int);
};

class Procedure_statement : public Statement
{
public:
    Id *id;
    Procedure_statement(Id *, int, int);
};
class Procedure_statementList : public Procedure_statement
{
public:
    Expression_list *expressionList;
    Procedure_statementList(Expression_list *, Id *, int, int);
};
class If : public Statement
{
public:
    Expression *expression;
    Statement *thenStatement;

    If(Expression *, Statement *, int, int);
};

class IfElse : public Statement
{
public:
    Expression *expression;
    Statement *thenStatement;
    Statement *elseStatement;

    IfElse(Expression *, Statement *, Statement *, int, int);
};

class While : public Statement
{
public:
    Expression *expression;
    Statement *doStatement;

    While(Expression *, Statement *, int, int);
};

class For : public Statement
{
public:
    Variable *variable;
    Expression *expression;
    Optional_statement *optionalStatement;

    For(Variable *, Expression *, Optional_statement *, int, int);
};

class Statement_list : public Node
{
public:
    vector<Statement *> *statement_list;

    Statement_list(int, int);

    void AddStatement(Statement *);
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
};

class IdExpr : public Expression
{
public:
    Id *id;

    IdExpr(Id *, int, int);
};

class IntNumExpr : public Expression
{
public:
    IntNum *intNum;

    IntNumExpr(IntNum *, int, int);
};

class RealNumExpr : public Expression
{
public:
    RealNum *realNum;

    RealNumExpr(RealNum *, int, int);
};

class BoolExpr : public Expression
{
public:
    Bool *aBool;

    BoolExpr(Bool *, int, int);
};

class StringExpr : public Expression
{
public:
    String *aString;

    StringExpr(String *, int, int);
};

class CharExpr : public Expression
{
public:
    Char *aChar;

    CharExpr(Char *, int, int);
};

class ListWithExpr : public Expression
{
public:
    Id *id;
    Expression_list *expressionList;

    ListWithExpr(Id *, Expression_list *, int, int);
};

class ExpressionWithExpr : public Expression
{
public:
    Expression *expression;

    ExpressionWithExpr(Expression *, int, int);
};

class UnaryExpr : public Expression
{
public:
    Expression *leftExpression;
    Unary_operator *unaryOperator;
    Expression *rightExpression;

    UnaryExpr(Expression *, Unary_operator *, Expression *, int, int);
};

class NotExpr : public Expression
{
public:
    Expression *expression;

    NotExpr(Expression *, int, int);
};

class BracketExpr : public Expression
{
public:
    Id *id;
    Expression *expression;

    BracketExpr(Id *, Expression *, int, int);
};

/// UOperator
class Unary_operator : public Node
{
public:
    int index;

    Unary_operator(int, int, int);
};

class Expression_list : public Node
{
public:
    vector<Expression *> *expressionList;

    Expression_list(int, int);

    void AddExpression(Expression *);
};

/// Var
class Variable : public Node
{
public:
    Id *id;

    Variable(Id *, int, int);
};

class VariableExpression : public Variable
{
public:
    Expression *expression;

    VariableExpression(Expression *, Id *, int, int);
};