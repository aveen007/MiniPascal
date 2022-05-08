#include <iostream>
using std::cout;
using std::endl;
extern int yyparse();
extern int yyerror(const char *);

int main()
{
    // extern FILE *yyin;
    // yyin = fopen("input.txt", "r");
    yyparse();

    cout << "parsing is done! \n";
    // system("pause");
    return 0;
}
// ifiuisdbo

// here edited

// second
