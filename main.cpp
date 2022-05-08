#include <iostream>
using std::cout;
using std::endl;
extern int yyparse();
extern int yyerror(const char *);

int main()
{
<<<<<<< HEAD
=======
    // extern FILE *yyin;
    // yyin = fopen("input.txt", "r");
>>>>>>> 6f5dd7fd671f5b5c8e0d4d190e1e80313878cb7c
    yyparse();
    cout << "parsing is done! \n";
    // system("pause");
    return 0;
}
// ifiuisdbo

// here edited

// second
