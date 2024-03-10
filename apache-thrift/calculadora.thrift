namespace cpp CalculadoraCPP

enum error {
   OK,
   UNDEFINED_EQUATION,
   UNDEFINED_VECTOR,
   UNDEFINED_MATRIX,
   NEGATIVE_VALUE,
   DIVISION_ZERO,
   DETERMINANT_ZERO,
   NO_SOLUTION,
}

struct errorCode{
   1:list<double> eq,
   2:list<double> vect,
   3:list<list<double>> matrix,
   4:double result,
   5:double det,
   6:list<i32> factors,
   7:error code,
   8:string message,
}

service Calculadora{
   void ping(),
   void changeServer(1:i32 index),
   double sum(1:double num1, 2:double num2),
   double substract(1:double num1, 2:double num2),
   double power(1:double num, 2:double power),
   double mult(1:double num1, 2:double num2)
   errorCode div(1:double num1, 2:double num2),
   double sin(1:double num),
   double cosin(1:double num),
   double tan(1:double num),
   double arcsin(1:double num),
   double arccos(1:double num),
   double arctan(1:double num),
   errorCode root(1:double num),
   double absolute(1:double num),

   void defineEquation(1:i32 index, 2:list<double> elements),
   errorCode sumEquation(1:i32 eq1, 2:i32 eq2),
   errorCode substractEquation(1:i32 eq1, 2:i32 eq2),
   errorCode multEquation(1:i32 eq1, 2:i32 eq2),
   errorCode solveEquation(1:i32 eq),
   void defineSystem(1:i32 numOfEquations, 2:list<list<double>> equations),
   map<string, double> solveSystem(),

   void defineVector(1:i32 index, 2:list<double> elements),
   errorCode sumVector(1:i32 vec1, 2:i32 vec2),
   errorCode substractVector(1:i32 vec1, 2:i32 vec2),
   errorCode multVector(1:i32 vec1, 2:i32 vec2),

   void defineMatrix(1:i32 index, 2:list<list<double>> elements),
   errorCode sumMatrix(1:i32 mat1, 2:i32 mat2),
   errorCode substractMatrix(1:i32 mat1, 2:i32 mat2),
   errorCode multMatrix(1:i32 mat1, 2:i32 mat2),
   errorCode powerMatrix(1:i32 mat1, 2:i32 power),
   errorCode determinant(1:i32 matrixIndex),
   errorCode inverseMatrix(1:i32 matrixIndex),
   errorCode transposeMatrix(1:i32 matrixIndex),

   string DecToBin(1:i32 decNum),
   i32 BinToDec(1:string binNum),
   string DecToHex(1:i32 decNum),
   i32 HexToDec(1:string HexNum),
   string HexToBin(1:string HexNum),
   string BinToHex(1:string BinNum),
 
   errorCode factorizacion(1:i32 num),
   errorCode factorial(1:i32 num),
   errorCode modulo(1:i32 num, 2:i32 mod),
}