#include <iostream>
using std::cout;
using std::endl;
extern int yyparse();
extern int yyerror(const char *);

int main()
{
    yyparse();
    cout << "parsing is done! \n";
<<<<<<< HEAD
    system("pause");
=======
    system("pause");
    cout << "somar";
>>>>>>> 13cf231971b95faa1a0cd510b09b9b60b5eed316
    return 0;
}
