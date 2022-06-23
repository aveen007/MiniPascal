#include <iostream>
using std::cout;
using std::endl;
#include "ast.h"
extern int yyparse();
extern int yyerror(const char *);

extern Id *root;
extern Visitor *visitor;

int main()
{
    yyparse();
    cout << "parsing is done! \n";
    system("pause");
    cout << "somar";
    root;
    Visitor *printVisitor = new PrintVisitor;
    root->accept(printVisitor);

    return 0;
}
