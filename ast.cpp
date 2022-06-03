
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
Array_type::Array_type(int first, int last, Standard_type *StandardType, int l, int r) : Type(l, r)
{
    this->first = first;
    this->last = last;
    this->StandardType = StandardType;
    StandardType->father = this;
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
