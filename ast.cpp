
#include "ast.h"
#include <algorithm>
extern SymbolTable *symbolTable;
extern int whileLabel = 0 ;
extern int ifLabel = 0;
extern int ifElseLabel = 0 ;
extern int forLabel = 0;
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
    this->first = NULL;
    this->second = NULL;
}
Type::Type(int type, int l, int r, int first, int second) : Node(l, r)
{
    this->type = type;
    this->first = first;
    this->second = second;
}
Standard_type::Standard_type(int type, int l, int r) : Type(type, l, r)
{
    this->type = type;
}

Array_type::Array_type(IntNum *first, IntNum *last, Standard_type *StandardType, int l, int r) : Type(StandardType->type, l, r, first->value, last->value)
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
    this->CG_visited = false ;
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

Assignment_statement::Assignment_statement(int l, int r) : Statement(l, r){};

AssignmentIdStatement::AssignmentIdStatement(Id *id, Expression *expression, int l, int r)
    : Assignment_statement(l, r)
{
    this->id = id;
    this->expression = expression;
    id->father = this;
    expression->father = this;
}
AssignmentArrayStatement::AssignmentArrayStatement(Id *id, Expression *index, Expression *expression, int l, int r)
    : Assignment_statement(l, r)
{
    this->id = id;
    this->index = index;
    this->expression = expression;
    id->father = this;
    index->father = this;
    expression->father = this;
}
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
    this->CG_visited = false;
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
For::For(Variable *variable, Expression *down, Expression *up, Optional_statement *optionalStatement, int l, int r)
    : Statement(l, r)
{
    this->variable = variable;
    this->down = down;
    this->up = up;
    this->optionalStatement = optionalStatement;
    variable->father = this;
    up->father = this;
    down->father = this;
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
void Variable_Expression::accept(Visitor *v) { v->Visit(this); }

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
void PrintVisitor::Visit(DeclarationVar *n)
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
    cout << "bla";
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
    cout << n->type;
}
void PrintVisitor::Visit(IdExpr *n)
{
    n->type = n->id->symbol->type;
}
void PrintVisitor::Visit(IntNumExpr *n)
{
    cout << "type: " << types[n->type] << " ,value: " << n->intNum->value << endl;
    // n->->accept(this);
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
    cout << "List With expression " << n->id->name << endl;
    n->expressionList->accept(this);
}
void PrintVisitor::Visit(UnaryExpr *n)
{

    n->leftExpression->accept(this);
    n->rightExpression->accept(this);
}
void PrintVisitor::Visit(NotExpr *n) { cout << ""; }
void PrintVisitor::Visit(BracketExpr *n)
{
    n->expression->accept(this);
    n->type = n->id->symbol->type;
    cout<<"Value is here "<<endl;
};
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
void PrintVisitor::Visit(VariableExpression *n)
{}
void PrintVisitor::Visit(Statement_list *n)
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
void PrintVisitor::Visit(Optional_statement *n)
{
    // cout << "**************************************" << endl;
    if (n->statementList != NULL)
    {
        // cout << "^^^^^^^^^^^^^^^";

        n->statementList->accept(this);
    }
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
    if (n->expressionList == NULL)
    {
        cout << "procedure: " << n->id->name << endl;
    }
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
    cout << "For statement " << endl;
    n->variable->accept(this);
    n->down->accept(this);
    n->up->accept(this);
    n->optionalStatement->accept(this);
};
void PrintVisitor::Visit(Unary_operator *n){

};
void PrintVisitor::Visit(Variable_Expression *n)
{
    n->variable->accept(this);
    n->expression->accept(this);
};
void PrintVisitor::Visit(Procedure_statementList *n)
{
    cout << "statementList  " << n->id->name << endl;
    n->expressionList->accept(this);
};
void PrintVisitor::Visit(Array_type *n){

};
//////////////////////////////////

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
void TypeChecker::Visit(VariableExpression *n)
{}
void TypeChecker::Visit(Program *n)
{

    n->declarations->accept(this);
    n->subprogramDeclarations->accept(this);
    n->compoundStatement->accept(this);
}
void TypeChecker::Visit(Declarations *n)
{

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
void TypeChecker::Visit(DeclarationVar *n)
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
}
void TypeChecker::Visit(Expression_list *n)
{

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
     //   cout<<"oooooo "<<n->name<<n->symbol->type<<endl;
}
void TypeChecker::Visit(IntNum *n)
{
}
void TypeChecker::Visit(RealNum *n)
{
}
void TypeChecker::Visit(String *n)
{
}
void TypeChecker::Visit(Bool *n)
{
}
void TypeChecker::Visit(Char *n)
{
    
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
  //  cout<<n->intNum->value<<" INTNUM "<<n->type<<endl;

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
                    else
                    {
                        n->type = temp->type;
                    }
                }
                else
                {
                    n->type = temp->type;
                }
            }
        }
        else
        {
            n->type = temp->type;
        }
    }
    else
    {
        n->type = temp->type;
    }
    cout << endl
         << n->type << endl;
}
void TypeChecker::Visit(UnaryExpr *n)
{
    int op = n->unaryOperator->index;

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
}
void TypeChecker::Visit(NotExpr *n) {}
void TypeChecker::Visit(BracketExpr *n)
{
    n->expression->accept(this);
    n->type = n->id->symbol->type;
};
void TypeChecker::Visit(ExpressionWithExpr *n){};
void TypeChecker::Visit(Type *n){};
void TypeChecker::Visit(Compound_statement *n)
{
    n->optionalStatement->accept(this);
}

void TypeChecker::Visit(Subprogram_head *n)
{
    n->arguments->accept(this);
};
void TypeChecker::Visit(Subprogram_variables *n)
{
    try
    {
        for (int i = 0; i < (int)(n->subprogramVariables->size()); i++)
        {
            n->subprogramVariables->at(i).first->accept(this);
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
void TypeChecker::Visit(Procedure_statement *n){

};
void TypeChecker::Visit(If *n)
{

    n->expression->accept(this);
    n->thenStatement->accept(this);
};
void TypeChecker::Visit(IfElse *n)
{

    n->expression->accept(this);
    n->thenStatement->accept(this);
    n->elseStatement->accept(this);
};
void TypeChecker::Visit(While *n)
{

    n->expression->accept(this);
    n->doStatement->accept(this);
};
void TypeChecker::Visit(For *n)
{

    n->variable->accept(this);
    n->down->accept(this);
    n->up->accept(this);
    n->optionalStatement->accept(this);
    int l = n->variable->id->symbol->type;
    int r = n->down->type;

    bool t = typechecking_assign(l, r);
    if (t)
    {

        cout << "mismatching assignment of var :" << n->variable->id->name << " in line: " << n->line << endl;
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

    bool t = typechecking_assign(l, r);
    if (t)
    {
        cout << "mismatching assignment of var :" << n->variable->id->name << " in line: " << n->line << endl;
    }
};
void TypeChecker::Visit(Procedure_statementList *n)
{

    string key = "Proc" + n->id->name;
    if (n->expressionList)
    {

        n->expressionList->accept(this);
        for (int i = 0; i < (int)(n->expressionList->expressionList->size()); i++)
        {
        //    n->expressionList->expressionList->at(i)->
            int e = n->expressionList->expressionList->at(i)->type;
        //    cout<<"eee "<<n->expressionList->expressionList->at(i)->type<<endl;
            key += "@" + types[e];
        }
    }
    cout<<endl<<key<<endl;

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
                    else
                    {
                        n->id->symbol=temp;
                        //  n->type = n->id->symbol->type;
                    }
                }else
                    {
                        n->id->symbol=temp;
                        //  n->type = n->id->symbol->type;
                    }
            }
        }
        else
                    {
                        n->id->symbol=temp;
                        //  n->type = n->id->symbol->type;
                    }
    }
    else
    {
                        n->id->symbol=temp;
      
        //  n->type = n->id->symbol->type;
    }
};
void TypeChecker::Visit(Array_type *n){

};
//////////////////////////////////

//////////////////Symbol table

/****************************************/
Symbol::Symbol(string name, int kind, int type)
{
    this->first = NULL ;
    this->second = NULL ;
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
Symbol::Symbol(string name, int kind, int type, int first, int second)
{
    this->name = name;
    this->kind = kind;
    this->type = type;
    this->first = first;
    this->second = second;
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
    kindes[3] = "F";
    kindes[1] = "GV";
    kindes[2] = "LV";
    kindes[4] = "Prog";
    kindes[5] = "Proc";
    types[1] = "int";
    types[2] = "float";
    types[3] = "boolean";
    types[4] = "char";
    types[5] = "string";
    types[6] = "null";
}

bool SymbolTable::AddSymbol(Id *id, int kind, Type *type)
{
    if (type->first == NULL)
    {
        Symbol *sym = new Symbol(id->name, kind, type->type);
        string key = kindes[kind] + id->name;
        // cout << endl
        //      << key << type->type << endl;
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
    }
    else
    {
        Symbol *sym = new Symbol(id->name, kind, type->type, type->first, type->second);
        string key = kindes[kind] + id->name;

        // key += "@" + to_string(type->second) + "@" + to_string(type->second);
        // cout << key << type->type << endl;

        // cout << id->name << " in line: " << id->line << "Key: " << key << endl;
        Symbol *temp = this->current->hashTab->GetMember(key);

        if (temp == NULL)
        {
            this->current->hashTab->AddKey(key, sym);
            id->symbol = sym;
            return true;
        }
        else
        {
            cout << " redifined array : " << id->name << " in line: " << id->line << endl;
            // symbolTable->errors->AddError("redifined function : " + id->name, id->line, 0);

            // symanticerror = true;
            return false;
        }
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

    key = kindes[2] + id->name;
    // cout <<endl<< key<<endl;
    sym = this->current->hashTab->GetMember(key);
    if (sym != NULL)
    {
        
       
        id->symbol = sym;
        return sym;
    }
    else
    {
        key = kindes[1] + id->name;
        // cout << key;
        sym = this->current->hashTab->GetMember(key);
        if (sym != NULL)
        {
           
            id->symbol = sym;
            return sym;
        }
        else
        {
            key = kindes[1] + id->name;
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

Symbol *SymbolTable::LookUpArray(Id *id, int index)
{
    string key;
    Symbol *sym;

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
        key = kindes[1] + id->name;
        // cout << key;
        sym = this->current->hashTab->GetMember(key);
        if (sym != NULL)
        {
            id->symbol = sym;
            return sym;
        }
        else
        {
            key = kindes[1] + id->name;
            // cout << this->scopes->size();

            sym = this->scopes->at(1)->hashTab->GetMember(key);
            if (sym != NULL)
            {
                if (index <= sym->second && index >= sym->first)
                {
                    id->symbol = sym;
                    return sym;
                }
                else
                {
                    cout << "Array index out of bounds " << id->name << " in line: " << id->line << endl;
                }
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

////////////////////////////////////////////// Code Visitor
void Print(string s)
{
    vout << s << endl;
}
 CodeVisitor::CodeVisitor()
{
    fp = 0;
    gp = 1024;
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
    operators[8] = "<";
    operators[9] = ">=";
    operators[10] = "=";
    operators[11] = "<>";
    operators[12] = "not";
    operators[13] = "or";
    operators[14] = "and";
    this->functions = new vector<Symbol *>;
}
void CodeVisitor::Visit(Node *n)
{
}
void CodeVisitor::Visit(Program *n)
{
    Print("Start");
    n->declarations->accept(this);
    Print("jump START_PROGRAM");
    n->subprogramDeclarations->accept(this);
    Print("START_PROGRAM:");
    n->compoundStatement->accept(this);
    Print("Stop\n");
}
void CodeVisitor::Visit(Declarations *n)
{
    // cout << "This is Declarations-" << endl;
    try
    {
        for (int i = 0; i < (int)(n->declarations->size()); i++)
        {
            n->declarations->at(i)->accept(this);
        }
    }
    catch (std::exception e)
    {
        cout << "Habidator" << endl;
    }
}
void CodeVisitor::Visit(DeclarationVar *n)
{
    if(n->type->first != NULL) {
        int Size = n->type->second - n->type->first + 1 ;
        for(int i=0;i<n->identifierList->Ids->size();i++)
        {

            Print("alloc " + std::to_string(Size));
            Print("storeg " + std::to_string(gp));
            int type = n->type->type;
            n->identifierList->Ids->at(i)->symbol->kind=1;
            for (int j = 0; j < Size; j++)
            {
                if (type == 1)
                {
                    Print("pushg " + std::to_string(gp));
                    Print("pushi " + std::to_string(j));
                    Print("pushi 0");
                    Print("storen");
                }
                else
                if (type == 3)
                {
                    Print("pushg " + std::to_string(gp));
                    Print("pushi " + std::to_string(j));
                    Print("pushi 0");
                    Print("storen");
                }
                else
                if (type == 2)
                {
                    Print("pushg " + std::to_string(gp));;
                    Print("pushi " + std::to_string(j));
                    Print("pushf 0.0");
                    Print("storen");
                }
                else
                if (type == 5)
                {
                    Print("pushg " + std::to_string(gp));
                    Print("pushi " + std::to_string(j));
                    Print("pushs \"\"");
                    Print("storen");
                }
            }
            //Print("pushl " + std::to_string(fp));
            gp--;
        }
    }
    else{

        for(int i=0;i<n->identifierList->Ids->size();i++)
        {
            Print("pushi 0") ;
            Id * currId = n->identifierList->Ids->at(i) ;
            currId->symbol->location = gp ;
            if(currId->symbol->type == 2 )
                Print("itof") ;
            Print("storeg " + std::to_string(gp));
            Print("pushg " + std::to_string(gp));
            gp--;
        }

    }
}
void CodeVisitor::Visit(Declaration *n)
{

    for (int i = 0; i < n->identifierList->Ids->size(); i++)
    {

        if (n->identifierList->Ids->at(i)->symbol->type < 5)
        {
            Print("pushi 0");
            if (n->identifierList->Ids->at(i)->symbol->type == 2)
                Print("itof");
            if(n->identifierList->Ids->at(i)->symbol->kind ==1) {
                n->identifierList->Ids->at(i)->symbol->location = gp;
                Print("storeg " + std::to_string(gp));
                Print("pushg " + std::to_string(gp));
                gp--;
            }
            else{
                n->identifierList->Ids->at(i)->symbol->location = gp;
                Print("storel " + std::to_string(fp));
                Print("pushl " + std::to_string(fp));
                fp++;
            }
        }
    }
}
void CodeVisitor::Visit(Subprogram_declarations *n)
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
void CodeVisitor::Visit(Subprogram_declaration *n)
{
    n->subprogramHead->accept(this);
    n->subprogramVariables->accept(this);
    n->compoundStatement->accept(this);
    Print("return") ;
}

void CodeVisitor::Visit(Statement *n)
{
    cout << "Habidator";
}
void CodeVisitor::Visit(Expression_list *n)
{
    try
    {
        for (int i = 0; i < (int)(n->expressionList->size()); i++)
        {
            n->expressionList->at(i)->accept(this);
        }
    }
    catch (std::exception e)
    {
        cout << "Habidator 2";
    }
}
void CodeVisitor::Visit(Identifier_list *n)
{
    try
    {
        for (int i = 0; i < (int)(n->Ids->size()); i++)
        {
            n->Ids->at(i)->accept(this);
        }
    }
    catch (std::exception e)
    {
        cout << "Habidator" << endl;
    }
}
void CodeVisitor::Visit(Id *n)
{
}
void CodeVisitor::Visit(IntNum *n)
{
    Print("Pushi " + std::to_string(n->value));
}
void CodeVisitor::Visit(RealNum *n)
{
    Print("Pushf " + std::to_string(n->value));
}
void CodeVisitor::Visit(String *n)
{
    Print("STring is here") ;
    string s = "";
    for (int i = 1; i < n->value.length() - 1; i++)
    {
        s += n->value[i];
    }
    Print("Pushs \"" + s + "\"");
}
void CodeVisitor::Visit(Bool *n)
{
    if (n->value)
    {
        Print("Pushi 1");
    }
    else
    {
        Print("Pushi 0");
    }
}
void CodeVisitor::Visit(Char *n)
{
    Print("Pushs " + std::to_string(n->value));
}
void CodeVisitor::Visit(Expression *n)
{

}
void CodeVisitor::Visit(IdExpr *n)
{
    if (n->id != NULL)
    {
        n->id->accept(this);
        if (n->id->symbol->kind == 1)
        {
            Print("pushg " + std::to_string(n->id->symbol->location));
        }
        else
        {
            Print("pushl " + std::to_string(n->id->symbol->location));
        }
    }
}
///////////
void CodeVisitor::Visit(IntNumExpr *n)
{
    n->intNum->accept(this);
}
void CodeVisitor::Visit(BoolExpr *n)
{
    n->aBool->accept(this);
}
void CodeVisitor::Visit(RealNumExpr *n)
{
    n->realNum->accept(this);
}
void CodeVisitor::Visit(StringExpr *n)
{
    n->aString->accept(this);
}
void CodeVisitor::Visit(CharExpr *n)
{
    n->aChar->accept(this);
}
void CodeVisitor::Visit(ListWithExpr *n)
{
    if (n->expressionList)
    {
        for (int i = 0; i < n->expressionList->expressionList->size(); i++)
        {
            n->expressionList->expressionList->at(i)->accept(this);
            if (n->expressionList->expressionList->at(i)->type == 1 &&
                n->id->symbol->subprogram_head->arguments->parameterList->parameters->at(i).second->type == 2)
                Print("itof");
        }
    }
    string label = "";
    label += n->id->name;
    if (n->expressionList)
    {
        for (int i = 0; i < n->expressionList->expressionList->size(); i++)
        {
            label += "__" + types[n->expressionList->expressionList->at(i)->type];
        }
    }
    Print("pusha " + label);
    Print("call");

    Symbol *functionSymbol = n->id->symbol;
    if (functionSymbol)
    {
        functions->push_back(functionSymbol);
        if (n->expressionList->expressionList != NULL && n->expressionList->expressionList && n->expressionList->expressionList->size() > 0)
            Print("pop " + std::to_string(n->expressionList->expressionList->size()));
        if (functionSymbol->type != 4)
            Print("pushg " + std::to_string(gp));
    }
    else
    {
        // Add errors
    }
}
void CodeVisitor::Visit(UnaryExpr *n)
{
    if (n->rightExpression != NULL)
        n->rightExpression->accept(this);
    if (n->leftExpression != NULL)
        n->leftExpression->accept(this);

    int op = n->unaryOperator->index;
    if (op < 5) /// Mul Add Sub Div
    {
        string operation = "";
        if (op == 1)
            operation = "mul";
        if (op == 2)
            operation = "add";
        if (op == 3)
            operation = "sub";
        if (op == 4)
            operation = "div";

        if (n->rightExpression->type == 1 && n->rightExpression->type == 1)
            Print(operation);
        else if (n->leftExpression->type == 1)
        {
            Print("storeg " + std::to_string(gp));
            Print("itof");
            Print("pushg " + std::to_string(gp));
            Print("f" + operation);
        }
        else if (n->rightExpression->type == 1)
        {
            Print("itof");
            Print("f" + operation);
        }
        else if (n->leftExpression->type == 2 && n->rightExpression->type == 2)
            Print("f" + operation);
    }
    if (op == 5) /// Mod
    {
        if (n->rightExpression->type == 1 && n->rightExpression->type == 1)
            Print("mod");
    }
    if (op == 14) /// And
    {
        Print("add");
        Print("pushi 2");
        Print("equal");
    }
    if (op == 13) /// Or
    {
        Print("add");
        Print("pushi 0");
        Print("equal");
        Print("not");
    }
    if (op >= 6 && op <= 11)
    {
        string operation = "";
        if (op == 6)
            operation = "sup";
        if (op == 7)
            operation = "infeq";
        if (op == 8)
            operation = "inf";
        if (op == 9)
            operation = "supeq";
        if (op == 10)
            operation = "equal";
        if (op == 11)
            operation = "equal";
        if (n->leftExpression->type == 1 && n->rightExpression->type == 1)
            Print(operation);
        else if (n->leftExpression->type == 1)
        {
            Print("storeg " + std::to_string(gp));
            Print("itof");
            Print("pushg " + std::to_string(gp));
            Print(operation);
        }
        else if (n->rightExpression->type == 1)
        {
            Print("itof");
            Print(operation);
        }
        else if (n->leftExpression->type == 2 && n->rightExpression->type == 2)
            Print(operation);
        if (op == 12)
            Print("not");
    }
}
void CodeVisitor::Visit(NotExpr *n)
{
    n->expression->accept(this);
    Print("not");
}
void CodeVisitor::Visit(BracketExpr *n)
{
    if (n->id != NULL)
        n->id->accept(this);
    int Location = n->id->symbol->location;
    if (n->id->symbol->kind == 3)
    {
        Print("Pushl " + std::to_string(Location));
    }
    if (n->id->symbol->kind == 2)
    {

        Print("Pushg " + std::to_string(Location));
    }
    if (n->expression != NULL)
        n->expression->accept(this);
    Print("loadn");
}
void CodeVisitor::Visit(ExpressionWithExpr *n)
{
    n->expression->accept(this);
}
/////////////////////////
void CodeVisitor::Visit(Type *n) {
    cout<<"dont go"<<endl;
};
//void CodeVisitor::Visit(Standard_type *n)
//{
//}
void CodeVisitor::Visit(Array_type *n)
{
//    int size = n->last->value - n->first->value + 1;
//    Print("alloc " + std::to_string(size));
//    Print("storel " + std::to_string(fp));
//    int type = n->type;
//    for (int i = 0; i < size; i++)
//    {
//        if (type == 1)
//        {
//            Print("pushl " + std::to_string(fp));
//            Print("pushi " + std::to_string(i));
//            Print("pushi 0");
//            Print("storen");
//        }
//        else if (type == 3)
//        {
//            Print("pushl " + std::to_string(fp));
//            Print("pushi " + std::to_string(i));
//            Print("pushi 0");
//            Print("storen");
//        }
//        else if (type == 2)
//        {
//            Print("pushl " + std::to_string(fp));
//            Print("pushi " + std::to_string(i));
//            Print("pushf 0.0");
//            Print("storen");
//        }
//        else if (type == 5)
//        {
//            Print("pushl " + std::to_string(fp));
//            Print("pushi " + std::to_string(i));
//            Print("pushs \"\"");
//            Print("storen");
//        }
//    }
//    Print("pushl " + std::to_string(fp));
//    // fp++;
//    fp += size;
}
void CodeVisitor::Visit(Compound_statement *n)
{
    if (n->optionalStatement != NULL)
        n->optionalStatement->accept(this);
}
void CodeVisitor::Visit(Variable *n) {}
void CodeVisitor::Visit(Subprogram_head *n)
{
    if (n->CG_visited == false)
    {
        fp = 0;
        n->CG_visited = true;
        string label = "";
        label += n->id->name;
        if (n->arguments->parameterList->parameters)
        {
            for (int i = 0; i < n->arguments->parameterList->parameters->size(); i++)
            {
                label += "__" + types[n->arguments->parameterList->parameters->at(i).second->type];
            }
        }
        Print(label + ":");
        if (n->arguments->parameterList->parameters)
            n->arguments->parameterList->accept(this);

    }

}

void CodeVisitor::Visit(Subprogram_variables *n)
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
void CodeVisitor::Visit(Arguments *n)
{
    if (n->parameterList != NULL)
        n->parameterList->accept(this);
}
void CodeVisitor::Visit(Parameter_list *n)
{
    if (n->parameters != NULL)
    {
        for (int i = 0; i < (int)(n->parameters->size()); i++)
        {
            n->parameters->at(i).first->accept(this);
        }
    }
}
void CodeVisitor::Visit(Statement_list *n)
{
    if (n->statement_list != NULL)
    {
        for (int i = 0; i < (int)(n->statement_list->size()); i++)
        {
            n->statement_list->at(i)->accept(this);
        }
    }
}
void CodeVisitor::Visit(Optional_statement *n)
{
    if (n->statementList != NULL)
    {
        n->statementList->accept(this);
    }
}
void CodeVisitor::Visit(Optional_statementNonEmpty *n)
{
    n->statementList->accept(this);
}
void CodeVisitor::Visit(VariableExpression *n)
{
    if (n->id != NULL) n->id->accept(this);
    //w("storeg " + std::to_string(g));
    if (n->id->symbol->kind == 1)
    {

        cout<<"here2"<<n->id->symbol->location<<endl;
        Print("pushg " + std::to_string(n->id->symbol->location));
    }
    else
    {
        Print("pushl " + std::to_string(n->id->symbol->location) );
    }
    if (n->expression != NULL) n->expression->accept(this);
    //w("pushg " + std::to_string(g));
    Print("loadn");
}

void CodeVisitor::Visit(Procedure_statement *n)
{
    if (n->CG_visited == false)
    {
        fp = 0;
        n->CG_visited = true;
        string label = "";
        label += n->id->name;
        if (n->id->symbol->subprogram_head->arguments->parameterList->parameters != NULL)
        {
            for (int i = 0; i < n->id->symbol->subprogram_head->arguments->parameterList->parameters->size(); i++)
            {
                label += "__" + types[n->id->symbol->subprogram_head->arguments->parameterList->parameters->at(i).second->type];
            }
        }
        Print(label + ":");
        if (n->id->symbol->subprogram_head->arguments->parameterList != NULL)
            n->id->symbol->subprogram_head->arguments->parameterList->accept(this);
        if (n->expressionList != NULL)
            n->expressionList->accept(this);
        Print("return");
    }
}
void CodeVisitor::Visit(If *n)
{
    ifLabel++;
    int label = ifLabel;
    Print("IF_BEGIN" + std::to_string((label)) + ":");
    if (n->expression != NULL)
        n->expression->accept(this);
    Print("jz IF_END" + std::to_string((label)));
    if (n->thenStatement != NULL)
        n->thenStatement->accept(this);
    Print("IF_END" + std::to_string((label)) + ":");
}
void CodeVisitor::Visit(IfElse *n)
{
    ifElseLabel++;
    int label = ifElseLabel;
    Print("IF_BEGIN" + std::to_string((label)) + ":");
    if (n->expression != NULL)
        n->expression->accept(this);
    Print("jz ELSE_BEGIN" + std::to_string((label)));
    if (n->thenStatement != NULL)
        n->thenStatement->accept(this);
    Print("IF_END" + std::to_string((label)) + ":");
    Print("jump ELSE_END" + std::to_string((label)));
    Print("ELSE_BEGIN" + std::to_string((label)) + ":");
    if (n->elseStatement != NULL)
        n->elseStatement->accept(this);
    Print("ELSE_END" + std::to_string((label)) + ":");
}
void CodeVisitor::Visit(While *n)
{
    whileLabel++;
    int label = whileLabel;
    Print("WHILE_BEGIN" + std::to_string(whileLabel) + ":");
    if (n->expression != NULL)
    {
        n->expression->accept(this);
    }
    Print("jz WHILE_END" + std::to_string(whileLabel));
    if (n->doStatement != NULL)
    {
        n->doStatement->accept(this);
    }
    Print("jump WHILE_BEGIN" + std::to_string(whileLabel));
    Print("WHILE_END" + std::to_string(whileLabel) + ":");
};
void CodeVisitor::Visit(For *n)
{
    forLabel++;
    int label = forLabel;
    if (n->variable->id != NULL)
    {
        //// assign for statement
        n->variable->id->symbol->location = gp;
        n->down->accept(this);
        if (n->variable->id->symbol->kind == 1)
        {
            n->variable->id->symbol->location = gp;
            Print("storeg " + std::to_string(gp));
            Print("pushg " + std::to_string(gp));
            gp--;
        }
        else if (n->variable->id->symbol->kind == 2)
        {
            if (n->down->type == 1 && n->variable->id->symbol->type == 2)
            {
                Print("itof");
            }
            n->variable->id->symbol->location = fp;
            Print("storel " + std::to_string(fp));
            Print("pushl " + std::to_string(fp));
            fp++;
        }
        Print("storeg " + std::to_string(gp));
    }
    Print("FOR_BEGIN" + std::to_string(label) + ":");
    ///// condition
    if (n->variable != NULL)
        n->variable->accept(this);
    if (n->up != NULL)
        n->up->accept(this);
    Print("infeq");
    Print("jz FOR_END" + std::to_string(label));

    if (n->optionalStatement != NULL)
        n->optionalStatement->accept(this);
    n->variable->accept(this);
    Print("pushi 1");
    Print("add");
    Print("jump FOR_BEGIN" + std::to_string(label));
    Print("FOR_END" + std::to_string(label) + ":");
};
void CodeVisitor::Visit(Unary_operator *n){

};
void CodeVisitor::Visit(Variable_Expression *n)
{
    cout<<n->variable->id->symbol->first<<endl;
    if(n->variable->id->symbol->first != NULL) {
        /*int type = n->variable->id->symbol->type;
        n->variable->accept(this);
        n->expression->accept(this) ;
        Print("loadn");*/
        cout<<"we"<<endl;
        if (n->variable->id != NULL) n->variable->id->accept(this);
        //w("storeg " + std::to_string(g));
        if (n->variable->id->symbol->kind == 1)
        {
            cout<<"here1"<<n->variable->id->symbol->location<<endl;
            Print("pushg " + std::to_string(n->variable->id->symbol->location));
        }
        else
        {
            Print("pushl " + std::to_string(n->variable->id->symbol->location));
        }
        if (n->variable != NULL) n->variable->accept(this);
        //w("pushg " + std::to_string(g));
        if (n->expression != NULL) n->expression->accept(this);
        Print("storen");
    }else{
        n->expression->accept(this);
        if (n->variable->id->symbol->kind == 1) {
            n->variable->id->symbol->location = gp;
            Print("storeg " + std::to_string(gp));
            Print("pushg " + std::to_string(gp));
            gp--;
        } else if (n->variable->id->symbol->kind == 2) {
            if (n->expression->type == 1 && n->variable->id->symbol->type == 2) {
                Print("itof");
            }
            n->variable->id->symbol->location = fp;
            Print("storel " + std::to_string(fp));
            Print("pushl " + std::to_string(fp));
            fp++;
        }
    }
};
void CodeVisitor::Visit(Procedure_statementList *n){
    if (n->expressionList != NULL) {
        for (int i = 0; i < n->expressionList->expressionList->size(); i++)
        {
            //cout<<"Done here"<<endl;
            n->expressionList->expressionList->at(i)->accept(this);


        }
    }
    string label = "";
    label += n->id->name;

    cout<<n->id->symbol->subprogram_head->arguments->parameterList->parameters->size()<<endl;
    if(n->id->symbol->subprogram_head->arguments->parameterList != NULL
    && n->id->symbol->subprogram_head->arguments->parameterList->parameters != NULL) {
        for (int i = 0; i < n->id->symbol->subprogram_head->arguments->parameterList->parameters->size(); i++) {
            label += "__" +
                     types[n->id->symbol->subprogram_head->arguments->parameterList->parameters->at(i).second->type];
        }
    }

    Print("pusha " + label);
    Print("call");

    Symbol * functionSymbol = n->id->symbol;
    if (functionSymbol != NULL)
    {
        functions->push_back(functionSymbol);
        if (n->expressionList != NULL && n->expressionList->expressionList && n->expressionList->expressionList->size() > 0)
            Print("pop " + std::to_string(n->expressionList->expressionList->size()));
        if (functionSymbol->type != 4) {
            Print("pushg " + std::to_string(gp));
        }
    }
    else
    {
        // Add errors
    }
};



 void CodeVisitor::generateReadWriteFunction()
 {
     Print("\n\n\n");
     Print("\n\n\n");
     ////writeline integer
     Print("write__int:");
     Print("pushl -1");
     Print("storel 0");
     Print("pushl 0");
     Print("pushl 0");
     Print("writei");
     Print("return\n\n\n");

     ////writeline real
     Print("write__double:");
     Print("pushl -1");
     Print("storel 0");
     Print("pushl 0");
     Print("pushl 0");
     Print("writef");
     Print("return\n\n\n");

     ////writeline real
     Print("write__string:");
     Print("pushl -1");
     Print("storel 0");
     Print("pushl 0");
     Print("pushl 0");
     Print("writes");
     Print("return\n\n\n");

     ////writeline boolean
     Print("write__boolean:");
     Print("pushl -1");
     Print("storel 0");
     Print("pushl 0");
     Print("pushl 0");
     Print("writei");
     Print("return\n\n\n");

     ////read integer
     Print("readInt:");
     Print("read");
     Print("atoi");
     Print("storeg " + std::to_string(gp) + "");
     Print("return\n\n\n");

     ////read real
     Print("readReal:");
     Print("read");
     Print("atof");
     Print("storeg " + std::to_string(gp) + "");
     Print("return\n\n\n");

     ////read string
     Print("readString:");
     Print("read");
     Print("storeg " + std::to_string(gp) + "");
     Print("return\n\n\n");

     /////read key
     Print("readKey:");
     Print("read");
     Print("pop 1");
     Print("return");
 }

/*void initialize()
{
    //  _write_int
    Id * id_write_int = new Id("write", 0, 0);
    Id * id_param_write_int = new Id("1_write_int_x", 0, 0);
    symbolTable->AddSymbol(id_param_write_int, Typ2, 1);
    Params * prameters_write_int = new Params(new Parameter(1, id_param_write_int, 0, 0), 0, 0);
    writeline_write_int = new Void_Param_Fun(id_write_int, prameters_write_int, NULL, 0, 0);
    writeline_write_int->CG_visited = true;
    symtab->AddSymbol(id_write_int, 3, 4, prameters_write_int, writeline_write_int);

    //  _write_real
    Identifier * id_write_real = new Identifier("write", 0, 0);
    Identifier * id_param_write_real = new Identifier("1_write_real_x", 0, 0);
    symtab->AddSymbol(id_param_write_real, 2, 2);
    Params * prameters_write_real = new Params(new Parameter(2, id_param_write_real, 0, 0), 0, 0);
    writeline_write_real = new Void_Param_Fun(id_write_real, prameters_write_real, NULL, 0, 0);
    writeline_write_real->CG_visited = true;
    symtab->AddSymbol(id_write_real, 3, 4, prameters_write_real, writeline_write_real);

    //  _write_string
    Identifier * id_write_string = new Identifier("write", 0, 0);
    Identifier * id_param_write_string = new Identifier("1_write_string_x", 0, 0);
    symtab->AddSymbol(id_param_write_string, 2, 5);
    Params * prameters_write_string = new Params(new Parameter(5, id_param_write_string, 0, 0), 0, 0);
    writeline_write_string = new Void_Param_Fun(id_write_string, prameters_write_string, NULL, 0, 0);
    writeline_write_string->CG_visited = true;
    symtab->AddSymbol(id_write_string, 3, 4, prameters_write_string, writeline_write_string);

    //  _write_bool
    Identifier * id_write_bool = new Identifier("write", 0, 0);
    Identifier * id_param_write_bool = new Identifier("1_write_bool_x", 0, 0);
    symtab->AddSymbol(id_param_write_bool, 2, 3);
    Params * prameters_write_bool = new Params(new Parameter(3, id_param_write_bool, 0, 0), 0, 0);
    writeline_write_bool = new Void_Param_Fun(id_write_bool, prameters_write_bool, NULL, 0, 0);
    writeline_write_bool->CG_visited = true;
    symtab->AddSymbol(id_write_bool, 3, 4, prameters_write_bool, writeline_write_bool);


    //  _read_int
    Identifier * id_read_int = new Identifier("readInt", 0, 0);
    readline_read_int = new Type_Param_Fun(1,id_read_int, NULL, NULL, 0, 0);
    readline_read_int->CG_visited = true;
    symtab->AddSymbol(id_read_int, 3, 1, NULL, readline_read_int);

    //  _read_real
    Identifier * id_read_real = new Identifier("readReal", 0, 0);
    readline_read_real = new Type_Param_Fun(2, id_read_real, NULL, NULL, 0, 0);
    readline_read_real->CG_visited = true;
    symtab->AddSymbol(id_read_real, 3, 2, NULL, readline_read_real);

    //  _read_string
    Identifier * id_read_string = new Identifier("readString", 0, 0);
    readline_read_string = new Type_Param_Fun(2, id_read_string, NULL, NULL, 0, 0);
    readline_read_string->CG_visited = true;
    symtab->AddSymbol(id_read_string, 3, 2, NULL, readline_read_string);

    //  _read_key
    Identifier * id_read_key = new Identifier("readKey", 0, 0);
    readline_read_key = new Type_Param_Fun(4, id_read_key, NULL, NULL, 0, 0);
    readline_read_key->CG_visited = true;
    symtab->AddSymbol(id_read_key, 3, 4, NULL, readline_read_key);

    ////  _read_bool
    //Identifier * id_read_bool = new Identifier("readBoolean", 0, 0);
    //Type_Param_Fun * readline_read_bool = new Type_Param_Fun(1, id_read_bool, NULL, NULL, 0, 0);
    //readline_read_bool->CG_visited = true;
    //symtab->AddSymbol(id_read_bool, 3, 1, NULL, readline_read_bool);
}
*/