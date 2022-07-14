
#include "ast.h"
#include <algorithm>
extern SymbolTable *symbolTable;

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
Type::Type(int type, int l, int r) : Node(l, r)
{
    this->type = type;
}

Standard_type::Standard_type(int type, int l, int r) : Type(type, l, r)
{
    this->type = type;
}

Array_type::Array_type(IntNum *first, IntNum *last, Standard_type *StandardType, int l, int r) : Type(StandardType->type, l, r)
{
    this->first = first;
    this->last = last;
    this->StandardType = StandardType;
    StandardType->father = this;
    first->father = this;
    last->father = this;
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
    this->symbol = NULL;
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

Optional_statementNonEmpty::Optional_statementNonEmpty(Statement_list *statementList, int l, int r)
    : Optional_statement(statementList, l, r)
{
    this->statementList = statementList;
    statementList->father = this;
    // statementList->father- = this;
    // this->father->
}
Optional_statement::Optional_statement(Statement_list *statementList, int l, int r) : Statement(l, r)
{
    this->statementList = statementList;
}
Variable_Expression::Variable_Expression(Variable *variable, Expression *expression, int l, int r)
    : Statement(l, r)
{
    this->variable = variable;
    this->expression = expression;
    variable->father = this;
    expression->father = this;
}

Procedure_statement::Procedure_statement(Expression_list *expressionList, Id *id, int l, int r)
    : Statement(l, r)
{
    this->expressionList = expressionList;

    this->id = id;
    id->father = this;
}
Procedure_statementList::Procedure_statementList(Expression_list *expressionList, Id *id, int l, int r)
    : Procedure_statement(expressionList, id, l, r)
{
    this->expressionList = expressionList;
    expressionList->father = this;
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
    this->type = 1;
    this->intNum = intNum;
    intNum->father = this;
}

RealNumExpr::RealNumExpr(RealNum *realNum, int l, int r)
    : Expression(l, r)
{
    this->type = 2;

    this->realNum = realNum;
    realNum->father = this;
}

BoolExpr::BoolExpr(Bool *aBool, int l, int r)
    : Expression(l, r)
{
    this->type = 3;

    this->aBool = aBool;
    aBool->father = this;
}

StringExpr::StringExpr(String *aString, int l, int r)
    : Expression(l, r)
{
    this->type = 5;

    this->aString = aString;
    aString->father = this;
}

CharExpr::CharExpr(Char *aChar, int l, int r)
    : Expression(l, r)
{
    this->type = 4;

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

ExpressionWithExpr::ExpressionWithExpr(Expression *expression, int l, int r)
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
Variable::Variable(Id *id, int l, int r)
    : Node(l, r)
{
    this->id = id;
    id->father = this;
}

VariableExpression::VariableExpression(Expression *expression, Id *id, int l, int r)
    : Variable(id, l, r)
{
    this->expression = expression;
    expression->father = this;
}
/////////////////////////////////////////////accept Visitorv->Visit(this);}
void Node::accept(Visitor *v) { v->Visit(this); }
void Variable_Expression::accept(Visitor *v) { v->Visit(this); }
void Procedure_statementList::accept(Visitor *v) { v->Visit(this); }
void VariableExpression::accept(Visitor *v) { v->Visit(this); }
void Function_head::accept(Visitor *v) { v->Visit(this); }
void Procedure_head::accept(Visitor *v) { v->Visit(this); }
void Optional_statementNonEmpty::accept(Visitor *v) { v->Visit(this); }
void Program::accept(Visitor *v) { v->Visit(this); }
void DeclarationVar::accept(Visitor *v) { v->Visit(this); }
void Array_type::accept(Visitor *v) { v->Visit(this); }
void Standard_type::accept(Visitor *v) { v->Visit(this); }
void Subprogram_declaration::accept(Visitor *v) { v->Visit(this); }
void Subprogram_declarations::accept(Visitor *v) { v->Visit(this); }
void Declarations::accept(Visitor *v) { v->Visit(this); }
void Declaration::accept(Visitor *v) { v->Visit(this); }
void Statement::accept(Visitor *v) { v->Visit(this); }
void Expression_list::accept(Visitor *v) { v->Visit(this); }
void Identifier_list::accept(Visitor *v) { v->Visit(this); }
void Id::accept(Visitor *v) { v->Visit(this); }
void IntNum::accept(Visitor *v) { v->Visit(this); }
void RealNum::accept(Visitor *v) { v->Visit(this); }
void String::accept(Visitor *v) { v->Visit(this); }
void Bool::accept(Visitor *v) { v->Visit(this); }
void Char::accept(Visitor *v) { v->Visit(this); }
void Expression::accept(Visitor *v) { v->Visit(this); }
void IdExpr::accept(Visitor *v) { v->Visit(this); }
void IntNumExpr::accept(Visitor *v) { v->Visit(this); }
void BoolExpr::accept(Visitor *v) { v->Visit(this); }
void RealNumExpr::accept(Visitor *v) { v->Visit(this); }
void StringExpr::accept(Visitor *v) { v->Visit(this); }
void CharExpr::accept(Visitor *v) { v->Visit(this); }
void ListWithExpr::accept(Visitor *v) { v->Visit(this); }
void UnaryExpr::accept(Visitor *v) { v->Visit(this); }
void NotExpr::accept(Visitor *v) { v->Visit(this); }
void BracketExpr::accept(Visitor *v) { v->Visit(this); }
void ExpressionWithExpr::accept(Visitor *v) { v->Visit(this); }
void Type::accept(Visitor *v) { v->Visit(this); }
void Compound_statement::accept(Visitor *v) { v->Visit(this); }
void Subprogram_head::accept(Visitor *v) { v->Visit(this); }
void Subprogram_variables::accept(Visitor *v) { v->Visit(this); }
void Arguments::accept(Visitor *v) { v->Visit(this); }
void Parameter_list::accept(Visitor *v) { v->Visit(this); }
void Statement_list::accept(Visitor *v) { v->Visit(this); }
void Optional_statement::accept(Visitor *v) { v->Visit(this); }
void Variable::accept(Visitor *v) { v->Visit(this); }
void Procedure_statement::accept(Visitor *v) { v->Visit(this); }
void If::accept(Visitor *v) { v->Visit(this); }
void IfElse::accept(Visitor *v) { v->Visit(this); }
void While::accept(Visitor *v) { v->Visit(this); }
void For::accept(Visitor *v) { v->Visit(this); }
void Unary_operator::accept(Visitor *v) { v->Visit(this); }
/////////////////////////

// void Visitor::Visit(Node *n) { cout << "this"; }
// void Visitor::Visit(Statement *n) { cout << "this"; }
// void Visitor::Visit(Expression_list *n) { cout << "this"; }
// void Visitor::Visit(Identifier_list *n) { cout << "this"; }
// void Visitor::Visit(Id *n)
// {

//     cout << "this is an ID: " << n->name << endl;
// }
// void Visitor::Visit(IntNum *n) { cout << "this"; }
// void Visitor::Visit(RealNum *n)
// {
//     cout << "this";
// }
// void Visitor::Visit(String *n)
// {
//     cout << "this";
// }
// void Visitor::Visit(Bool *n)
// {
//     cout << "this";
// }
// void Visitor::Visit(Char *n)
// {
//     cout << "this";
// }
// void Visitor::Visit(Expression *n) { cout << "this"; }
// void Visitor::Visit(IdExpr *n) { cout << "this"; }
// void Visitor::Visit(IntNumExpr *n) { cout << "this"; }
// void Visitor::Visit(BoolExpr *n) { cout << "this"; }
// void Visitor::Visit(RealNumExpr *n) { cout << "this"; }
// void Visitor::Visit(StringExpr *n) { cout << "this"; }
// void Visitor::Visit(CharExpr *n) { cout << "this"; }
// void Visitor::Visit(ListWithExpr *n) { cout << "this"; }
// void Visitor::Visit(UnaryExpr *n) { cout << "this"; }
// void Visitor::Visit(NotExpr *n) { cout << "this"; }
// void Visitor::Visit(BracketExpr *n) { cout << "this"; };
// void Visitor::Visit(ExpressionWithExpr *n) { cout << "this"; };
// void Visitor::Visit(Subprogram_declarations *n) { cout << "this"; };
// void Visitor::Visit(Type *n) { cout << "this"; };
// void Visitor::Visit(Compound_statement *n)
// {
//     cout << "this";

//     //   cout << "this is a compound statement: " << n-><< endl;
// }

// void Visitor::Visit(Subprogram_head *n) { cout << "this"; };
// void Visitor::Visit(Subprogram_variables *n) { cout << "this"; };
// void Visitor::Visit(Arguments *n) { cout << "this"; };
// void Visitor::Visit(Parameter_list *n) { cout << "this"; };
// void Visitor::Visit(Statement_list *n) { cout << "this"; };
// void Visitor::Visit(Optional_statement *n) { cout << "this"; };
// void Visitor::Visit(Variable *n) { cout << "this"; };
// void Visitor::Visit(Procedure_statement *n) { cout << "this"; };
// void Visitor::Visit(If *n) { cout << "this"; };
// void Visitor::Visit(IfElse *n) { cout << "this"; };
// void Visitor::Visit(While *n) { cout << "this"; };
// void Visitor::Visit(For *n) { cout << "this"; };
// void Visitor::Visit(Unary_operator *n) { cout << "this"; };
// ////////////////////////////////////////////// Print Visitor
PrintVisitor::PrintVisitor() {}

void PrintVisitor::Visit(Node *n) {}
void PrintVisitor::Visit(Program *n)
{
    cout << " This is a program " << n->id->name << endl;
    n->declarations->accept(this);
    n->subprogramDeclarations->accept(this);
    n->compoundStatement->accept(this);
}
void PrintVisitor::Visit(Declarations *n)
{
    // cout << "This is Declarations-" << endl;
    try
    {
        for (int i = 0; i < (int)(n->declarations->size()); i++)
        {
            n->declarations->at(i)->accept(this);
            if (i != (int)(n->declarations->size() - 1))
                cout << ",";
        }
    }
    catch (std::exception e)
    {
        cout << "";
    }
}
void PrintVisitor::Visit(Declaration *n)
{
    n->identifierList->accept(this);
}
void PrintVisitor::Visit(Subprogram_declarations *n)
{
    try
    {
        for (int i = 0; i < (int)(n->subprogram_declarations->size()); i++)
        {
            n->subprogram_declarations->at(i)->accept(this);
            if (i != (int)(n->subprogram_declarations->size() - 1))
                cout << ",";
        }
    }
    catch (std::exception e)
    {
        cout << "";
    }
}
void PrintVisitor::Visit(Subprogram_declaration *n)
{
    n->subprogramHead->accept(this);
    n->subprogramVariables->accept(this);
    n->compoundStatement->accept(this);
}
void PrintVisitor::Visit(Statement *n)
{
    cout << endl;
}
void PrintVisitor::Visit(Expression_list *n)
{
    // cout << "This is Declarations-" << endl;
    try
    {
        for (int i = 0; i < (int)(n->expressionList->size()); i++)
        {
            n->expressionList->at(i)->accept(this);
            if (i != (int)(n->expressionList->size() - 1))
                cout << ",";
        }
    }
    catch (std::exception e)
    {
        cout << "";
    }
}
void PrintVisitor::Visit(Identifier_list *n)
{
    try
    {
        for (int i = 0; i < (int)(n->Ids->size()); i++)
        {
            n->Ids->at(i)->accept(this);
            if (i != (int)(n->Ids->size() - 1))
                cout << ",";
        }
    }
    catch (std::exception e)
    {
        cout << "";
    }
}
void PrintVisitor::Visit(Id *n)
{

    cout << "this is an ID: " << n->name << endl;
}
void PrintVisitor::Visit(IntNum *n)
{
}
void PrintVisitor::Visit(RealNum *n)
{
    cout << "";
}
void PrintVisitor::Visit(String *n)
{
    cout << "";
}
void PrintVisitor::Visit(Bool *n)
{
    cout << "";
}
void PrintVisitor::Visit(Char *n)
{
    cout << "";
}
void PrintVisitor::Visit(Expression *n)
{
}
void PrintVisitor::Visit(IdExpr *n)
{
    n->id->accept(this);
}
void PrintVisitor::Visit(IntNumExpr *n)
{
    cout << "type: " << types[n->type] << " ,value: " << n->intNum->value << endl;
}
void PrintVisitor::Visit(BoolExpr *n)
{
    cout << "type: " << types[n->type] << " ,value: " << n->aBool->value << endl;
}
void PrintVisitor::Visit(RealNumExpr *n)
{
    cout << "type: " << types[n->type] << " ,value: " << n->realNum->value << endl;
}
void PrintVisitor::Visit(StringExpr *n)
{
    cout << "type: " << types[n->type] << " ,value: " << n->aString->value << endl;
}
void PrintVisitor::Visit(CharExpr *n)
{
    cout << "type: " << types[n->type] << " ,value: " << n->aChar->value << endl;
}
void PrintVisitor::Visit(ListWithExpr *n)
{
    n->id->accept(this);
    n->expressionList->accept(this);
}
void PrintVisitor::Visit(UnaryExpr *n) { cout << ""; }
void PrintVisitor::Visit(NotExpr *n) { cout << ""; }
void PrintVisitor::Visit(BracketExpr *n) { cout << ""; };
void PrintVisitor::Visit(ExpressionWithExpr *n) { cout << ""; };
void PrintVisitor::Visit(Type *n) { cout << ""; };
void PrintVisitor::Visit(Compound_statement *n)
{
    n->optionalStatement->accept(this);
    //   cout << "this is a compound statement: " << n-><< endl;
}

void PrintVisitor::Visit(Subprogram_head *n)
{
    cout << " Subprogram " << n->id->name << endl;
    cout << "Arguments " << endl;
    n->arguments->accept(this);
};
void PrintVisitor::Visit(Subprogram_variables *n)
{
    try
    {
        for (int i = 0; i < (int)(n->subprogramVariables->size()); i++)
        {
            n->subprogramVariables->at(i).first->accept(this);
            if (i != (int)(n->subprogramVariables->size() - 1))
                cout << ",";
        }
    }
    catch (std::exception e)
    {
        cout << "";
    }
};
void PrintVisitor::Visit(Arguments *n)
{
    n->parameterList->accept(this);
};
void PrintVisitor::Visit(Parameter_list *n)
{
    try
    {
        for (int i = 0; i < (int)(n->parameters->size()); i++)
        {
            n->parameters->at(i).first->accept(this);
            if (i != (int)(n->parameters->size() - 1))
                cout << ",";
        }
    }
    catch (std::exception e)
    {
        cout << "";
    }
};
void PrintVisitor::Visit(Statement_list *n)
{
    try
    {
        for (int i = 0; i < (int)(n->statement_list->size()); i++)
        {
            n->statement_list->at(i)->accept(this);
            if (i != (int)(n->statement_list->size() - 1))
                cout << ",";
        }
    }
    catch (std::exception e)
    {
        cout << "";
    }
};
void PrintVisitor::Visit(Optional_statement *n)
{

    n->statementList->accept(this);
};
void PrintVisitor::Visit(Optional_statementNonEmpty *n)
{

    n->statementList->accept(this);
};
void PrintVisitor::Visit(Variable *n)
{
    n->id->accept(this);
};
void PrintVisitor::Visit(Procedure_statement *n)
{
    cout << "procedure: " << n->id->name << endl;
};
void PrintVisitor::Visit(Procedure_statementList *n)
{
    cout << "procedure: " << n->id->name << endl;
};
void PrintVisitor::Visit(If *n)
{
    cout << "If statement " << endl;
    n->expression->accept(this);
    n->thenStatement->accept(this);
};
void PrintVisitor::Visit(IfElse *n)
{
    cout << "If Else statement " << endl;
    n->expression->accept(this);
    n->thenStatement->accept(this);
    n->elseStatement->accept(this);
};
void PrintVisitor::Visit(While *n)
{
    cout << "While statement " << endl;
    n->expression->accept(this);
    n->doStatement->accept(this);
};
void PrintVisitor::Visit(For *n)
{
    cout << "While statement " << endl;
    n->variable->accept(this);
    n->expression->accept(this);
    n->optionalStatement->accept(this);
};
void PrintVisitor::Visit(Unary_operator *n){

};
void PrintVisitor::Visit(Variable_Expression *n){

};

/************************Typechecker****/

bool typechecking_assign(int l, int r)
{
    bool mismatch = false;
    if (l == 1)
    {
        if (r == 1 || r == 2 || r == 3 || r == 4)
            mismatch = false;
        else
            mismatch = true;
    }
    else if (l == 2)
    {
        if (r == 1 || r == 2)
            mismatch = false;
        else
            mismatch = true;
    }
    else if (l == 3)
    {
        if (r == 3)
            mismatch = false;
        else
            mismatch = true;
    }
    else if (l == 4)
    {
        if (r == 4)
            mismatch = false;
        else
            mismatch = true;
    }
    else if (l == 5)
    {
        if (r == 5)
            mismatch = false;
        else
            mismatch = true;
    }
    return mismatch;
}

bool check_mismatch(int l, string op, int r)
{
    bool mis = false;
    if (op == "+")
    {
        if (l == r)
            mis = true;
        else
        {
            if (l == 1 || l == 2)
            {
                if (r != 6 && r != 5)
                    mis = true;
                else
                    mis = false;
            }
            if (l == 3)
            {
                if (r == 4 || r == 5 || r == 6)
                    mis = false;
                else
                    mis = true;
            }
            if (l == 4)
            {
                if (r == 4 || r == 5 || r == 1 || r == 2)
                    mis = true;
                else
                    mis = false;
            }
            if (l == 5)
            {
                if (r == 3 || r == 1 || r == 2 || r == 6)
                    mis = false;
                else
                    mis = true;
            }
            if (l == 6)
            {
                return false;
            }
        }
    }
    else
    {
        if (op == "-")
        {
            if (l == r && l != 5)
                mis = true;
            else
            {
                if (l == 1 || l == 2)
                {
                    if (r != 6 && r != 5)
                        mis = true;
                    else
                        mis = false;
                }
                if (l == 3)
                {
                    if (r == 4 || r == 5 || r == 6)
                        mis = false;
                    else
                        mis = true;
                }
                if (l == 4)
                {
                    if (r == 4 || r == 1 || r == 2)
                        mis = true;
                    else
                        mis = false;
                }
                if (l == 5)
                {
                    mis = false;
                }
                if (l == 6)
                {
                    return false;
                }
            }
        }
        else
        {
            if (op == "*" || op == "/" || op == "div")
            {
                if (l == r && l != 5 && l != 4 && l != 3)
                    mis = true;
                else
                {
                    if (l == 1 || l == 2)
                    {
                        if (r != 6 && r != 5 && l != 4 && l != 3)
                            mis = true;
                        else
                            mis = false;
                    }
                    if (l == 3 || l == 4 || l == 5)
                    {
                        mis = false;
                    }
                    if (l == 6)
                    {
                        return false;
                    }
                }
            }
            else
            {
                if (op == "and" || op == "or" || op == "not")
                {
                    if (l == 3 && r == 3)
                    {
                        mis = true;
                    }
                    else
                        mis = false;
                }
                else
                {
                    if (op == "<>" || op == "=")
                    {
                        if (l == r)
                            mis = true;
                        else
                            mis = false;
                    }
                    else
                    {
                        if (op == ">" || op == "<" || op == "<=" || op == ">=")
                        {
                            if (l == 1 || l == 2)
                            {
                                if (r != 6 && r != 5 && r != 4 && r != 3)
                                    mis = true;
                                else
                                    mis = false;
                            }
                            if (l == 3 || l == 4 || l == 5 || l == 6)
                            {
                                mis = false;
                            }
                        }
                    }
                }
            }
        }
    }

    return mis;
}

int get_type(int l, string op, int r)
{
    // cout << "lklklklkllklklklklklklklklk" << op;
    if (op == "+")
    {
        if (l == r)
            return l;
        else
        {
            if (l == 1)
            {
                if (r == 2)
                    return 2;
                if (r == 3)
                    return 1;
                if (r == 4)
                    return 4;
            }
            if (l == 2)
            {
                if (r == 1)
                    return 2;
                if (r == 3)
                    return 2;
                if (r == 4)
                    return 4;
            }
            if (l == 3)
            {
                if (r == 1)
                    return 1;
                if (r == 2)
                    return 2;
            }
            if (l == 4)
            {
                if (r == 1)
                    return 4;
                if (r == 2)
                    return 4;
                if (r == 5)
                    return 5;
            }
            if (l == 5)
            {
                return 5;
            }
        }
    }
    else
    {
        if (op == "-")
        {
            if (l == 1)
            {
                if (r == 1)
                    return 1;
                if (r == 2)
                    return 2;
                if (r == 3)
                    return 1;
                if (r == 4)
                    return 4;
            }
            if (l == 2)
            {
                if (r == 1)
                    return 2;
                if (r == 2)
                    return 2;
                if (r == 3)
                    return 2;
                if (r == 4)
                    return 4;
            }
            if (l == 3)
            {
                if (r == 1)
                    return 1;
                if (r == 2)
                    return 2;
                if (r == 3)
                    return 3;
            }
            if (l == 4)
            {
                if (r == 1)
                    return 4;
                if (r == 2)
                    return 4;
                if (r == 4)
                    return 4;
                if (r == 5)
                    return 5;
            }
            if (l == 5)
            {
                return 5;
            }
        }
        else
        {
            if (op == "*" || op == "/" || op == "div")
            {
                if (l == 1)
                {
                    if (r == 1)
                        return 1;
                    if (r == 2)
                        return 2;
                }
                if (l == 2)
                {
                    if (r == 1)
                        return 2;
                    if (r == 2)
                        return 2;
                }
            }
            else
            {
                if (op == "=" || op == "<>" || op == ">" || op == "<" || op == "and" || op == "or" || op == "not" || op == "<=" || op == ">=")
                {
                    return 3;
                }
            }
        }
    }
    return 0;
}
//////////////////////////type checker

TypeChecker::TypeChecker()
{
    types[1] = "int";
    types[2] = "real";
    types[3] = "boolean";
    types[4] = "char";
    types[5] = "string";
    types[6] = "null";
    operators[1] = "*";
    operators[2] = "+";
    operators[3] = "-";
    operators[4] = "/";
    operators[5] = "div";
    operators[6] = ">";
    operators[7] = "<=";
    operators[8] = ">";
    operators[9] = ">=";
    operators[10] = "=";
    operators[11] = "<>";
    operators[12] = "not";
    operators[13] = "or";
    operators[14] = "and";
}

void TypeChecker::Visit(Node *n) {}
void TypeChecker::Visit(Program *n)
{
    cout << " This is a program " << n->id->name << endl;
    n->declarations->accept(this);
    n->subprogramDeclarations->accept(this);
    n->compoundStatement->accept(this);
}
void TypeChecker::Visit(Declarations *n)
{
    // cout << "This is Declarations-" << endl;
    try
    {
        for (int i = 0; i < (int)(n->declarations->size()); i++)
        {
            n->declarations->at(i)->accept(this);
            if (i != (int)(n->declarations->size() - 1))
                cout << ",";
        }
    }
    catch (std::exception e)
    {
        cout << "";
    }
}
void TypeChecker::Visit(Declaration *n)
{
    n->identifierList->accept(this);
}
void TypeChecker::Visit(Subprogram_declarations *n)
{
    try
    {
        for (int i = 0; i < (int)(n->subprogram_declarations->size()); i++)
        {
            n->subprogram_declarations->at(i)->accept(this);
            if (i != (int)(n->subprogram_declarations->size() - 1))
                cout << ",";
        }
    }
    catch (std::exception e)
    {
        cout << "";
    }
}
void TypeChecker::Visit(Subprogram_declaration *n)
{
    n->subprogramHead->accept(this);
    n->subprogramVariables->accept(this);
    n->compoundStatement->accept(this);
}
void TypeChecker::Visit(Statement *n)
{
    cout << "bla";
}
void TypeChecker::Visit(Expression_list *n)
{
    // cout << "This is Declarations-" << endl;
    try
    {
        for (int i = 0; i < (int)(n->expressionList->size()); i++)
        {
            n->expressionList->at(i)->accept(this);
            if (i != (int)(n->expressionList->size() - 1))
                cout << ",";
        }
    }
    catch (std::exception e)
    {
        cout << "";
    }
}
void TypeChecker::Visit(Identifier_list *n)
{
    try
    {
        for (int i = 0; i < (int)(n->Ids->size()); i++)
        {
            n->Ids->at(i)->accept(this);
            if (i != (int)(n->Ids->size() - 1))
                cout << ",";
        }
    }
    catch (std::exception e)
    {
        cout << "";
    }
}
void TypeChecker::Visit(Id *n)
{

    cout << "this is an ID: " << n->name << endl;
}
void TypeChecker::Visit(IntNum *n)
{
}
void TypeChecker::Visit(RealNum *n)
{
    cout << "";
}
void TypeChecker::Visit(String *n)
{
    cout << "";
}
void TypeChecker::Visit(Bool *n)
{
    cout << "";
}
void TypeChecker::Visit(Char *n)
{
    cout << "";
}
void TypeChecker::Visit(Expression *n)
{
}
void TypeChecker::Visit(IdExpr *n)
{
    n->type = n->id->symbol->type;
}
void TypeChecker::Visit(IntNumExpr *n)
{
    cout << "type: " << types[n->type] << " ,value: " << n->intNum->value << endl;
    // n->->accept(this);
    int l = n->type;
    if (l != 1)
    {
        cout << "mismatching type on operation ! :"
             << " in line: " << n->line << endl;
        // symbolTable->errors->AddError("mismatching type on operation '!' ", n->line, n->column);
        // symanticerror = true;
        n->type = 6;
        return;
    }
    n->type = 1;
}
void TypeChecker::Visit(BoolExpr *n)
{
    cout << "type: " << types[n->type] << " ,value: " << n->aBool->value << endl;
    int l = n->type;
    if (l != 3)
    {
        cout << "mismatching type on operation ! :"
             << " in line: " << n->line << endl;
        // symbolTable->errors->AddError("mismatching type on operation '!' ", n->line, n->column);
        // symanticerror = true;
        n->type = 6;
        return;
    }
    n->type = 3;
}
void TypeChecker::Visit(RealNumExpr *n)
{
    cout << "type: " << types[n->type] << " ,value: " << n->realNum->value << endl;
    int l = n->type;
    if (l != 2)
    {
        cout << "mismatching type on operation ! :"
             << " in line: " << n->line << endl;
        // symbolTable->errors->AddError("mismatching type on operation '!' ", n->line, n->column);
        // symanticerror = true;
        n->type = 6;
        return;
    }
    n->type = 2;
}
void TypeChecker::Visit(StringExpr *n)
{
    cout << "type: " << types[n->type] << " ,value: " << n->aString->value << endl;
    int l = n->type;
    if (l != 5)
    {
        cout << "mismatching type on operation ! :"
             << " in line: " << n->line << endl;
        // symbolTable->errors->AddError("mismatching type on operation '!' ", n->line, n->column);
        // symanticerror = true;
        n->type = 6;
        return;
    }
    n->type = 5;
}
void TypeChecker::Visit(CharExpr *n)
{
    cout << "type: " << types[n->type] << " ,value: " << n->aChar->value << endl;
    int l = n->type;
    if (l != 4)
    {
        cout << "mismatching type on operation ! :"
             << " in line: " << n->line << endl;
        // symbolTable->errors->AddError("mismatching type on operation '!' ", n->line, n->column);
        // symanticerror = true;
        n->type = 6;
        return;
    }
    n->type = 4;
}
void TypeChecker::Visit(ListWithExpr *n)
{
    cout << "List With expression " << n->id->name << endl;

    n->expressionList->accept(this);

    string key = "Proc" + n->id->name;
    if (n->expressionList)
    {
        for (int i = 0; i < (int)(n->expressionList->expressionList->size()); i++)
        {
            int e = n->expressionList->expressionList->at(i)->type;
            key += "@" + types[e];
        }
    }
    Symbol *temp = symbolTable->current->hashTab->GetMember(key);
    if (temp == NULL)
    {
        string key = "F" + n->id->name;
        if (n->expressionList)
        {
            for (int i = 0; i < (int)(n->expressionList->expressionList->size()); i++)
            {
                int e = n->expressionList->expressionList->at(i)->type;
                key += "@" + types[e];
            }
        }
        else
        {
            cout << "no such Procedure/function exists : " << n->id->name << " " << n->id->line;
            // symbolTable->errors->AddError("no such function exists : " + n->name->name, n->name->line, 0);
            // symanticerror = true;
        }
    }
    else
    {
        n->id->symbol->type = temp->type;
        //  n-> = temp->function;
    }
}
void TypeChecker::Visit(UnaryExpr *n)
{
    int op = n->unaryOperator->index;
    // cout << endl
    //      << "******" << endl
    //      << operators[op] << endl;
    n->leftExpression->accept(this);
    n->rightExpression->accept(this);
    bool t = check_mismatch(n->leftExpression->type, operators[op], n->rightExpression->type);
    if (t)
    {
        int x = get_type(n->leftExpression->type, operators[op], n->rightExpression->type);
        n->type = x;
    }
    else
    {
        cout << "mismatching type on expr " << operators[op] << " expr :"
             << " in line: " << n->line << endl;
        // symbolTable->errors->AddError("mismatching type on expr " + operators[op] + " expr ", n->line, n->column);
        // symanticerror = true;
        n->type = 6;
    }
    // cout << "ended";
}
void TypeChecker::Visit(NotExpr *n) { cout << ""; }
void TypeChecker::Visit(BracketExpr *n) { cout << ""; };
void TypeChecker::Visit(ExpressionWithExpr *n) { cout << ""; };
void TypeChecker::Visit(Type *n) { cout << ""; };
void TypeChecker::Visit(Compound_statement *n)
{
    n->optionalStatement->accept(this);
    //   cout << "this is a compound statement: " << n-><< endl;
}

void TypeChecker::Visit(Subprogram_head *n)
{
    cout << " Subprogram " << n->id->name << endl;
    cout << "Arguments " << endl;
    n->arguments->accept(this);
};
void TypeChecker::Visit(Subprogram_variables *n)
{
    try
    {
        for (int i = 0; i < (int)(n->subprogramVariables->size()); i++)
        {
            n->subprogramVariables->at(i).first->accept(this);
            if (i != (int)(n->subprogramVariables->size() - 1))
                cout << ",";
        }
    }
    catch (std::exception e)
    {
        cout << "";
    }
};
void TypeChecker::Visit(Arguments *n)
{
    n->parameterList->accept(this);
};
void TypeChecker::Visit(Parameter_list *n)
{
    try
    {
        for (int i = 0; i < (int)(n->parameters->size()); i++)
        {
            n->parameters->at(i).first->accept(this);
            if (i != (int)(n->parameters->size() - 1))
                cout << ",";
        }
    }
    catch (std::exception e)
    {
        cout << "";
    }
};
void TypeChecker::Visit(Statement_list *n)
{
    try
    {
        for (int i = 0; i < (int)(n->statement_list->size()); i++)
        {

            n->statement_list->at(i)->accept(this);
            if (i != (int)(n->statement_list->size() - 1))
                cout << ",";
            // }
        }
    }
    catch (std::exception e)
    {
        cout << "";
    }
};
void TypeChecker::Visit(Optional_statement *n)
{
    // cout << "**************************************" << endl;
    if (n->statementList != NULL)
    {
        // cout << "^^^^^^^^^^^^^^^";

        n->statementList->accept(this);
    }
};
void TypeChecker::Visit(Optional_statementNonEmpty *n)
{

    n->statementList->accept(this);
};
void TypeChecker::Visit(Variable *n)
{
    n->id->accept(this);
};
void TypeChecker::Visit(Procedure_statement *n)
{
    if (n->expressionList == NULL)
    {
        cout << "procedure: " << n->id->name << endl;
    }
};
void TypeChecker::Visit(If *n)
{
    cout << "If statement " << endl;
    n->expression->accept(this);
    n->thenStatement->accept(this);
};
void TypeChecker::Visit(IfElse *n)
{
    cout << "If Else statement " << endl;
    n->expression->accept(this);
    n->thenStatement->accept(this);
    n->elseStatement->accept(this);
};
void TypeChecker::Visit(While *n)
{
    cout << "While statement " << endl;
    n->expression->accept(this);
    n->doStatement->accept(this);
};
void TypeChecker::Visit(For *n)
{
    cout << "While statement " << endl;
    n->variable->accept(this);
    n->expression->accept(this);
    n->optionalStatement->accept(this);
    int l = n->variable->id->symbol->type;
    int r = n->expression->type;
    // cout << l << "hkhk" << r << endl;
    bool t = typechecking_assign(l, r);
    if (t)
    {
        // cout << "jkljljljl";
        cout << "mismatching assignment of var :" << n->variable->id->name << " in line: " << n->line << endl;
        // symbolTable->errors->AddError("mismatching assignment of var :" + n->name->name, n->line, n->column);
        // symanticerror = true;
    }
};
void TypeChecker::Visit(Unary_operator *n){

};
void TypeChecker::Visit(Variable_Expression *n)
{
    n->variable->accept(this);
    n->expression->accept(this);
    int l = n->variable->id->symbol->type;
    int r = n->expression->type;
    // cout << l << "hkhk" << r << endl;
    bool t = typechecking_assign(l, r);
    if (t)
    {
        cout << "mismatching assignment of var :" << n->variable->id->name << " in line: " << n->line << endl;
        // symbolTable->errors->AddError("mismatching assignment of var :" + n->name->name, n->line, n->column);
        // symanticerror = true;
    }
};
void TypeChecker::Visit(Procedure_statementList *n)
{
    cout << "Procedure_statementList  " << n->id->name << endl;

    string key = "Proc" + n->id->name;
    if (n->expressionList)
    {
        cout << " { ";
        for (int i = 0; i < (int)(n->expressionList->expressionList->size()); i++)
        {
            int e = n->expressionList->expressionList->at(i)->type;
            cout << " type : " << types[e] << ";";
            key += "@" + types[e];
        }
        cout << " } " << endl;
    }

    Symbol *temp = symbolTable->current->hashTab->GetMember(key);

    if (temp == NULL)
    {

        temp = symbolTable->scopes->at(1)->hashTab->GetMember(key);
        if (temp == NULL)
        {
            string key = "F" + n->id->name;
            if (n->expressionList)
            {

                for (int i = 0; i < (int)(n->expressionList->expressionList->size()); i++)
                {
                    int e = n->expressionList->expressionList->at(i)->type;

                    key += "@" + types[e];
                }
                Symbol *temp = symbolTable->current->hashTab->GetMember(key);
                if (temp == NULL)
                {
                    temp = symbolTable->scopes->at(1)->hashTab->GetMember(key);
                    if (temp == NULL)
                    {
                        cout << "no such Procedure/function exists : " << n->id->name << " " << n->id->line << endl;
                        //++++++++++++++++++++++++++++++++
                    }
                }
            }
        }
    }
    else
    {
        // n->type = n->id->symbol->type;
    }
};
//////////////////////////////////

//////////////////Symbol table

/****************************************/
Symbol::Symbol(string name, int kind, int type)
{
    this->name = name;
    this->kind = kind;
    this->type = type;
}

Symbol::Symbol(string name, int kind, int type, Subprogram_head *f)
{
    this->name = name;
    this->kind = kind;
    this->type = type;
    this->subprogram_head = f;
}

Scope::Scope()
{
    this->hashTab = new HashTab();
    // this->children = new vector<Scope *>;
}

SymbolTable::SymbolTable()
{

    this->scopes = new vector<Scope *>;
    this->scopes->push_back(new Scope());
    // this->errors = new Errors();
    this->current = this->scopes->at(0);
    kindes[1] = "F";
    kindes[2] = "GV";
    kindes[3] = "LV";
    kindes[4] = "Prog";
    kindes[5] = "Proc";
    types[1] = "int";
    types[2] = "float";
    types[3] = "boolean";
    types[4] = "char";
    types[5] = "string";
    types[6] = "null";
}

bool SymbolTable::AddSymbol(Id *id, int kind, int type)
{
    Symbol *sym = new Symbol(id->name, kind, type);
    string key = kindes[kind] + id->name;
    // cout << endl
    //      << key << endl;
    // getIndex(this->scopes, this->current);
    Symbol *temp = this->current->hashTab->GetMember(key);
    if (temp == NULL)
    {
        this->current->hashTab->AddKey(key, sym);
        id->symbol = sym;
        return true;
    }
    else
    {
        cout << " redifined variable : " << id->name << " in line: " << id->line << endl;
        // symbolTable->errors->AddError("redifined variable : " + id->name, id->line, 0);
        // symanticerror = true;
        return false;
    }
    // return NULL;
}
bool SymbolTable::AddFunc(Id *id, int kind, Arguments *d, int type, Subprogram_head *f)
{
    Symbol *sym = new Symbol(id->name, kind, type, f);
    string key = kindes[kind] + id->name;

    if (d)
    {
        for (int i = 0; i < (int)(d->parameterList->parameters->size()); i++)
        {
            int e = d->parameterList->parameters->at(i).second->type;
            key += "@" + types[e];
        }
    }

    cout << id->name << " in line: " << id->line << "Key: " << key << endl;
    Symbol *temp = this->current->hashTab->GetMember(key);

    if (temp == NULL)
    {
        this->current->hashTab->AddKey(key, sym);
        id->symbol = sym;
        return true;
    }
    else
    {
        cout << " redifined function : " << id->name << " in line: " << id->line << endl;
        // symbolTable->errors->AddError("redifined function : " + id->name, id->line, 0);

        // symanticerror = true;
        return false;
    }
}

Symbol *SymbolTable::LookUp(Id *id)
{
    string key;
    Symbol *sym;

    key = kindes[3] + id->name;
    // cout << key;
    sym = this->current->hashTab->GetMember(key);
    if (sym != NULL)
    {
        id->symbol = sym;
        return sym;
    }
    else
    {
        key = kindes[2] + id->name;
        // cout << key;
        sym = this->current->hashTab->GetMember(key);
        if (sym != NULL)
        {
            id->symbol = sym;
            return sym;
        }
        else
        {
            key = kindes[2] + id->name;
            // cout << this->scopes->size();

            sym = this->scopes->at(1)->hashTab->GetMember(key);
            if (sym != NULL)
            {
                id->symbol = sym;
                return sym;
            }
            else
            {
                cout << " undefined variable: " << id->name << " in line: " << id->line << endl;
                //  symbolTable->errors->AddError("undifined variable : " + id->name, id->line, 0);

                //  symanticerror = true;
                return NULL;
            }
        }
    }
}

// Symbol *SymbolTable::LookupConstructor(Id *id, Expression_list *d)
// {
//     string key;
//     Symbol *sym;
//     key = kindes[5] + id->name;
//     sym = this->scopes->at(0)->hashTab->GetMember(key);
//  if (d)
//     {
//         for (int i = 0; i < (int)(d->parameterList->parameters->size()); i++)
//         {
//             int e = d->parameterList->parameters->at(i).second->type;
//             key += "@" + types[e];
//         }
//     }
//     // sym = this->current->hashTab->GetMember(key);
//     if (sym != NULL)
//     {
//         id->symbol = sym;
//         return sym;
//     }
//     else
//     {
//         key = kindes[1] + id->name;
//         // sym = this->current->hashTab->GetMember(key);

//         sym = this->scopes->at(0)->hashTab->GetMember(key);
//         if (sym != NULL)
//         {
//             id->symbol = sym;
//             return sym;
//         }
//         else
//         {
//             cout << " undefined function/procedure constrcutor in line: " << id->line << endl;
//             // symbolTable->errors->AddError("undefined class constrcutor ", id->line, 0);

//             //   symanticerror = true;
//             return NULL;
//         }
//     }
// }

void SymbolTable::OpenScope()
{
    this->scopes->push_back(new Scope());
    this->current = this->scopes->at(this->scopes->size() - 1);
    // cout << ":" << endl;
}

void SymbolTable::CloseScope()
{
    this->scopes->pop_back();
    this->current = this->scopes->at(this->scopes->size() - 1);

    // cout << "cc" << endl;
}
///////////////////////////let's
// void getIndex(vector<Scope *> v, Scope K)
// {
//     auto it = find(v.begin(), v.end(), K);

//     // If element was found
//     if (it != v.end())
//     {

//         // calculating the index
//         // of K
//         int index = it - v.begin();
//         cout << index << endl;
//     }
//     else
//     {
//         // If the element is not
//         // present in the vector
//         cout << "-1" << endl;
//     }
// }