del app.exe
flex.exe -oScanner.cpp scanner.l
bison.exe -dtv -o Parser.cpp --define=Parser.h Parser.y
g++ Parser.cpp Scanner.cpp main.cpp Parser.h -o app
:: You can comment the followin line mm
del Scanner.cpp Parser.cpp Parser.output Parser.h
type input.txt | app.exe