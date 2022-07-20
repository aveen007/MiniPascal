Program exProcedure;
Var a: Array [ 1 .. 5 ] of Integer;
var ccc:integer;
Function FindMin(x : Array [ 1 .. 5 ] of Integer ; y : Integer ): Integer; 
Begin
    while y>6 do begin
    y:=y*x[1];
    End;
    *FindMin := 1;
End; 
Begin
 //a[1]:=2;

 ccc:=FindMin(a,5);
End.