#include <iostream>
using std::cout;
using std::endl;
extern int yyparse();
extern int yyerror(const char *);

int main()
{
    yyparse();
    cout << "parsing is done! \n";
    // system("pause");
    cout << "somar";
    return 0;
}
