#include <iostream>
using std::cout;
using std::endl;
#include "ast.h"
extern int yyparse();
extern int yyerror(const char *);

extern Program *root;
extern Visitor *visitor;
extern TypeChecker *typeChecker;

int main()
{
    yyparse();
    cout << "parsing is done! \n";
    system("pause");
    // cout << "somar";
    root;
    Visitor *printVisitor = new PrintVisitor;
    TypeChecker *typeChecker = new TypeChecker;
    //  root->accept(printVisitor);
    root->accept(typeChecker);

    return 0;
}
