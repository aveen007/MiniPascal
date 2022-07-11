program HELLO;
var counter,factorial,avo: integer;
// var counter: integer;
begin
counter :=5;
factorial :=15;
// factoria :=15;
while factorial>5 do begin
factorial:=factorial*counter;
counter:=counter-1;
end;

writeln(factorial);
writeln('hi');

end.