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
   // CodeVisitor *codeVisitor = new CodeVisitor ;
    root->accept(printVisitor);
    root->accept(typeChecker) ;
    //root->accept(codeVisitor);

    return 0;
}
