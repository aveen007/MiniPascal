
#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using std::cout;
using std::endl;

class Declarations;

class Identifier_list;

class Id;

class Subprogram_declarations;
class Type ;
class Compound_statement;
class Subprogram_head ;
class Subprogram_variables ;
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
    Compound_statement *compoundStatement ;
    Subprogram_declaration(Subprogram_head * ,
                           Subprogram_variables * ,
                           Compound_statement * , int, int);
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
    int first;
    int last;
    Standard_type *StandardType;
    Array_type(int, int, Standard_type *, int, int);
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

/// Id
class Id : public Node
{
};


