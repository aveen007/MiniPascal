
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

Array_type::Array_type(IntNum *first, IntNum *last, Standard_type *StandardType, int l, int r) : Type(l, r)
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
    : Optional_statement(l, r)
{
    this->statementList = statementList;
    statementList->father = this;
}
Optional_statement::Optional_statement(int l, int r) : Statement(l, r) {}
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
Procedure_statementList::Procedure_statementList(Expression_list *expressionList, Id *id, int l, int r)
    : Procedure_statement(id, l, r)
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

void PrintVisitor::Visit(Node *n) { cout << "this"; }
void PrintVisitor::Visit(Declarations *n) { cout << "this"; }
void PrintVisitor::Visit(Statement *n) { cout << "this"; }
void PrintVisitor::Visit(Expression_list *n) { cout << "this"; }
void PrintVisitor::Visit(Identifier_list *n) { cout << "this"; }
void PrintVisitor::Visit(Id *n)
{

    cout << "this is an ID: " << n->name << endl;
}
void PrintVisitor::Visit(IntNum *n) { cout << "this"; }
void PrintVisitor::Visit(RealNum *n)
{
    cout << "this";
}
void PrintVisitor::Visit(String *n)
{
    cout << "this";
}
void PrintVisitor::Visit(Bool *n)
{
    cout << "this";
}
void PrintVisitor::Visit(Char *n)
{
    cout << "this";
}
void PrintVisitor::Visit(Expression *n) { cout << "this"; }
void PrintVisitor::Visit(IdExpr *n) { cout << "this"; }
void PrintVisitor::Visit(IntNumExpr *n) { cout << "this"; }
void PrintVisitor::Visit(BoolExpr *n) { cout << "this"; }
void PrintVisitor::Visit(RealNumExpr *n) { cout << "this"; }
void PrintVisitor::Visit(StringExpr *n) { cout << "this"; }
void PrintVisitor::Visit(CharExpr *n) { cout << "this"; }
void PrintVisitor::Visit(ListWithExpr *n) { cout << "this"; }
void PrintVisitor::Visit(UnaryExpr *n) { cout << "this"; }
void PrintVisitor::Visit(NotExpr *n) { cout << "this"; }
void PrintVisitor::Visit(BracketExpr *n) { cout << "this"; };
void PrintVisitor::Visit(ExpressionWithExpr *n) { cout << "this"; };
void PrintVisitor::Visit(Subprogram_declarations *n) { cout << "this"; };
void PrintVisitor::Visit(Type *n) { cout << "this"; };
void PrintVisitor::Visit(Compound_statement *n)
{
    cout << "this";

    //   cout << "this is a compound statement: " << n-><< endl;
}

void PrintVisitor::Visit(Subprogram_head *n) { cout << "this"; };
void PrintVisitor::Visit(Subprogram_variables *n) { cout << "this"; };
void PrintVisitor::Visit(Arguments *n) { cout << "this"; };
void PrintVisitor::Visit(Parameter_list *n) { cout << "this"; };
void PrintVisitor::Visit(Statement_list *n) { cout << "this"; };
void PrintVisitor::Visit(Optional_statement *n) { cout << "this"; };
void PrintVisitor::Visit(Variable *n) { cout << "this"; };
void PrintVisitor::Visit(Procedure_statement *n) { cout << "this"; };
void PrintVisitor::Visit(If *n) { cout << "this"; };
void PrintVisitor::Visit(IfElse *n) { cout << "this"; };
void PrintVisitor::Visit(While *n) { cout << "this"; };
void PrintVisitor::Visit(For *n) { cout << "this"; };
void PrintVisitor::Visit(Unary_operator *n) { cout << "this"; };
//////////////////Symbol table

/****************************************/
Symbol::Symbol(string name, int kind, int type)
{
    this->name = name;
    this->kind = kind;
    this->type = type;
}

// Symbol::Symbol(string name, int kind, int type, function *f)
// {
//     this->name = name;
//     this->kind = kind;
//     this->type = type;
//     this->function = f;
// }

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
    kindes[4] = "C";
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
    Symbol *temp = this->current->hashTab->GetMember(key);
    if (temp == NULL)
    {
        this->current->hashTab->AddKey(key, sym);
        // id->symbol = sym;
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

// bool SymbolTable::AddFunc(Id *id, int kind, Decl_List *d, int type, Func *f)
// {
//     Symbol *sym = new Symbol(id->name, kind, type, f);
//     string key = kindes[kind] + id->name;
//     if (d)
//     {
//         for (int i = 0; i < (int)(d->params->size()); i++)
//         {
//             int e = d->params->at(i)->type->type;
//             key += "@" + types[e];
//         }
//     }

//     // cout << id->name << " in line: " << id->line<< "Key: " << key << endl;
//     Symbol *temp = this->current->hashTab->GetMember(key);

//     if (temp == NULL)
//     {
//         this->current->hashTab->AddKey(key, sym);
//         // id->symbol = sym;
//         return true;
//     }
//     else
//     {
//         cout << " redifined function : " << id->name << " in line: " << id->line << endl;
//         // symbolTable->errors->AddError("redifined function : " + id->name, id->line, 0);

//         // symanticerror = true;
//         return false;
//     }
// }

// Symbol *SymbolTable::LookUp(Id *id)
// {
//     string key;
//     Symbol *sym;

//     key = kindes[3] + id->name;
//     sym = this->current->hashTab->GetMember(key);
//     if (sym != NULL)
//     {
//         //  id->symbol = sym;
//         return sym;
//     }
//     else
//     {
//         key = kindes[2] + id->name;
//         sym = this->scopes->at(this->scopes->size() - 2)->hashTab->GetMember(key);
//         if (sym != NULL)
//         {
//             //      id->symbol = sym;
//             return sym;
//         }
//         else
//         {
//             cout << " undefined variable: " << id->name << " in line: " << id->line << endl;
//             //  symbolTable->errors->AddError("undifined variable : " + id->name, id->line, 0);

//             //  symanticerror = true;
//             return NULL;
//         }
//     }
// }

// Symbol *SymbolTable::LookupConstructor(Id *id)
// {
//     string key;
//     Symbol *sym;
//     key = kindes[4] + id->name;
//     sym = this->scopes->at(1)->hashTab->GetMember(key);
//     if (sym != NULL)
//     {
//         // id->symbol = sym;
//         return sym;
//     }
//     else
//     {
//         cout << " undefined class constrcutor in line: " << id->line << endl;
//         // symbolTable->errors->AddError("undefined class constrcutor ", id->line, 0);

//         //   symanticerror = true;
//         return NULL;
//     }
// }

// void SymbolTable::OpenScope()
// {
//     this->scopes->push_back(new Scope());
//     this->current = this->scopes->at(this->scopes->size() - 1);
// }

// void SymbolTable::CloseScope()
// {
//     this->scopes->pop_back();
//     this->current = this->scopes->at(this->scopes->size() - 1);
// }
