import os
import re
import math
from calculadora import Calculadora
from calculadora import ttypes as tt
from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

operators = ['+', '-', '/', '*', '^', '!']
parenthesis = ['(', ')']
functions = ['cos', 'sin', 'tan', 'sqr', 'arccos', 'arcsin', 'arctan', 'abs']
hierarchy = {"+":2, "-":2, "*":3, "/":3, "^":4}
system = {1:'SCD', 2:'SCI', 3: 'SI'}
def parse(sequence):
    buffer = []
    queue = []
    startedExpression = False

    for token in sequence:
        if token != ' ':
            if token in parenthesis:                    #Si encontramos un paréntesis
                if buffer:
                    queue.append(''.join(buffer))
                    buffer = []

                if queue and (token == '('):
                    if queue[-1] not in parenthesis and queue[-1] not in functions and queue[-1] not in operators:
                        #Si metemos algo del tipo a(b), sería, en a * b
                        queue.append('*')
                
                queue.append(token)
                startedExpression = True

                if token == ')':
                    startedExpression = False
            elif token in operators:
                if token == '-' and ((startedExpression or len(queue) == 0) and not buffer):
                    buffer.append(token)
                    startedExpression = not(startedExpression)
                else:
                    if buffer:
                        queue.append(''.join(buffer))
                        buffer = []
                    queue.append(token)
                    startedExpression = True
            else:
                buffer.append(token)

    if buffer:
        queue.append(''.join(buffer))
    return queue
def shunting(parse):
    queue = []
    stack = []
    for token in parse:
        if token not in operators and token not in functions and token not in parenthesis:
            queue.append(token)
        elif token in functions:
            stack.append(token)
        elif token in operators:
            while stack and stack[-1] != '(' and hierarchy[token] <= hierarchy[stack[-1]]:
                queue.append(stack.pop())
            stack.append(token)
        elif token in parenthesis:
            if token == '(' :
                stack.append(token)
            else:
                while stack[-1] != '(':
                    queue.append(stack.pop())
                stack.pop()
                if stack and stack[-1] in functions:
                    element = stack.pop()
                    queue.append(element)
                    
    while stack:
        if stack[-1] in parenthesis:
            os.sys('clear')
            print('SYNTAX ERROR')
        queue.append(stack.pop())

    return queue

def RPN(parse):
    stack = []
    arg1 = 0
    arg2 = 0
    for token in parse:
        if token not in operators and token not in functions:
            stack.append(float(token))
        elif token in operators and token != '!':
            arg2 = float(stack.pop())
            arg1 = float(stack.pop())

            if token == '+':
                stack.append(float(client.sum(arg1, arg2)))
            elif token == '-':
                stack.append(float(client.substract(arg1, arg2)))
            elif token == '*':
                stack.append(float(client.mult(arg1, arg2)))
            elif token == '/':
                error = client.div(arg1, arg2)
                if error.code != tt.error.OK:
                    print(error.message)
                    transport.close()
                    exit(-1)
                else:
                    stack.append(float(error.result))
                # stack.append(float())
            elif token == '^':
                stack.append(float(client.power(arg1, arg2)))

        elif token in functions or token == '!':
            arg = float(stack.pop())

            if token == 'cos':
                stack.append(float(client.cosin(arg)))
            elif token == 'sin':
                stack.append(float(client.sin(arg)))
            elif token == 'tan':
                stack.append(float(client.tan(arg)))
            elif token == 'sqr':
                error = client.root(arg)
                if error.code != tt.error.OK:
                    print(error.message)
                    transport.close()
                    exit(-1)
                stack.append(float(error.result))
            elif token == 'arcsin':
                stack.append(float(client.arcsin(arg)))
            elif token == 'arctan':
                stack.append(float(client.arctan(arg)))
            elif token == 'arccos':
                stack.append(float(client.arccos(arg)))
            elif token == '!':
                error = client.factorial(int(arg))
                if error.code != tt.error.OK:
                    print(error.message)
                    transport.close()
                    exit(-1)
                stack.append(float(error.result))
            elif token == 'abs':
                stack.append(float(client.absolute(arg)))

    
    return stack

transport = TSocket.TSocket("127.0.0.0", 9090)
transport = TTransport.TBufferedTransport(transport)
protocol = TBinaryProtocol.TBinaryProtocol(transport)

client = Calculadora.Client(protocol)
transport.open()

client.ping()

os.system('clear')
print('Introduce el modo de la calculadora que quieres usar.')
print('\t1 - Cálculo algebraico.')
print('\t2 - Cambio de base.')
print('\t3 - Ecuaciones.')
print('\t4 - Vectores.')
print('\t5 - Matrices.')
print('\t6 - Operaciones varias.')
print('\t7 - Apagar calculadora.')

opcion = int(input(''))

while opcion < 1 or opcion > 7:
    os.system('clear')
    print('Opción incorrecta.')
    print('Introduce el modo de la calculadora que quieres usar.')
    print('\t1 - Cálculo algebraico.')
    print('\t2 - Cambio de base.')
    print('\t3 - Ecuaciones.')
    print('\t4 - Vectores.')
    print('\t5 - Matrices.')
    print('\t6 - Operaciones varias.')
    print('\t7 - Apagar calculadora.')

    opcion = int(input(''))

continueDefining = 'Y'
# #calculadora algebraica
if opcion == 1:
    os.system('clear')
    print(' ___________________________________________________________')
    print('|                                                           |')
    print('|                  CALCULADORA  ALGEBRAICA                  |')
    print('|___________________________________________________________|')
    print('|                                                           |')
    print('|                   OPERACIONES ADMITIDAS                   |')
    print('|___________________________________________________________|')
    print('|                                                           |')
    print('|  a + b                                                    |')
    print('|  a - b                                                    |')
    print('|  a * b                                                    |')
    print('|  a / b                                                    |')
    print('|  a ^ b                                                    |')
    print('|  cos(a)                                                   |')
    print('|  sin(a)                                                   |')
    print('|  tan(a)                                                   |')
    print('|  sqr(a)                                                   |')
    print('|  a ^ (n / m) ===> raíz de orden n/m                       |')
    print('|  arcsin(a)                                                |')
    print('|  arctan(a)                                                |')
    print('|  arccos(a)                                                |')
    print('|  a!                                                       |')
    print('|  abs(a)                                                   |')
    print('|___________________________________________________________|')
    
    secuencia = input('Introduce la expresión algebraica a evaluar: ')
    print(secuencia)
    parsing = parse(secuencia)
    queue = shunting(parsing)
    os.system('clear')
    result = RPN(queue)
    print(f'El paso de infijo a posfijo es: {queue}\n')
    print(queue)
    print(f'{secuencia}\n')
    print(*result)

# #cambio de base
elif opcion == 2:
    #Limpiamos la consola
    os.system('clear')
    result = 0
    #Introducimos la base inicial y comprobamos que sea correcta
    initialBase = input('¿En qué base está tu número inicial (D/B/H): ').upper()

    while initialBase != 'D' and initialBase != 'B' and initialBase != 'H':
        os.system('clear')
        print('Base incorrecta.')
        initialBase = input('¿En qué base está tu número inicial (D/B/H): ').upper()

    #Número decimal
    if initialBase == 'D':
        #Comprobación de base e input del número
        os.system('clear')
        num = int(input('Introduce el número en base 10: '))

        os.system('clear')
        nextBase = input('¿A qué base quieres pasar el número (B/H): ').upper()

        while nextBase != 'B' and nextBase != 'H':
            os.system('clear')
            print('Base incorrecta.')
            nextBase = input('¿A qué base quieres pasar el número (B/H): ').upper()

        #Hacemos el cambio de base llamando al servidor
        if nextBase == 'B':
            result = client.DecToBin(num)
        else:
            result = client.DecToHex(num)

    #Número binario
    elif initialBase == 'B':
        #Comprobación de base e input del número
        os.system('clear')

        num = input('Introduce el número en base 2 (0b0100...): ')

        os.system('clear')
        nextBase = input('¿A qué base quieres pasar el número (D/H): ').upper()


        while nextBase != 'D' and nextBase != 'H':
            os.system('clear')
            print('Base incorrecta.')
            nextBase = input('¿A qué base quieres pasar el número (D/H): ').upper()

        #Hacemos el cambio de base llamando al servidor
        if nextBase == 'D':
            result = client.BinToDec(num)
        else:
            result = client.BinToHex(num)

    #Número hexadecimal
    else:
        #Comprobación de base e input del número
        os.system('clear')

        num = input('Introduce el número en base 16 (0x0AB...): ')

        os.system('clear')
        nextBase = input('¿A qué base quieres pasar el número (D/B): ').upper()


        while nextBase != 'D' and nextBase != 'B':
            os.system('clear')
            print('Base incorrecta.')
            nextBase = input('¿A qué base quieres pasar el número (D/B): ').upper()

        #Hacemos el cambio de base llamando al servidor
        if nextBase == 'B':
            result = client.HexToBin(num)
        else:
            result = client.HexToDec(num)
    os.system('clear')
    print(f'{num} == {result}')
# #ecuaciones
elif opcion == 3:
    #Limpiamos la consola
    while continueDefining == 'Y':
        terms = []
        os.system('clear')
        print('Definir ecuación')
        print('1:EquationA\t2:EquationB')
        print('3:EquationC\t4:EquationD')
        print('5:Sistemas de ecuación lineal')
        opcionEcuacion = int(input())
        while opcionEcuacion < 1 or opcionEcuacion > 5:
            os.system('clear')
            print('Opción no reconocida')
            print('Definir ecuación')
            print('1:EquationA\t2:EquationB')
            print('3:EquationC\t4:EquationD')
            print('5:Sistemas de ecuación lineal')
            opcionEcuacion = int(input())

        os.system('clear')

        if opcionEcuacion >= 1 and opcionEcuacion <= 4:
            a = float(input('Introduce el término de segundo grado: '))
            b = float(input('Introduce el término de primer grado: '))
            c = float(input('Introduce el término independiente: '))

            terms.append(a)
            terms.append(b)
            terms.append(c)

            client.defineEquation(opcionEcuacion - 1, terms)

            os.system('clear')
            continueDefining = input('¿Quiere definir otra ecuación? Y/N: ').upper()

            while continueDefining != 'Y' and continueDefining != 'N':
                os.system('clear')
                print('Opción no reconocida')
                continueDefining = input('¿Quiere definir otra ecuación? Y/N: ').upper()    
        else:
            continueDefining = False
    if opcionEcuacion >= 1 and opcionEcuacion <= 4:
        os.system('clear')  
        print('¿Qué operación quiere realizar?')
        print('\t1 - Suma de ecuaciones')
        print('\t2 - Resta de ecuaciones')
        print('\t3 - Multiplicación de ecuaciones')
        print('\t4 - Resolución de ecuaciones')
        operation = int(input(''))

        while operation < 1 or operation > 4:
            os.system('clear')
            print('Opción no reconocida')
            print('¿Qué operación quiere realizar?')
            print('\t1 - Suma de ecuaciones')
            print('\t2 - Resta de ecuaciones')
            print('\t3 - Multiplicación de ecuaciones')
            print('\t4 - Resolución de ecuaciones')
            operation = int(input(''))
        os.system('clear')
        if operation >= 1 and operation <= 3:
            eq1 = int(input('Introduce el índice (1, 2, 3, 4) de la primera ecuación: '))
            eq2 = int(input('Introduce el índice (1, 2, 3, 4) de la segunda ecuación: '))

            if operation == 1:
                result = client.sumEquation(eq1 - 1, eq2 - 1)
            elif operation == 2:
                result = client.substractEquation(eq1 - 1, eq2 - 1)
            else:
                result = client.multEquation(eq1 - 1, eq2 - 1)
        else:
            eq = int(input('Introduce el índice (1, 2, 3, 4) de la ecuación: '))
            result = client.solveEquation(eq - 1)
        os.system('clear')
        if result.code != tt.error.OK:
            print(result.message)
            transport.close()
            exit(-1)

        print(result.eq)
    else:
        numEc = int(input('¿Cuántas ecuaciones tiene tu sistema? (2-3): '))

        while numEc < 2 or numEc > 3:
            os.system('clear')
            print('Cantidad equivocada')
            numEc = int(input('¿Cuántas ecuaciones tiene tu sistema? (2-3): '))

        eq = []
        values = []

        for i in range(numEc):
            os.system('clear')
            values = []

            x = float(input(f'Introduce la X de la ecuación {i + 1}: '))
            y = float(input(f'Introduce la Y de la ecuación {i + 1}: '))
            values.append(x)
            values.append(y)
            if numEc == 3:
                z = float(input(f'Introduce la Z de la ecuación {i + 1}: '))
                values.append(z)
            independent = float(input(f'Introduce el término independiente: '))
            values.append(independent)
            eq.append(values)

        client.defineSystem(numEc, eq)
        solutions = client.solveSystem()
        tipo = system[int(solutions['Tipo'])]
        os.system('clear')
        if tipo == 'SCD':
            print(f'El sistema es de tipo {tipo} y tiene las siguientes soluciones: ')

            for clave, valor in solutions.items():
                if clave != 'Tipo':
                    print(f'{clave} : {valor}') 
        elif tipo == 'SCI':
            print(f'El sistema es de tipo {tipo} y por tanto tiene infinitas soluciones.')
        else:
            print(f'El sistema es de tipo {tipo}, por lo tanto no tiene ninguna solución.')
        # print(f'Las soluciones al sistema introducido son:\n x : {solutions[0]}\n y : {solutions[1]}')
        # if numEc == 3:
            # print(f' z : {solutions[2]}')

#vectores
elif opcion == 4:
    #Limpiamos la consola
    while continueDefining == 'Y':
        elements = []
        os.system('clear')
        print('Definir vector')
        print('1:VectorA\t2:VectorB')
        print('3:VectorC\t4:VectorD')
        opcionVectors = int(input())
        while opcionVectors < 1 or opcionVectors > 4:
            os.system('clear')
            print('Opción no reconocida')
            print('Definir vector')
            print('1:VectorA\t2:VectorB')
            print('3:VectorC\t4:VectorD')
            opcionVectors = int(input())
    
        os.system('clear')

        x = float(input('Introduce la coordenada X: '))
        y = float(input('Introduce la coordenada Y: '))
        z = float(input('Introduce la coordenada Z: '))

        elements.append(x)
        elements.append(y)
        elements.append(z)

        client.defineVector(opcionVectors - 1, elements)

        os.system('clear')
        continueDefining = input('¿Quiere definir otro vector? Y/N: ').upper()

        while continueDefining != 'Y' and continueDefining != 'N':
            os.system('clear')
            print('Opción no reconocida')
            continueDefining = input('¿Quiere definir otro vector? Y/N: ').upper()    
    os.system('clear')
    print('¿Qué operación quiere realizar?')
    print('\t1 - Suma de vectores')
    print('\t2 - Resta de vectores')
    print('\t3 - Multiplicación de vectores')
    operation = int(input(''))

    while operation < 1 or operation > 3:
        os.system('clear')
        print('Opción no reconocida')
        print('¿Qué operación quiere realizar?')
        print('\t1 - Suma de vectores')
        print('\t2 - Resta de vectores')
        print('\t3 - Multiplicación de vectores')
        operation = int(input(''))
    os.system('clear')
    vect1 = int(input('Introduce el índice (1, 2, 3, 4) del primer vector: '))
    vect2 = int(input('Introduce el índice (1, 2, 3, 4) del primer vector: '))

    if operation == 1:
        result = client.sumVector(vect1 - 1, vect2 - 1)
    elif operation == 2:
        result = client.substractVector(vect1 - 1, vect2 - 1)
    else:
        result = client.multVector(vect1 - 1, vect2 - 1)

    os.system('clear')   
    if result.code != tt.error.OK:
        print(result.message)
        transport.close()
        exit(-1)
    print(result.vect)
    #matrices
elif opcion == 5:
    #Limpiamos la consola
    while continueDefining == 'Y':
        os.system('clear')
        print('Definir matriz')
        print('1:MatrizA\t2:MatrizB')
        print('3:MatrizC\t4:MatrizD')
        opcionMatrixes = int(input())
        while opcionMatrixes < 1 or opcionMatrixes > 4:
            os.system('clear')
            print('Opción no reconocida')
            print('Definir matriz')
            print('1:MatrizA\t2:MatrizB')
            print('3:MatrizC\t4:MatrizD')
            opcionMatrixes = int(input())

        os.system('clear')
        values = []

        for row in range(4):
            aux = []
            for column in range(4):
                val = float(input(f'Introduce el valor de la fila {row}, columna {column}: '))
                aux.append(val)
            values.append(aux)

        client.defineMatrix(opcionMatrixes - 1, values)

        os.system('clear')
        continueDefining = input('¿Quiere definir otra matriz? Y/N: ').upper()

        while continueDefining != 'Y' and continueDefining != 'N':
            os.system('clear')
            print('Opción no reconocida')
            continueDefining = input('¿Quiere definir otra matriz? Y/N: ').upper()    

    os.system('clear')
    print('¿Qué operación quiere realizar?')
    print('\t1 - Suma de matrices')
    print('\t2 - Resta de matrices')
    print('\t3 - Multiplicación de matrices')
    print('\t4 - Potencia de matrices')
    print('\t5 - Determinante de una matriz')
    print('\t6 - Inversa de una matriz')
    print('\t7 - Transpuesta de una matriz')
    operation = int(input(''))

    while operation < 1 or operation > 7:
        os.system('clear')
        print('Opción no reconocida')
        print('¿Qué operación quiere realizar?')
        print('\t1 - Suma de matrices')
        print('\t2 - Resta de matrices')
        print('\t3 - Multiplicación de matrices')
        print('\t4 - Potencia de matrices')
        print('\t5 - Determinante de una matriz')
        print('\t6 - Inversa de una matriz')
        print('\t7 - Transpuesta de una matriz')
        operation = int(input(''))

    os.system('clear')
    
    if operation >= 1 and operation <= 3:
        mat1 = int(input('Introduce el índice (1, 2, 3, 4) de la primera matriz: '))
        mat2 = int(input('Introduce el índice (1, 2, 3, 4) de la segunda matriz: '))

        if operation == 1:
            result = client.sumMatrix(mat1 - 1, mat2 - 1)
        elif operation == 2:
            result = client.substractMatrix(mat1 - 1, mat2 - 1)
        else:
            result = client.multMatrix(mat1 - 1, mat2 - 1)
    elif operation == 4:
        mat = int(input('Introduce el índice (1, 2, 3, 4) de la matriz: '))
        pow = int(input('Introduce la potencia: '))
        result = client.powerMatrix(mat - 1, pow)
    elif operation == 5:
        mat = int(input('Introduce el índice (1, 2, 3, 4) de la matriz a la quieres sacar el determinante: '))
        result = client.determinant(mat - 1)
    elif operation == 6:
        mat = int(input('Introduce el índice (1, 2, 3, 4) de la matriz a la que quieres sacar la inversa: '))
        result = client.inverseMatrix(mat - 1)
    elif operation == 7:
        mat = int(input('Introduce el índice (1, 2, 3, 4) de la matriz a la que quieres sacar la transpuesta: '))
        result = client.transposeMatrix(mat - 1)
    os.system('clear')
       
    if result.code != tt.error.OK:
        print(result.message)
        transport.close()
        exit(-1)

    if operation != 5:
        for row in range(4):
            print(result.matrix[row])
    else:
        print(result.det)
#Operaciones varias
elif opcion == 6:
    os.system('clear')
    print('Selecciona la operación que quieras hacer:')
    print('\t1 - Factorización en números primos de un número')
    print('\t2 - Módulo de un número')
    print('\t3 - Factorial de un número')
    opcionMisc = int(input(''))

    while opcionMisc < 1 or opcionMisc > 3:
        os.system('clear')
        print('Opción incorrecta.')
        print('Selecciona la operación que quieras hacer:')
        print('\t1 - Factorización en números primos de un número')
        print('\t2 - Módulo de un número')
        print('\t3 - Factorial de un número')
        opcionMisc = int(input(''))

    os.system('clear')

    if opcionMisc == 1:
        numFact = int(input('Introduce el número del que quieres sacar su factorización en números primos: '))
        result = client.factorizacion (numFact)

        os.system('clear')
        if result.code != tt.error.OK:
            print(result.message)
            transport.close()
            exit(-1)
        print(f'{numFact}')

        for number in range(1, len(result.factors) - 1):
            print(number, end = " x ")

        print(result.factors[-1])
    elif opcionMisc == 2:
        num = int(input('Introduce el número al que quieres hacerle el módulo: '))
        module = int(input('Introduce el módulo: '))
        result = client.modulo (num, module)
        os.system('clear')
        if result.code != tt.error.OK:
            print(result.message)
            transport.close()
            exit(-1)

        print(f'{num} % {module} = {result.result}')
    elif opcionMisc == 3:
        num = int(input('Introduce el número al que quieras hacerle el factorial: '))
        result = client.factorial (num)
        os.system('clear')
        if result.code != tt.error.OK:
            print(result.message)
            transport.close()
            exit(-1)
        print(f'{num}! = {result.result}')
#Salir de la calculadora
elif opcion == 7:
    os.system('clear')
    print('Saliendo de la calculadora. . .')

transport.close()