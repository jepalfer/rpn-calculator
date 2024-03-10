import glob
import sys
import math
import os

from calculadora import Calculadora
from calculadora import ttypes as tt
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from thrift.server import TServer

import logging

logging.basicConfig(level = logging.DEBUG)

def isPrimeNumber(i):
    if i == 1 or i == 2 or i == 3:
        return True
    
    isPrime = True

    index = 2

    while index <= math.sqrt(i):
        if i % index == 0:
            isPrime = False
            break
        index = index + 1

    return isPrime

def solveSecondGrade(a, b, c):
    return math.pow(b, 2) - (4 * a * c)

def solveFirstGrade(a, b):
    return -b/a

def partialDeterminant(elements):
    #Caso base
    if len(elements) == 2:
        return (elements[0][0] * elements[1][1] - (elements[0][1] * elements[1][0]))
    else:
        det = 0

        for column in range(len(elements)):
            mult = 1
            if (column) % 2 == 1:
                mult = -1
            value = elements[0][column]

            smallerMatrix = []
            for row in range(len(elements)):
                auxiliarColumn = []
                for aux_column in range(len(elements)):
                    if row != 0:
                        if aux_column != column:
                            auxiliarColumn.append(elements[row][aux_column])
                if auxiliarColumn:
                    smallerMatrix.append(auxiliarColumn) 

            det += (mult * value * partialDeterminant(smallerMatrix))

    return det

    

class CalculadoraHandler:
    def __init__(self):
        self.log = {}

        #Calculator memory
        self.definedEquations = [0 for i in range(4)]
        self.definedVectors = [0 for i in range(4)]
        self.definedMatrixes = [0 for i in range(6)]
        self.equations = [[0 for i in range(3)]for i in range(4)]
        self.vectors = [[0 for i in range(3)]for i in range(4)]
        #range(5) because last one is auxiliar for power
        self.matrixes = [[[0 for i in range(4)]for i in range(4)]for k in range(6)]
        self.system2 = [[0 for i in range(3)]for j in range(2)]
        self.system3 = [[0 for i in range(4)]for j in range(3)]
        self.numOfEquations = 0  

    def ping(self):
        print('Ping a calculadora base. . .')

    def sum(self, arg1, arg2):
        return arg1 + arg2
    
    def substract(self, arg1, arg2):
        return arg1 - arg2
    
    def mult(self, arg1, arg2):
        return arg1 * arg2
    
    def power(self, arg1, arg2):
        return math.pow(arg1, arg2)
    
    def div(self, arg1, arg2):
        if arg2 == 0:
            error = tt.errorCode(None, None, None, None, None, None, tt.error.DIVISION_ZERO, 'SYNTAX ERROR. DIVISIÓN POR 0')
            return error
        
        correcto = tt.errorCode(None, None, None, arg1 / arg2, None, None, tt.error.OK, None)

        return correcto
    
    def sin(self, n):
        return math.sin(n)
    
    def cosin(self, n):
        return math.cos(n)
    
    def tan(self, n):
        return math.tan(n)
    
    def arcsin(self, n):
        return math.asin(n)
    
    def arccos(self, n):
        return math.acos(n)
    
    def arctan(self, n):
        return math.atan(n)
    
    def root(self, n):
        if n < 0:
            error = tt.errorCode(None, None, None, None, None, None, tt.error.NEGATIVE_VALUE, 'SYNTAX ERROR. LA RAÍZ NO PUEDE SER NEGATIVA')
            return error
        correct = tt.errorCode(None, None, None, math.sqrt(n), None, None, tt.error.OK, None)
        return correct
    
    def absolute(self, n):
        if n < 0:
            n = n * -1

        return n
    
    def DecToBin(self, number):
        return bin(number)
    
    def BinToDec(self, number):
        return int(number, 2)
    
    def DecToHex(self, number):
        return hex(number)
    
    def HexToDec(self, number):
        return int(number, 16)
    
    def BinToHex(self, number):
        aux = int(number, 2)
        return hex(aux)
    
    def HexToBin(self, number):
        aux = int(number, 16)
        return bin(aux)
    
    def defineEquation(self, index, elements):
        self.definedEquations[index] = 1

        for i in range(3):
            self.equations[index][i] = elements[i]

    def sumEquation(self, eq1, eq2):
        if (self.definedEquations[eq1] == 0 or self.definedEquations[eq2] == 0):
            error = tt.errorCode(None, None, None, None, None, None, tt.error.UNDEFINED_EQUATION, 'SYNTAX ERROR. ECUACION(ES) NO DEFINIDA(S)')
            return error
        
        result = [0 for i in range(3)]

        for i in range(3):
            result[i] = self.equations[eq1][i] + self.equations[eq2][i]

        correct = tt.errorCode(result, None, None, None, None, None, tt.error.OK, None)

        return correct

    def substractEquation(self, eq1, eq2):
        if (self.definedEquations[eq1] == 0 or self.definedEquations[eq2] == 0):
            error = tt.errorCode(None, None, None, None, None, None, tt.error.UNDEFINED_EQUATION, 'SYNTAX ERROR. ECUACION(ES) NO DEFINIDA(S)')
            return error
        
        result = [0 for i in range(3)]

        for i in range(3):
            result[i] = self.equations[eq1][i] - self.equations[eq2][i]

        correct = tt.errorCode(result, None, None, None, None, None, tt.error.OK, None)

        return correct
    
    def multEquation(self, eq1, eq2):
        if (self.definedEquations[eq1] == 0 or self.definedEquations[eq2] == 0):
            error = tt.errorCode(None, None, None, None, None, None, tt.error.UNDEFINED_EQUATION, 'SYNTAX ERROR. ECUACION(ES) NO DEFINIDA(S)')
            return error
        
        result = [0 for i in range(5)]

        result[0] = self.equations[eq1][0] * self.equations[eq2][0] 
        result[1] = self.equations[eq1][0] * self.equations[eq2][1] + self.equations[eq1][1] * self.equations[eq2][0]
        result[2] = self.equations[eq1][0] * self.equations[eq2][2] + self.equations[eq1][1] * self.equations[eq2][1] + self.equations[eq1][2] * self.equations[eq2][0]
        result[3] = self.equations[eq1][1] * self.equations[eq2][2]+ self.equations[eq1][2] * self.equations[eq2][1]
        result[4] = self.equations[eq1][2] * self.equations[eq2][2]
    
        correct = tt.errorCode(result, None, None, None, None, None, tt.error.OK, None)

        return correct
    
    def solveEquation(self, eq):
        if (self.definedEquations[eq] == 0):
            error = tt.errorCode(None, None, None, None, None, None, tt.error.UNDEFINED_EQUATION, 'SYNTAX ERROR. ECUACION(ES) NO DEFINIDA(S)')
            return error

        a = float(self.equations[eq][0])
        b = float(self.equations[eq][1])
        c = float(self.equations[eq][2])

        if a != 0:
            solutions = [0 for i in range(2)]
            if b != 0:
                if c != 0:
                    sqr = solveSecondGrade(a, b, c)

                    if sqr < 0:
                        error = tt.errorCode(None, None, None, None, None, None, tt.error.NEGATIVE_VALUE, 'SYNTAX ERROR. LA RAÍZ NO PUEDE SER NEGATIVA')
                        return error
                    solutions[0] = (-b + math.sqrt(sqr)) / (2 * a)
                    solutions[1] = (-b - math.sqrt(sqr)) / (2 * a)
                else:
                    solutions[0] = 0
                    solutions[1] = solveFirstGrade(a, b)
            else:
                if c != 0:
                    sqr = -c / a
                    if sqr < 0:
                        error = tt.errorCode(None, None, None, None, None, None, tt.error.NEGATIVE_VALUE, 'SYNTAX ERROR. LA RAÍZ NO PUEDE SER NEGATIVA')
                        return error
                    solutions[0] = math.sqrt(sqr)
                    solutions[1] = -math.sqrt(sqr)
                else:
                    solutions[0] = 0
                    solutions[1] = 0
        elif b != 0:
            solutions = [0 for i in range(1)]
            if c != 0:
                solutions[0] = -c/b
            else:
                solutions[0] = 0
        else:
            if c != 0:
                error = tt.errorCode(None, None, None, None, None, None, tt.error.NO_SOLUTION, 'SYNTAX ERROR. NO HAY SOLUCIONES')
                return error
            else:
                solutions[0] = 0

        correct = tt.errorCode(solutions, None, None, None, None, None, tt.error.OK, None)

        return correct
    
    def defineSystem(self, numOfEquations, equations):
        self.numOfEquations = numOfEquations
        if numOfEquations == 2:
            for equation in range(numOfEquations):
                self.system2[equation] = equations[equation]
        else:
            for equation in range(numOfEquations):
                self.system3[equation] = equations[equation]
   
    def solveSystem(self):
        output = []
        sistema = {}
        #Switching first equation if it has a 0 in x term as we later want a system this way
        #   ax   by    cz    = d
        #   0    ey    fz    = g
        #   0    0     mz    = e
        if self.numOfEquations == 2:

            if self.system2[0][0] == 0:
                if self.system2[1][0] != 0:
                    aux = self.system2[0]
                    self.system2[0] = self.system2[1]
                    self.system2[1] = aux
               
            #Eliminate x

            multiply = -self.system2[1][0]
            div = self.system2[0][0]
            for column in range(len(self.system2[0])):
                self.system2[1][column] += (multiply / div) * self.system2[0][column]

            if self.system2[1][1] != 0:
                sistema['Tipo'] = 1
            else:
                if self.system2[1][2] == 0:
                    sistema['Tipo'] = 2
                else:
                    sistema['Tipo'] = 3

            if sistema['Tipo'] == 1:
                output.append(self.system2[1][2] / self.system2[1][1])
                output.append((self.system2[0][2] - self.system2[0][1] * output[0]) / self.system2[0][0])
            
                sistema['x'] = output[0]
                sistema['y'] = output[1]

            #Eliminate Y
        else:
            #Switch X
            if self.system3[0][0] == 0:
                if self.system3[1][0] != 0:
                    aux = self.system3[0]
                    self.system3[0] = self.system3[1]
                    self.system3[1] = aux
                elif self.system3[2][0] != 0:
                    aux = self.system3[0]
                    self.system3[0] = self.system3[2]
                    self.system3[2] = aux

            if self.system3[0][0] == 0:
                sistema['Tipo'] = 3
            else:
                #eliminating X
                div = self.system3[0][0]
                for equation in range(1, 3):
                    multiply = -self.system3[equation][0]
                    for column in range(4):
                        self.system3[equation][column] += (multiply / div) * self.system3[0][column]

                if self.system3[1][1] == 0:
                    aux = self.system3[1]
                    self.system3[1] = self.system3[2]
                    self.system3[2] = aux

                counter = 0
                notSCD = False
                for row in range(len(self.system3)):
                    counter = 0
                    for column in range(len(self.system3[0])):
                        if self.system3[row][column] == 0:
                            counter += 1
                        else:
                            break
                    if counter == len(self.system3[0]):
                        sistema['Tipo'] = 3
                        notSCD = True
                        break
                    elif counter == len(self.system3[0]) - 1:
                        sistema['Tipo'] = 2
                        notSCD = True
                        break

                if not notSCD:
                    #eliminating Y
                    if (self.system3[1][1] != 0):
                        multiply = -self.system3[2][1]
                        div = self.system3[1][1]
                        for column in range(1, len(self.system3[0])):
                            self.system3[2][column] += (multiply / div) * self.system3[1][column]

                    print(self.system3)
                    counter = 0
                    notSCD = False
                    for row in range(len(self.system3)):
                        counter = 0
                        for column in range(len(self.system3[0])):
                            if self.system3[row][column] == 0:
                                counter += 1
                        if counter == len(self.system3[0]):
                            sistema['Tipo'] = 3
                            notSCD = True
                            break
                        elif counter == len(self.system3[0]) - 1:
                            sistema['Tipo'] = 2
                            notSCD = True
                            break

                    if not notSCD:
                        z = self.system3[2][3] / self.system3[2][2]
                        y = (self.system3[1][3] - z * self.system3[1][2]) / self.system3[1][1]
                        x = (self.system3[0][3] - y * self.system3[0][1] - z * self.system3[0][2]) / self.system3[0][0]
                        sistema['Tipo'] = 1
                        sistema['x'] = x
                        sistema['y'] = y
                        sistema['z'] = z

                    
        self.system2 = [[0 for i in range(3)]for j in range(2)]
        self.system3 = [[0 for i in range(4)]for j in range(3)]
        return sistema

    def defineVector(self, index, elements):
        self.definedVectors[index] = 1

        for i in range(3):
            self.vectors[index][i] = elements[i]
    

    def sumVector(self, vec1, vec2):
        if (self.definedVectors[vec1] == 0 or self.definedVectors[vec2] == 0):
            error = tt.errorCode(None, None, None, None, None, None, tt.error.UNDEFINED_VECTOR, 'SYNTAX ERROR. VECTOR(ES) NO DEFINIDO(S)')
            return error
        
        result = [0 for i in range(3)]

        for i in range(3):
            result[i] = self.vectors[vec1][i] + self.vectors[vec2][i]

        correct = tt.errorCode(None, result, None, None, None, None, tt.error.OK, None)
        return correct

    def substractVector(self, vec1, vec2):
        if (self.definedVectors[vec1] == 0 or self.definedVectors[vec2] == 0):
            error = tt.errorCode(None, None, None, None, None, None, tt.error.UNDEFINED_VECTOR, 'SYNTAX ERROR. VECTOR(ES) NO DEFINIDO(S)')
            return error
        
        result = [0 for i in range(3)]

        for i in range(3):
            result[i] = self.vectors[vec1][i] - self.vectors[vec2][i]

        correct = tt.errorCode(None, result, None, None, None, None, tt.error.OK, None)
        return correct
    
    def multVector(self, vect1, vect2):
        if (self.definedVectors[vect1] == 0 or self.definedVectors[vect2] == 0):
            error = tt.errorCode(None, None, None, None, None, None, tt.error.UNDEFINED_VECTOR, 'SYNTAX ERROR. VECTOR(ES) NO DEFINIDO(S)')
            return error
        
        result = [0 for i in range(3)]

        result[0] = self.vectors[vect1][1] * self.vectors[vect2][2] - (self.vectors[vect1][2] * self.vectors[vect2][1])
        result[1] = -(self.vectors[vect1][0] * self.vectors[vect2][2] - (self.vectors[vect1][2] * self.vectors[vect2][0]))
        result[2] = self.vectors[vect1][0] * self.vectors[vect2][1] - (self.vectors[vect1][1] * self.vectors[vect2][0])

        correct = tt.errorCode(None, result, None, None, None, None, tt.error.OK, None)
        return correct

    def defineMatrix(self, index, elements):
        self.definedMatrixes[index] = 1

        for row in range(len(self.matrixes[index][0])):
            for column in range(len(self.matrixes[index][0])):
                self.matrixes[index][row][column] = elements[row][column]

    def sumMatrix(self, mat1, mat2):
        if (self.definedMatrixes[mat1] == 0 or self.definedMatrixes[mat2] == 0):
            error = tt.errorCode(None, None, None, None, None, None, tt.error.UNDEFINED_MATRIX, 'SYNTAX ERROR. MATRIX(ES) NO DEFINIDA(S)')
            return error

        output = []

        for row in range(len(self.matrixes[mat1][0])):
            aux = []
            for column in range(len(self.matrixes[mat1][0])):
                aux.append(self.matrixes[mat1][row][column] + self.matrixes[mat2][row][column])
            output.append(aux)

        correct = tt.errorCode(None, None, output, None, None, None, tt.error.OK, None)
        return correct

    def substractMatrix(self, mat1, mat2):
        if (self.definedMatrixes[mat1] == 0 or self.definedMatrixes[mat2] == 0):
            error = tt.errorCode(None, None, None, None, None, None, tt.error.UNDEFINED_MATRIX, 'SYNTAX ERROR. MATRIX(ES) NO DEFINIDA(S)')
            return error

        output = []

        for row in range(len(self.matrixes[mat1][0])):
            aux = []
            for column in range(len(self.matrixes[mat1][0])):
                aux.append(self.matrixes[mat1][row][column] - self.matrixes[mat2][row][column])
            output.append(aux)

        correct = tt.errorCode(None, None, output, None, None, None, tt.error.OK, None)
        return correct

    def multMatrix(self, mat1, mat2):
        if (self.definedMatrixes[mat1] == 0 or self.definedMatrixes[mat2] == 0):
            error = tt.errorCode(None, None, None, None, None, None, tt.error.UNDEFINED_MATRIX, 'SYNTAX ERROR. MATRIX(ES) NO DEFINIDA(S)')
            return error
        
        output = []
        value = 0

        for row in range(len(self.matrixes[mat1][0])):
            auxiliar_row = []
            for column in range(len(self.matrixes[mat1][0])):
                value = 0
                for aux in range(len(self.matrixes[mat1][0])):
                    value += (self.matrixes[mat1][row][aux] * self.matrixes[mat2][aux][column])
                auxiliar_row.append(value)
            
            output.append(auxiliar_row)

        correct = tt.errorCode(None, None, output, None, None, None, tt.error.OK, None)
        return correct

    def powerMatrix(self, mat1, power):
        if (self.definedMatrixes[mat1] == 0):
            error = tt.errorCode(None, None, None, None, None, None, tt.error.UNDEFINED_MATRIX, 'SYNTAX ERROR. MATRIZ NO DEFINIDA')
            return error
        

        self.matrixes[4] = self.matrixes[mat1]
        self.definedMatrixes[4] = 1
        if power == 0:
            output = []
            for row in range(len(self.matrixes[mat1][0])):
                auxRow = []
                for column in range(len(self.matrixes[mat1][0])):
                    if row == column:
                        auxRow.append(1)
                    else:
                        auxRow.append(0)
                output.append(auxRow)
        elif power > 0:
            for iterations in range(1, power):
                error = CalculadoraHandler.multMatrix(self, 4, mat1)

                if error.code == tt.error.UNDEFINED_MATRIX:
                    return error
                
                self.matrixes[4] = error.matrix
            output = self.matrixes[4]
        else:
            error = CalculadoraHandler.inverseMatrix(self, mat1)
            
            if error.code == tt.error.UNDEFINED_MATRIX or error.code == tt.error.DETERMINANT_ZERO:
                return error
            
            aux = error.matrix
            self.matrixes[4] = aux
            self.definedMatrixes[5] = 1
            self.matrixes[5] = aux
            new = -power
            for iterations in range(1, new):
                error = CalculadoraHandler.multMatrix(self, 4, 5)
                
                if error.code == tt.error.UNDEFINED_MATRIX:
                    return error
                
                self.matrixes[4] = error.matrix

            output = self.matrixes[4]

        correct = tt.errorCode(None, None, output, None, None, None, tt.error.OK, None)
        return correct
    
    def determinant(self, index):
        if self.definedMatrixes[index] == 0:
            error = tt.errorCode(None, None, None, None, None, None, tt.error.UNDEFINED_MATRIX, 'SYNTAX ERROR. MATRIZ NO DEFINIDA')
            return error

        #calculus of determinant
        det = 0

        for column in range(len(self.matrixes[index][0])):
            mult = 1
            if (column) % 2 == 1:
                mult = -1
            value = self.matrixes[index][0][column]

            smallerMatrix = []
            for row in range(len(self.matrixes[index][0])):
                auxiliarColumn = []
                for aux_column in range(len(self.matrixes[index][0])):
                    if row != 0:
                        if aux_column != column:
                            auxiliarColumn.append(self.matrixes[index][row][aux_column])
                if auxiliarColumn:
                    smallerMatrix.append(auxiliarColumn)

            if value != 0:
                det += (mult * value) * partialDeterminant(smallerMatrix)

        
        correct = tt.errorCode(None, None, None, None, det, None, tt.error.OK, None)
        return correct

    def inverseMatrix(self, index):
        if self.definedMatrixes[index] == 0:
            error = tt.errorCode(None, None, None, None, None, None, tt.error.UNDEFINED_MATRIX, 'SYNTAX ERROR. MATRIZ NO DEFINIDA')
            return error

        matrix = self.matrixes[index]

        determinante = CalculadoraHandler.determinant(self, index).det

        if determinante == 0:
            error = tt.errorCode(None, None, None, None, None, None, tt.error.DETERMINANT_ZERO, 'SYNTAX ERROR. DETERMINANTE NO PUEDE SER 0')
            return error

        adjunta = [[0 for row in range(len(matrix[0]))]for column in range(len(matrix[0]))]

        #calculate determinants
        for row in range(len(matrix[0])):
            for column in range(len(matrix[0])):       #going over all elements in the matrix
                subMatrix = []
                for detRow in range(len(matrix[0])):
                    auxiliar = []
                    for detColumn in range(len(matrix[0])):        #making a determinant for all elements
                        if detRow != row and detColumn != column:
                            auxiliar.append(matrix[detRow][detColumn])
                    if auxiliar:
                        subMatrix.append(auxiliar)
                adjunta[column][row] = math.pow(-1, (column + row)) * partialDeterminant(subMatrix)

        for row in range(len(adjunta[0])):
            for column in range(len(adjunta[0])): 
                adjunta[row][column] /= determinante

        correct = tt.errorCode(None, None, adjunta, None, None, None, tt.error.OK, None)
        return correct

    def transposeMatrix(self, index):
        if self.definedMatrixes[index] == 0:
            error = tt.errorCode(None, None, None, None, None, None, tt.error.UNDEFINED_MATRIX, 'SYNTAX ERROR. MATRIZ NO DEFINIDA')
            return error
        
        transpose = []
        matrix = self.matrixes[index]

        for row in range(len(matrix[0])):
            auxiliarRow = []
            for column in range(len(matrix[0])):
                auxiliarRow.append(matrix[column][row])
            transpose.append(auxiliarRow)


        correct = tt.errorCode(None, None, transpose, None, None, None, tt.error.OK, None)
        return correct

    def factorizacion(self, num):
        if num < 0:
            error = tt.errorCode(None, None, None, None, None, None, tt.error.NEGATIVE_VALUE, 'SYNTAX ERROR. EL VALOR NO PUEDE SER NEGATIVO')
            return error
        output = [] 
        index = 2
        output.append(1)

        while index <= num:
            if isPrimeNumber(index):
                if num % index == 0:
                    output.append(index)
                    num = num / index
                    index = 1

            index = index + 1

        correct = tt.errorCode(None, None, None, None, None, output, tt.error.OK, None)
        return correct
    
    def modulo(self, num, module):
        if module == 0:
            error = tt.errorCode(None, None, None, None, None, None, tt.error.DIVISION_ZERO, 'SYNTAX ERROR. EL MÓDULO NO PUEDE SER 0')
            return error
        
        correct = tt.errorCode(None, None, None, float(num % module), None, None, tt.error.OK, None)

        return correct
    
    def factorial(self, num):
        if num < 0:
            error = tt.errorCode(None, None, None, None, None, None, tt.error.NEGATIVE_VALUE, 'SYNTAX ERROR. EL VALOR NO PUEDE SER NEGATIVO')
            return error

        correcto = tt.errorCode(None, None, None, (math.factorial(num)), None, None, tt.error.OK, None)
        return correcto

if __name__ == "__main__":
    handler = CalculadoraHandler()
    processor = Calculadora.Processor(handler)
    transport = TSocket.TServerSocket(host = "127.0.0.0", port = 9090)
    tfactory = TTransport.TBufferedTransportFactory()
    pfactory = TBinaryProtocol.TBinaryProtocolFactory()

    server = TServer.TSimpleServer(processor, transport, tfactory, pfactory)

    print('Iniciando servidor...')
    server.serve()
    print('Fin')