Program Lesson7_Program2;
Procedure DrawLine(X : Integer; Y : Integer);
Var Counter : Integer;
Begin
For Counter := 1 to 10 do
Begin
End;
End;
Begin
DrawLine(10,5);
DrawLine(10,6);
DrawLine(10,7);
DrawLine(10,10);
End.

Program exProcedure;
Var a: Integer;
Procedure FindMin(x :Integer ; y : Integer ); 
Var m : Integer;
Begin
   If x < y Then
      m:= x;
   If x >= y Then
      m:= y;
End;  
Begin
FindMin(5,3);
End.