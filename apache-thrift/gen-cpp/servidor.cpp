#include <iostream>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include "../gen-cpp/Calculadora.h"
#include <vector>
#include <math.h>

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;
using namespace CalculadoraCPP;


class CalculadoraHandler : public CalculadoraIf {
    private:

        //Calculator memory

        vector<int> definedEquations;
        vector<int> definedVectors;
        vector<int> definedMatrixes;

        vector<vector<double>> equations;
        vector<vector<double>> vectors;
        vector<vector<vector<double>>> matrixes;

        vector<vector<double>> system2x2;
        vector<vector<double>> system3x3;

        int numOfEquations;

        map<char, int> mapeadoHexadecimal = {{'1', 1}, {'2', 2}, {'3', 3}, 
                                             {'4', 4}, {'5', 5}, {'6', 6}, 
                                             {'7', 7}, {'8', 8}, {'9', 9}, 
                                             {'A', 10}, {'B', 11}, {'C', 12}, 
                                             {'D', 13}, {'E', 14}, {'F', 15}};
        map<int, char> mapeadoHexadecimalReverso = {{1, '1'}, {2, '2'}, {3, '3'}, 
                                                    {4, '4'}, {5, '5'}, {6, '6'}, 
                                                    {7, '7'}, {8, '8'}, {9, '9'}, 
                                                    {10, 'A'}, {11, 'B'}, {12, 'C'}, 
                                                    {13, 'D'}, {14, 'E'}, {15, 'F'}};

        /*
        self.definedEquations = [0 for i in range(4)]
        self.definedVectors = [0 for i in range(4)]
        self.definedMatrixes = [0 for i in range(6)]
        self.equations = [[0 for i in range(3)]for i in range(4)]
        self.vectors = [[0 for i in range(3)]for i in range(4)]
        self.matrixes = [[[0 for i in range(4)]for i in range(4)]for k in range(6)]
        self.system2 = [[0 for i in range(3)]for j in range(2)]
        self.system3 = [[0 for i in range(4)]for j in range(3)]
        self.numOfEquations = 0  */
    public:
        CalculadoraHandler() {
            definedEquations = {0, 0, 0, 0};
            definedVectors = {0, 0, 0, 0};
            definedMatrixes = {0, 0, 0, 0};

            equations = vector<vector<double>>(4, vector<double>(3));
            vectors = vector<vector<double>>(4, vector<double>(3));
            matrixes = vector<vector<vector<double>>>(6, vector<vector<double>>(4, vector<double>(4)));

            numOfEquations = 0;
        }
        void ping(){
            cout << "Ping a calculadora. . ." << endl;
        }

        void changeServer(const int index) {
            cout << "No hace nada" << endl;
        }

        double sum(const double num1, const double num2){
            return num1 + num2;
        }
        
        double substract(const double num1, const double num2) {
            return num1 - num2;
        }

        double power(const double num, const double power) {
            return pow(num, power);
        }

        double mult(const double num1, const double num2) {
            return num1 * num2;
        }

        void div(CalculadoraCPP::errorCode & _return, const double num1, const double num2) {
            if (num2 == 0) {
                _return.code = CalculadoraCPP::error::DIVISION_ZERO;
                _return.message = "SYNTAX ERROR. DIVISIÓN POR 0";
            }
            else {
                _return.result = num1 / num2;
                _return.code = CalculadoraCPP::error::OK;
            }
        }

        double sin(const double num) {
            return sin(num);
        }

        double cosin(const double num) {
            return cos(num);
        }

        double tan(const double num) {
            return tan(num);
        }

        double arcsin(const double num) {
            return asin(num);
        }

        double arccos(const double num) {
            return acos(num);
        }

        double arctan(const double num) {
            return atan(num);
        }

        void root(CalculadoraCPP::errorCode & _return, const double num) {
            if (num == 0) {
                _return.code = CalculadoraCPP::error::NEGATIVE_VALUE;
                _return.message = "SYNTAX ERROR. LA RAÍZ NO PUEDE SER NEGATIVA";
            }
            else {
                _return.result = sqrt(num);
                _return.code = CalculadoraCPP::error::OK;
            }
        }

        double absolute(const double num) {
            return abs(num);
        }
        void reverseString(const string & input, string & output) {
            int index = input.size() - 1;
            output.resize(input.size());
            for (size_t character = 0; character < input.size(); ++character) {
                output[character] = input[index];
                index--;
            }
        }

        void DecToBin(string & _return, const int32_t decNum) {
            int32_t cociente = decNum;
            string binarioInverso = "";
            while (cociente != 0) {
                binarioInverso += to_string(cociente % 2);
                cociente /= 2;
            }
            reverseString(binarioInverso, _return);
        }

        
        int32_t BinToDec(const string & binNum) {
            int output = 0, index = 0;
            for (int character = binNum.size() - 1; character >= 0; --character) {
                output += pow(2, index) * int(binNum[character] - '0'); 
                index++;
            }

            return output;
        }
        
        void DecToHex(string & _return, const int32_t decNum) {
            int32_t cociente = decNum;
            string hexadecimalInverso = "";

            while (cociente != 0) {
                hexadecimalInverso += mapeadoHexadecimalReverso[cociente % 16];
                cociente /= 16;
            }

            reverseString(hexadecimalInverso, _return);
        }
        
        int32_t HexToDec(const string & HexNum) {
            int output = 0, index = 0;

            for (int character = HexNum.size() - 1; character >= 0; --character) {
                output += mapeadoHexadecimal[HexNum[character]] * pow(16, index);
                index++;
            }

            return output;
        }
        
        void HexToBin(string & _return, const string & HexNum) {
            int32_t decimal = HexToDec(HexNum);
            DecToBin(_return, decimal);
        }
        
        void BinToHex(string & _return, const string & BinNum) {
            int32_t decimal = BinToDec(BinNum);
            DecToHex(_return, decimal);
        }

        void defineEquation(const int32_t index, const vector<double> & elements) {
            definedEquations[index] = 1;

            for (size_t element = 0; element < elements.size(); ++element)
                equations[index][element] = elements[element];
        }

        void sumEquation(CalculadoraCPP::errorCode & _return, const int32_t eq1, const int32_t eq2) {
            if (definedEquations[eq1] == 0 || definedEquations[eq2] == 0) {
                _return.code = CalculadoraCPP::error::UNDEFINED_EQUATION;
                _return.message = "SYNTAX ERROR. ECUACION(ES) NO DEFINIDA(S)";
            }
            else {
                vector<double> output;

                for (size_t term = 0; term < equations[eq1].size(); ++term)
                    output.push_back(equations[eq1][term] + equations[eq2][term]);

                _return.code = CalculadoraCPP::error::OK;
                _return.eq = output;
            }
        }
        
        void substractEquation(CalculadoraCPP::errorCode & _return, const int32_t eq1, const int32_t eq2) {
            if (definedEquations[eq1] == 0 || definedEquations[eq2] == 0) {
                _return.code = CalculadoraCPP::error::UNDEFINED_EQUATION;
                _return.message = "SYNTAX ERROR. ECUACION(ES) NO DEFINIDA(S)";
            }
            else {
                vector<double> output;

                for (size_t term = 0; term < equations[eq1].size(); ++term)
                    output.push_back(equations[eq1][term] - equations[eq2][term]);

                _return.code = CalculadoraCPP::error::OK;
                _return.eq = output;
                
            }
        }
        
        void multEquation(CalculadoraCPP::errorCode & _return, const int32_t eq1, const int32_t eq2) {
            if (definedEquations[eq1] == 0 || definedEquations[eq2] == 0) {
                _return.code = CalculadoraCPP::error::UNDEFINED_EQUATION;
                _return.message = "SYNTAX ERROR. ECUACION(ES) NO DEFINIDA(S)";
            }
            else {
                vector<double> output;

                output.push_back(equations[eq1][0] * equations[eq2][0]);
                output.push_back(equations[eq1][0] * equations[eq2][1] + equations[eq1][1] * equations[eq2][0]);
                output.push_back(equations[eq1][0] * equations[eq2][2] + equations[eq1][1] * equations[eq2][1] + equations[eq1][2] * equations[eq2][0]);
                output.push_back(equations[eq1][1] * equations[eq2][2] + equations[eq1][2] * equations[eq2][1]);
                output.push_back(equations[eq1][2] * equations[eq2][2]);

                _return.code = CalculadoraCPP::error::OK;
                _return.eq = output;
                
            }
        }   
        
        void solveEquation(CalculadoraCPP::errorCode & _return, const int32_t eq) {
            if (definedEquations[eq] == 0) {
                _return.code = CalculadoraCPP::error::UNDEFINED_EQUATION;
                _return.message = "SYNTAX ERROR. ECUACION(ES) NO DEFINIDA(S)";
            }
            else {
                _return.code = CalculadoraCPP::error::OK;
                double a = equations[eq][0], b = equations[eq][1], c = equations[eq][2];
                vector<double> solutions;
                if (a != 0) {
                    if (b != 0) {
                        if (c != 0) {
                            double sqr = solveSecondGrade(a, b, c);

                            if (sqr < 0) {
                                _return.code = CalculadoraCPP::error::NEGATIVE_VALUE;
                                _return.message = "SYNTAX ERROR. LA RAÍZ NO PUEDE SER NEGATIVA";
                            }
                            else {
                                solutions.push_back((-b + sqrt(sqr)) / (2 * a));
                                solutions.push_back((-b - sqrt(sqr)) / (2 * a));
                            }
                        }
                        else {
                            solutions.push_back(0);
                            solutions.push_back(solveFirstGrade(a, b));                            
                        }
                    }
                    else {
                        if (c != 0) {
                            double sqr = solveFirstGrade(a, c);

                            if (sqr < 0) {
                                _return.code = CalculadoraCPP::error::NEGATIVE_VALUE;
                                _return.message = "SYNTAX ERROR. LA RAÍZ NO PUEDE SER NEGATIVA";
                            }
                            else {
                                solutions.push_back(sqrt(sqr));
                                solutions.push_back(-sqrt(sqr));
                            }
                        }
                        else {
                            solutions.push_back(0);
                            solutions.push_back(0);
                        }
                    }
                }
                else if (b != 0) {
                    if (c != 0) {
                        solutions.push_back(solveFirstGrade(b, c));
                    }
                    else {
                        solutions.push_back(0);
                    }
                }
                else {
                    if (c != 0) {
                        _return.code = CalculadoraCPP::error::NO_SOLUTION;
                        _return.message = "SYNTAX ERROR. NO HAY SOLUCIONES";
                    }
                    else {
                        solutions.push_back(0);
                    }
                }

                if (_return.code == 0) {
                    _return.eq = solutions;
                }
            }
        }
        
        void defineSystem(const int32_t numOfEquations, const vector<vector<double> > & equations) {
            this->numOfEquations = numOfEquations;
            if (numOfEquations == 2) {
                for (int32_t equation = 0; equation < numOfEquations; ++equation)
                    system2x2.push_back(equations[equation]);
            }
            else {
                for (int32_t equation = 0; equation < numOfEquations; ++equation)
                    system3x3.push_back(equations[equation]);
            }
        }
        
        void solveSystem(map<string, double> & _return) {
            vector<double> output;
        // #Switching first equation if it has a 0 in x term as we later want a system this way
        // #   ax   by    cz    = d
        // #   0    ey    fz    = g
        // #   0    0     mz    = e
            if (numOfEquations == 2) {
                if (system2x2[0][0] == 0) {
                    if (system2x2[1][0] != 0) {
                        vector<double> aux = system2x2[0];
                        system2x2[0] = system2x2[1];
                        system2x2[1] = aux;
                    }
                }
                //     Eliminate x
                double multiply = -system2x2[1][0];
                double div = system2x2[0][0];

                for (size_t column = 0; column < system2x2[0].size(); ++column) {
                    system2x2[1][column] += (multiply / div) * system2x2[0][column];
                }

                if (system2x2[1][1] != 0) {
                    _return["Tipo"] = 1;
                }
                else {
                    if (system2x2[1][2] == 0) {
                        _return["Tipo"] = 2;
                    }
                    else {
                        _return["Tipo"] = 3;
                    }
                }

                if (_return["Tipo"] == 1) {
                    output.push_back(system2x2[1][2] / system2x2[1][1]);
                    output.push_back((system2x2[0][2] - (system2x2[0][1] * output[0])) / system2x2[0][0]);
                }

                _return["x"] = output[0];
                _return["y"] = output[1];

                system2x2.clear();
            }
            else {
                if (system3x3[0][0] == 0) {
                    if (system3x3[1][0] != 0) {
                        vector<double> aux = system3x3[0];
                        system3x3[0] = system3x3[1];
                        system3x3[1] = aux;
                    }
                    else if (system3x3[2][0] != 0) {
                        vector<double> aux = system3x3[0];
                        system3x3[0] = system3x3[2];
                        system3x3[2] = aux;
                    }
                }

                if (system3x3[0][0] == 0) {
                    _return["Tipo"] = 3;
                }
                else {
                    double div = system3x3[0][0];

                    for (size_t equation = 1; equation < system3x3.size(); ++equation) {
                        double multiply = -system3x3[equation][0];

                        for (size_t column = 0; column < system3x3[0].size(); ++column) {
                            system3x3[equation][column] += (multiply / div) * system3x3[0][column];
                        }
                    }

                    if (system3x3[1][1] == 0) {
                        vector<double> aux = system3x3[1];
                        system3x3[1] = system3x3[2];
                        system3x3[2] = aux;
                    }

                    int counter = 0;
                    bool isSCD = true;

                    for (size_t row = 0; row < system3x3.size(); ++row) {
                        counter = 0;
                        for (size_t column = 0; column < system3x3[0].size(); ++column) {
                            if (system3x3[row][column] == 0) {
                                counter++;
                            }
                            else {
                                break;
                            }
                        }

                        if (size_t(counter) == system3x3[0].size()) {
                            _return["Tipo"] = 3;
                            isSCD = false;
                            break;
                        }
                        else if (size_t(counter) == (system3x3[0].size() - 1)) {
                            _return["Tipo"] = 2;
                            isSCD = false;
                            break;
                        }
                    }

                    if (isSCD) {
                        double multiply = -system3x3[2][1], div = system3x3[1][1];
                        if (system3x3[1][1] != 0) {
                            for (size_t column = 1; column < system3x3[0].size(); ++column) {
                                system3x3[2][column] += (multiply / div) * system3x3[1][column];
                            }
                        }
                        isSCD = true;

                        for (size_t row = 0; row < system3x3.size(); ++row) {
                            counter = 0;
                            for (size_t column = 0; column < system3x3[0].size(); ++column) {
                                if (system3x3[row][column] == 0) {
                                    counter++;
                                }
                                else {
                                    break;
                                }
                            }
                            
                            if (size_t(counter) == system3x3[0].size()) {
                                _return["Tipo"] = 3;
                                isSCD = false;
                                break;
                            } 
                            else if (size_t(counter) == (system3x3[0].size() - 1)) {
                                _return["Tipo"] = 2;
                                isSCD = false;
                                break;
                            } 
                        }

                        if (isSCD) {
                            double z = system3x3[2][3] / system3x3[2][2];
                            double y = (system3x3[1][3] - z * system3x3[1][2]) / system3x3[1][1];
                            double x = (system3x3[0][3] - y * system3x3[0][1] - z * system3x3[0][2]) / system3x3[0][0];
                            _return["Tipo"] = 1;
                            _return["x"] = x;
                            _return["y"] = y;
                            _return["z"] = z;
                        }
                    }
                }
                system3x3.clear();
            }
        }


        void defineVector(const int32_t index, const vector<double> & elements) {
            definedVectors[index] = 1;

            for (size_t element = 0; element < elements.size(); ++element)
                vectors[index][element] = elements[element];
        }

        void sumVector(CalculadoraCPP::errorCode & _return, const int32_t vec1, const int32_t vec2) {
            if (definedVectors[vec1] == 0 || definedVectors[vec2] == 0) {
                _return.code = CalculadoraCPP::error::UNDEFINED_VECTOR;
                _return.message = "SYNTAX ERROR. VECTOR(ES) NO DEFINIDO(S)";
            }
            else {
                vector<double> output;
                for (size_t element = 0; element < vectors[vec1].size(); ++element)
                    output.push_back(vectors[vec1][element] + vectors[vec2][element]);
                _return.vect = output;
                _return.code = CalculadoraCPP::error::OK;
            }
        }
        
        void substractVector(CalculadoraCPP::errorCode & _return, const int32_t vec1, const int32_t vec2) {
            if (definedVectors[vec1] == 0 || definedVectors[vec2] == 0) {
                _return.code = CalculadoraCPP::error::UNDEFINED_VECTOR;
                _return.message = "SYNTAX ERROR. VECTOR(ES) NO DEFINIDO(S)";            
            }
            else {
                vector<double> output;
                for (size_t element = 0; element < vectors[vec1].size(); ++element)
                    output.push_back(vectors[vec1][element] - vectors[vec2][element]);
                _return.vect = output;
                _return.code = CalculadoraCPP::error::OK;
            }
        }
        
        void multVector(CalculadoraCPP::errorCode & _return, const int32_t vec1, const int32_t vec2) {
            if (definedVectors[vec1] == 0 || definedVectors[vec2] == 0) {
                _return.code = CalculadoraCPP::error::UNDEFINED_VECTOR;
                _return.message = "SYNTAX ERROR. VECTOR(ES) NO DEFINIDO(S)";            
            }
            else {
                vector<double> output;
                
                output.push_back((vectors[vec1][1] * vectors[vec2][2]) - (vectors[vec1][2] * vectors[vec2][1]));
                output.push_back((vectors[vec1][0] * vectors[vec2][2]) - (vectors[vec1][2] * vectors[vec2][0]));
                output.push_back((vectors[vec1][0] * vectors[vec2][1]) - (vectors[vec1][1] * vectors[vec2][0]));

                _return.vect = output;
                _return.code = CalculadoraCPP::error::OK;
            }
        }

        void defineMatrix(const int32_t index, const vector<vector<double>> & elements) {
            definedMatrixes[index] = 1;

            for (size_t row = 0; row < elements.size(); ++row)
                for (size_t column = 0; column < elements.size(); ++column)
                    matrixes[index][row][column] = elements[row][column];
        }

        void sumMatrix(CalculadoraCPP::errorCode & _return, const int32_t mat1, const int32_t mat2) {
            if (definedMatrixes[mat1] == 0 || definedMatrixes[mat2] == 0) {
                _return.code = CalculadoraCPP::error::UNDEFINED_MATRIX;
                _return.message = "SYNTAX ERROR. MATRIX(ES) NO DEFINIDA(S)";            
            }
            else {
                vector<vector<double>> output = {{0, 0, 0, 0},
                                                 {0, 0, 0, 0},
                                                 {0, 0, 0, 0},
                                                 {0, 0, 0, 0}};
                for (size_t row = 0; row < matrixes[mat1][0].size(); ++row)
                    for (size_t column = 0; column < matrixes[mat1][0].size(); ++column)
                        output[row][column] = matrixes[mat1][row][column] + matrixes[mat2][row][column];
                
                _return.code = CalculadoraCPP::error::OK;
                _return.matrix = output;
            }
        }
        
        void substractMatrix(CalculadoraCPP::errorCode & _return, const int32_t mat1, const int32_t mat2) {
            if (definedMatrixes[mat1] == 0 || definedMatrixes[mat2] == 0) {
                _return.code = CalculadoraCPP::error::UNDEFINED_MATRIX;
                _return.message = "SYNTAX ERROR. MATRIX(ES) NO DEFINIDA(S)";  
            }
            else {                
                vector<vector<double>> output = {{0, 0, 0, 0},
                                                 {0, 0, 0, 0},
                                                 {0, 0, 0, 0},
                                                 {0, 0, 0, 0}};
                for (size_t row = 0; row < matrixes[mat1][0].size(); ++row)
                    for (size_t column = 0; column < matrixes[mat1][0].size(); ++column)
                        output[row][column] = matrixes[mat1][row][column] - matrixes[mat2][row][column];

                _return.matrix = output;
                _return.code = CalculadoraCPP::error::OK;
            }
        }
        
        void multMatrix(CalculadoraCPP::errorCode & _return, const int32_t mat1, const int32_t mat2) {
            if (definedMatrixes[mat1] == 0 || definedMatrixes[mat2] == 0) {
                _return.code = CalculadoraCPP::error::UNDEFINED_MATRIX;
                _return.message = "SYNTAX ERROR. MATRIX(ES) NO DEFINIDA(S)";  
            }
            else {
                vector<vector<double>> output = {{0, 0, 0, 0},
                                                 {0, 0, 0, 0},
                                                 {0, 0, 0, 0},
                                                 {0, 0, 0, 0}};
                
                for (size_t row = 0; row < matrixes[mat1][0].size(); ++row)
                    for (size_t column = 0; column < matrixes[mat1][0].size(); ++column)
                        for (size_t aux = 0; aux < matrixes[mat1][0].size(); ++aux)
                            output[row][column] += matrixes[mat1][row][aux] * matrixes[mat2][aux][column];

                _return.code = CalculadoraCPP::error::OK;
                _return.matrix = output;
            }
        }
        
        void powerMatrix(CalculadoraCPP::errorCode & _return, const int32_t mat1, const int32_t power) {
            if (definedMatrixes[mat1] == 0) {
                _return.code = CalculadoraCPP::error::UNDEFINED_MATRIX;
                _return.message = "SYNTAX ERROR. MATRIZ NO DEFINIDA";  
            }
            else {

                if (power < 0) {
                    inverseMatrix(_return, mat1);

                    if (_return.code == 4 || _return.code == 5) {
                    }
                    else {
                        definedMatrixes[5] = 1;
                        definedMatrixes[4] = 1;

                        matrixes[4] = _return.matrix;
                        matrixes[5] = _return.matrix;
                        _return.code = CalculadoraCPP::error::OK;
                        for (int32_t iteration = 1; iteration < (-1*power); ++iteration) {
                            multMatrix(_return, 4, 5);

                            if (_return.code == 5) {
                                break;
                            }
                            else {
                                matrixes[5] = _return.matrix;
                            }
                        }

                        if (_return.code == CalculadoraCPP::error::OK)
                            _return.matrix = matrixes[5];
                    }

                }
                else if (power == 0) {
                    vector<vector<double>> output = {{1, 0, 0, 0},
                                                     {0, 1, 0, 0},
                                                     {0, 0, 1, 0},
                                                     {0, 0, 0, 1}};
                    
                    _return.code = CalculadoraCPP::error::OK;
                    _return.matrix = output;
                }
                else {
                    _return.code = CalculadoraCPP::error::OK;
                    matrixes[4] = matrixes[mat1];
                    definedMatrixes[4] = 1;
                    for (int32_t iteration = 1; iteration < power; ++iteration) {
                        multMatrix(_return, mat1, 4);
                        if (_return.code == 5) {
                        }
                        else {
                            matrixes[4] = _return.matrix;
                        }
                    }
                    if (_return.code == CalculadoraCPP::error::OK) {
                        _return.matrix = matrixes[4];
                    }
                    
                }
            }
        }
        
        void determinant(CalculadoraCPP::errorCode & _return, const int32_t matrixIndex) {
            if (definedMatrixes[matrixIndex] == 0) {
                _return.code = CalculadoraCPP::error::UNDEFINED_MATRIX;
                _return.message = "SYNTAX ERROR. MATRIZ NO DEFINIDA"; 
            }
            else {
                //calculus of determinant
                double det = 0;

                vector<vector<double>> subMatrix;
                    vector<double> auxiliar;
                for (size_t column = 0; column < matrixes[matrixIndex][0].size(); ++column) {
                    double mult = 1;
                    if (column % 2 == 1) {
                        mult = -1;
                    }
                    double value = matrixes[matrixIndex][0][column];

                    subMatrix.clear();

                    for (size_t row = 0; row < matrixes[matrixIndex][0].size(); ++row) {
                        auxiliar.clear();
                        for (size_t auxiliarColumn = 0; auxiliarColumn < matrixes[matrixIndex][0].size(); ++auxiliarColumn) {
                            if (row != 0) {
                                if (auxiliarColumn != column) {
                                    auxiliar.push_back(matrixes[matrixIndex][row][auxiliarColumn]);
                                }
                            }
                        }
                        if (!auxiliar.empty()) {
                            subMatrix.push_back(auxiliar);
                        }
                    }
                    if (value != 0) {
                        det += (mult * value * partialDeterminant(subMatrix));
                    }
                }

                _return.code = CalculadoraCPP::error::OK;
                _return.det = det;
            }
        }
        
        void inverseMatrix(CalculadoraCPP::errorCode & _return, const int32_t matrixIndex) {
            if (definedMatrixes[matrixIndex] == 0) {
                _return.code = CalculadoraCPP::error::UNDEFINED_MATRIX;
                _return.message = "SYNTAX ERROR. MATRIZ NO DEFINIDA"; 
            }
            else {           
                vector<vector<double>> matrix = matrixes[matrixIndex];

                determinant(_return, matrixIndex);

                if (_return.det == 0) {
                    _return.code = CalculadoraCPP::error::DETERMINANT_ZERO;
                    _return.message = "SYNTAX ERROR. EL DETERMINANTE NO PUEDE SER 0";
                }
                else {
                    vector<vector<double>> adjunta(4, vector<double>(4, 0));
                    //Calculate determinants
                    
                    for (size_t row = 0; row < matrix[0].size(); ++row) {
                        for (size_t column = 0; column < matrix[0].size(); ++column) {
                            vector<vector<double>> subMatrix;
                            for (size_t detRow = 0; detRow < matrix[0].size(); ++detRow) {
                                vector<double> aux;
                                for (size_t detCol = 0; detCol < matrix[0].size(); ++detCol) {
                                    if (detRow != row && detCol != column) {
                                        aux.push_back(matrix[detRow][detCol]);
                                    }
                                }
                                if (aux.size() > 0) {
                                    subMatrix.push_back(aux);
                                }
                            }
                            adjunta[column][row] = pow(-1, (column + row)) * partialDeterminant(subMatrix);
                        }
                    }

                    for (size_t row = 0; row < adjunta[0].size(); ++row) {
                        for (size_t column = 0; column < adjunta[0].size(); ++column) {
                            adjunta[row][column] /= _return.det;
                        }
                    }
                    _return.code = CalculadoraCPP::error::OK;
                    _return.matrix = adjunta;
                }

            }
        }
        
        void transposeMatrix(CalculadoraCPP::errorCode & _return, const int32_t matrixIndex) {
            if (definedMatrixes[matrixIndex] == 0) {
                _return.code = CalculadoraCPP::error::UNDEFINED_MATRIX;
                _return.message = "SYNTAX ERROR. MATRIZ NO DEFINIDA"; 
            }
            else {
                vector<vector<double>> output = {{0, 0, 0, 0},
                                                 {0, 0, 0, 0},
                                                 {0, 0, 0, 0},
                                                 {0, 0, 0, 0}};

                for (size_t row = 0; row < matrixes[matrixIndex][0].size(); ++row)
                    for (size_t column = 0; column < matrixes[matrixIndex][0].size(); ++column)
                        output[row][column] = matrixes[matrixIndex][column][row];

                _return.matrix = output;
                _return.code = CalculadoraCPP::error::OK;
            }
        }
        

        void factorizacion(CalculadoraCPP::errorCode & _return, const int32_t num) {
            if (num < 0) {
                _return.code = CalculadoraCPP::error::NEGATIVE_VALUE;
                _return.message = "SYNTAX ERROR. EL VALOR NO PUEDE SER NEGATIVO"; 
            }
            else {
                int32_t aux = num;

                vector<int32_t> factors;
                factors.push_back(1);

                for (int i = 2; i <= aux; ++i){
                    if (esPrimo(i)){
                        if (aux % i == 0){
                            factors.push_back(i);
                            aux = int(aux / i);
                            i = 1;
                        }
                    }
                }

                _return.code = CalculadoraCPP::error::OK;
                _return.factors = factors;
            }
        }

        void factorial(CalculadoraCPP::errorCode & _return, const int32_t num) {
            if (num < 0) {
                _return.code = CalculadoraCPP::error::NEGATIVE_VALUE;
                _return.message = "SYNTAX ERROR. EL VALOR NO PUEDE SER NEGATIVO"; 
            }
            else {
                _return.code = CalculadoraCPP::error::OK;
                _return.result = double(factorialRecursive(num));
            }
        }

        void modulo(CalculadoraCPP::errorCode & _return, const int32_t num, const int32_t mod) {
            if (mod == 0) {
               _return.code = CalculadoraCPP::error::DIVISION_ZERO;
               _return.message = "SYNTAX ERROR. NO SE PUEDE DIVIDIR POR 0";
            }
            else {
                _return.code = CalculadoraCPP::error::OK;
                _return.result = double(num % mod);
            }
            
        }

        int32_t factorialRecursive(const int32_t n) {
            if (n <= 1){
                return 1;
            }
            else {
                return factorialRecursive(n - 1) * n;
            }
        }

        bool esPrimo(const int32_t num) {
            bool primo = true;

            if (num != 1 && num != 2 && num != 3){
                for (int i = 2; i <= sqrt(num); ++i){
                    if (num % i == 0){
                        primo = false;
                        break;
                    }
                }
            }
            return primo;
        }

        double partialDeterminant(vector<vector<double>> subMatrix) {
            //Caso base

            double det = 0;
            if (subMatrix.size() == 2) {
                return (subMatrix[0][0] * subMatrix[1][1] - (subMatrix[0][1] * subMatrix[1][0]));
            }
            else {
                vector<vector<double>> smallerMatrix;
                vector<double> auxiliarMatrix;
                for (size_t column = 0; column < subMatrix.size(); ++column) {
                    int mult = 1;

                    if (column % 2 == 1) {
                        mult = -1;
                    }
                    smallerMatrix.clear();
                    double value = subMatrix[0][column];
                    for (size_t row = 0; row < subMatrix.size(); ++row) {
                        auxiliarMatrix.clear();
                        for (size_t aux_column = 0; aux_column < subMatrix.size(); ++aux_column) {
                            if (row != 0) {
                                if (aux_column != column) {
                                    auxiliarMatrix.push_back(subMatrix[row][aux_column]);
                                }
                            }
                        }
                        if (auxiliarMatrix.size() > 0) {
                            smallerMatrix.push_back(auxiliarMatrix);   
                        }
                    
                    }
                    det += (mult * value * partialDeterminant(smallerMatrix));
                }
            }
            return det;
        }

        double solveSecondGrade(double a, double b, double c) {
            return pow(b, 2) - (4 * a * c); 
        }

        double solveFirstGrade(double a, double b) {
            return -b / a;
        }
};

int main() {
    shared_ptr<CalculadoraHandler> handler(new CalculadoraHandler());
    shared_ptr<TProcessor> processor(new CalculadoraProcessor(handler));
    shared_ptr<TServerTransport> serverTransport(new TServerSocket(9090));
    shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    TThreadedServer server(processor, serverTransport, transportFactory, protocolFactory);

    cout << "Iniciando servidor..." << endl;
    server.serve();
    cout << "Fin" << endl;

    return 0;
}
