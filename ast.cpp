
#include "ast.h"


/// Node
Node::Node(int line, int column) {
    this->line = line;
    this->column = column;
    this->father = NULL;
}

/// Program
Program::Program(Id *id, Declarations *declarations,
                 Subprogram_declarations *subprogramDeclarations,
                 Compound_statement *compoundStatement,
                 int l, int c) : Node(l, c) {
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
Declaration::Declaration(Identifier_list * identifierList, int l , int r)
: Node(l , r){
    this->identifierList = identifierList ;
    identifierList->father = this;
}
DeclarationVar::DeclarationVar(Identifier_list * identifierList, int type, int l, int r)
: Declaration(identifierList , l , r){
    this->type = type ;
}
Declarations::Declarations(int l , int r) : Node(l,r){
    this->declarations = new vector<Declaration *>() ;
}
void Declarations::AddDeclaration(Declaration * declaration) {
    this->declarations->push_back(declaration) ;
    declaration->father = this ;
}

