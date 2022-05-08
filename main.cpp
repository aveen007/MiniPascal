#include <iostream>
using std::cout;
using std::endl;
extern int yyparse();
extern int yyerror(const char *);

int main()
{
    yyparse();
    cout << "parsing is done! \n";
    return 0;
}
// ifiuisdbo

// here edited

// second
