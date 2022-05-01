flex.exe -oScanner.cpp scanner.l
bison.exe -dtv -o Parser.cpp --define=Parser.h Parser.y
del app.exe
g++ Parser.cpp Scanner.cpp main.cpp Parser.h -o app
:: You can comment the followin line
del Scanner.cpp Parser.cpp Parser.output Parser.h
app.exe
