
#include "ast.h"

/// Node
Node::Node(int line, int column)
{
    this->line = line;
    this->column = column;
    this->father = NULL;
}

/// Program
Program::Program(Id *id, Declarations *declarations,
                 Subprogram_declarations *subprogramDeclarations,
                 Compound_statement *compoundStatement,
                 int l, int c) : Node(l, c)
{
    this->id = id;
    this->declarations = declarations;
    this->subprogramDeclarations = subprogramDeclarations;
    this->compoundStatement = compoundStatement;
    id->father = this;
    declarations->father = this;
    subprogramDeclarations->father = this;
    compoundStatement->father = this;
}

/// Declarations
Declaration::Declaration(Identifier_list *identifierList, int l, int r)
    : Node(l, r)
{
    this->identifierList = identifierList;
    identifierList->father = this;
}

DeclarationVar::DeclarationVar(Identifier_list *identifierList, Type *type, int l, int r)
    : Declaration(identifierList, l, r)
{
    this->type = type;
    type->father = this;
}

Declarations::Declarations(int l, int r) : Node(l, r)
{
    this->declarations = new vector<Declaration *>();
}

void Declarations::AddDeclaration(Declaration *declaration)
{
    this->declarations->push_back(declaration);
    declaration->father = this;
}

/// Type
Type::Type(int l, int r) : Node(l, r)
{
}

Standard_type::Standard_type(int type, int l, int r) : Type(l, r)
{
    this->type = type;
}

Array_type::Array_type(IntNum * first, IntNum * last, Standard_type *StandardType, int l, int r) : Type(l, r)
{
    this->first = first;
    this->last = last;
    this->StandardType = StandardType;
    StandardType->father = this;
    first->father = this ;
    last->father = this ;
}

/// subprogram_declarations
Subprogram_declaration::Subprogram_declaration(Subprogram_head *subprogramHead,
                                               Subprogram_variables *subprogramVariables,
                                               Compound_statement *compoundStatement,
                                               int l, int r) : Node(l, r)
{
    this->subprogramHead = subprogramHead;
    this->subprogramVariables = subprogramVariables;
    this->compoundStatement = compoundStatement;
    subprogramHead->father = this;
    subprogramVariables->father = this;
    compoundStatement->father = this;
}

Subprogram_declarations::Subprogram_declarations(int l, int r) : Node(l, r)
{
    this->subprogram_declarations = new vector<Subprogram_declaration *>();
}

void Subprogram_declarations::AddSubprogramDeclaration(Subprogram_declaration *subprogramDeclaration)
{
    this->subprogram_declarations->push_back(subprogramDeclaration);
    subprogramDeclaration->father = this;
}

// From Here--------------------somar
Id::Id(string name, int l, int r) : Node(l, r)
{
    this->name = name;
}

IntNum::IntNum(int value, int l, int r)
    : Node(l, r)
{
    this->value = value;
}

RealNum::RealNum(double value, int l, int r)
    : Node(l, r)
{
    this->value = value;
}

String::String(string value, int l, int r)
    : Node(l, r)
{
    this->value = value;
}

Char::Char(char value, int l, int r)
    : Node(l, r)
{
    this->value = value;
}

Bool::Bool(bool value, int l, int r)
    : Node(l, r)
{
    this->value = value;
}

Identifier_list::Identifier_list(int l, int r) : Node(l, r)
{
    this->Ids = new vector<Id *>();
}

void Identifier_list::AddId(Id *id)
{
    this->Ids->push_back(id);
    id->father = this;
}

Subprogram_variables::Subprogram_variables(int l, int r) : Node(l, r)
{
    this->subprogramVariables = new vector<pair<Identifier_list *, Type *>>();
}

void Subprogram_variables::AddVar(Identifier_list *identifierList, Type *type)
{
    this->subprogramVariables->push_back({identifierList, type});
    identifierList->father = this;
    type->father = this;
}

Subprogram_head::Subprogram_head(Id *id, Arguments *arguments, int l, int r) : Node(l, r)
{
    this->id = id;
    this->arguments = arguments;
    id->father = this;
    arguments->father = this;
}

Function_head::Function_head(Id *id, Arguments *arguments, Standard_type *standardType, int l, int r)
    : Subprogram_head(id, arguments, l, r)
{
    this->standardType = standardType;
    standardType->father = this;
}

Procedure_head::Procedure_head(Id *id, Arguments *arguments, int l, int r)
    : Subprogram_head(id, arguments, l, r)
{
}

Arguments::Arguments(Parameter_list *ParameterList, int l, int r) : Node(l, r)
{
    this->parameterList = ParameterList;
    ParameterList->father = this;
}

Parameter_list::Parameter_list(int l, int r) : Node(l, r)
{
    this->parameters = new vector<pair<Identifier_list *, Type *>>();
}

void Parameter_list::AddParameter(Identifier_list *identifierList, Type *type)
{
    this->parameters->push_back({identifierList, type});
    identifierList->father = this;
    type->father = this;
}

/// ------------------------------------ Ghaffar
/// Statement
Statement::Statement(int l, int r) : Node(l, r){};

Compound_statement::Compound_statement(Optional_statement *optionalStatement, int l, int r)
    : Statement(l, r)
{
    this->optionalStatement = optionalStatement;
    optionalStatement->father = this;
}

Optional_statement::Optional_statement(Statement_list *statementList, int l, int r)
    : Statement(l, r)
{
    this->statementList = statementList;
    statementList->father = this;
}

Empty_optional_statement::Empty_optional_statement(int l, int r) : Statement(l, r){};

Variable_Expression::Variable_Expression(Variable *variable, Expression *expression, int l, int r)
    : Statement(l, r)
{
    this->variable = variable;
    this->expression = expression;
    variable->father = this;
    expression->father = this;
}

Procedure_statement::Procedure_statement(Id *id, int l, int r)
    : Statement(l, r)
{
    this->id = id;
    id->father = this;
}
Procedure_statementList::Procedure_statementList(Expression_list * expressionList, Id * id, int l, int r)
: Procedure_statement(id , l , r)
{
    this->expressionList = expressionList ;
    expressionList->father = this ;
}

If::If(Expression *expression, Statement *thenStatement, int l, int r)
    : Statement(l, r)
{
    this->expression = expression;
    this->thenStatement = thenStatement;
    expression->father = this;
    thenStatement->father = this;
}

IfElse::IfElse(Expression *expression, Statement *thenStatement, Statement *elseStatement, int l, int r)
    : Statement(l, r)
{
    this->expression = expression;
    this->thenStatement = thenStatement;
    this->elseStatement = elseStatement;
    expression->father = this;
    thenStatement->father = this;
    elseStatement->father = this;
}

While::While(Expression *expression, Statement *doStatement, int l, int r)
    : Statement(l, r)
{
    this->expression = expression;
    this->doStatement = doStatement;
    expression->father = this;
    doStatement->father = this;
}

For::For(Variable *variable, Expression *expression, Optional_statement *optionalStatement, int l, int r)
    : Statement(l, r)
{
    this->variable = variable;
    this->expression = expression;
    this->optionalStatement = optionalStatement;
    variable->father = this;
    expression->father = this;
    optionalStatement->father = this;
}

/// Statement list
Statement_list::Statement_list(int l, int r)
    : Node(l, r)
{
    this->statement_list = new vector<Statement *>();
};

void Statement_list::AddStatement(Statement *statement)
{
    this->statement_list->push_back(statement);
    statement->father = this;
}

/// Expressions
Expression::Expression(int l, int r)
    : Node(l, r)
{
}

IdExpr::IdExpr(Id *id, int l, int r)
    : Expression(l, r)
{
    this->id = id;
    id->father = this;
}

IntNumExpr::IntNumExpr(IntNum *intNum, int l, int r)
    : Expression(l, r)
{
    this->intNum = intNum;
    intNum->father = this;
}

RealNumExpr::RealNumExpr(RealNum *realNum, int l, int r)
    : Expression(l, r)
{
    this->realNum = realNum;
    realNum->father = this;
}

BoolExpr::BoolExpr(Bool *aBool, int l, int r)
    : Expression(l, r)
{
    this->aBool = aBool;
    aBool->father = this;
}

StringExpr::StringExpr(String *aString, int l, int r)
    : Expression(l, r)
{
    this->aString = aString;
    aString->father = this;
}

CharExpr::CharExpr(Char *aChar, int l, int r)
    : Expression(l, r)
{
    this->aChar = aChar;
    aChar->father = this;
}

ListWithExpr::ListWithExpr(Id *id, Expression_list *expressionList, int l, int r)
    : Expression(l, r)
{
    this->id = id;
    this->expressionList = expressionList;
    expressionList->father = this;
    id->father = this;
}

ExpressionWithExpr::ExpressionWithExpr(Expression *expression, int index, int l, int r)
    : Expression(l, r)
{
    this->expression = expression;
    expression->father = this;
}

UnaryExpr::UnaryExpr(Expression *LExpression, Unary_operator *unaryOperator, Expression *RExpression,
                     int l, int r)
    : Expression(l, r)
{
    this->leftExpression = LExpression;
    this->unaryOperator = unaryOperator;
    this->rightExpression = RExpression;
    LExpression->father = this;
    unaryOperator->father = this;
    RExpression->father = this;
}

NotExpr::NotExpr(Expression *expression, int l, int r)
    : Expression(l, r)
{
    this->expression = expression;
    expression->father = this;
}

BracketExpr::BracketExpr(Id *id, Expression *expression, int l, int r)
    : Expression(l, r)
{
    this->id = id;
    this->expression = expression;
    id->father = this;
    expression->father = this;
}

Unary_operator::Unary_operator(int index, int l, int r)
    : Node(l, r)
{
    this->index = index;
}

Expression_list::Expression_list(int l, int r)
    : Node(l, r)
{
    this->expressionList = new vector<Expression *>();
}

void Expression_list::AddExpression(Expression *expression)
{
    this->expressionList->push_back(expression);
    expression->father = this;
}

/// Var
Variable::Variable(Id * id, int l, int r)
    : Node(l, r)
{
    this->id = id;
    id->father = this ;
}

VariableExpression::VariableExpression(Expression *expression, Id * id , int l, int r)
    : Variable(id, l, r)
{
    this->expression = expression;
    expression->father = this;
}
