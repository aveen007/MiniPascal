
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
Subprogram_declaration::Subprogram_declaration(Subprogram_head * subprogramHead,
                                               Subprogram_variables * subprogramVariables ,
                                               Compound_statement *compoundStatement,
                                               int l , int r) : Node(l,r) {
    this->subprogramHead = subprogramHead ;
    this->subprogramVariables = subprogramVariables ;
    this->compoundStatement = compoundStatement ;
    subprogramHead->father = this ;
    subprogramVariables->father = this ;
    compoundStatement->father = this;
}
Subprogram_declarations::Subprogram_declarations(int l , int r) : Node(l,r) {
    this->subprogram_declarations = new vector<Subprogram_declaration *>();
}
void Subprogram_declarations::AddSubprogramDeclaration(Subprogram_declaration * subprogramDeclaration) {
    this->subprogram_declarations->push_back(subprogramDeclaration) ;
    subprogramDeclaration->father = this ;
}