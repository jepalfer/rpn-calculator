#include <iostream>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include "../gen-cpp/calculadora_types.h"
using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace CalculadoraCPP;

#include "../gen-cpp/Calculadora.h"

vector<char> operators = {'+', '-', '/', '*', '^', '!'};
vector<char> parenthesis = {'(', ')'};
vector<string> functions = {"cos", "sin", "tan", "sqr", "arccos", "arcsin", "arctan", "abs"};
map<char, int> hierarchy = {{'+', 2}, {'-', 2}, {'*', 3}, {'/', 3}, {'^', 4}};
map<int, string> systemMappedTypes = {{1, "SCD"}, {2, "SCI"}, {3, "SI"}};

vector<string> parse(string & parsing) {
    vector<string> queue;
    string buffer;
    bool startedExpression = false;

    parsing.erase(remove(parsing.begin(), parsing.end(), ' '), parsing.end());
    
    for (char token : parsing) {
        if (find(parenthesis.begin(), parenthesis.end(), token) != parenthesis.end()) {
            if (!buffer.empty()) {
                queue.push_back(buffer);
                buffer.clear();
            }

            if (!queue.empty() && token == '(') {
                if (find(parenthesis.begin(), parenthesis.end(), queue.back()[0]) == parenthesis.end() && find(functions.begin(), functions.end(), queue.back()) == functions.end() && find(operators.begin(), operators.end(), queue.back()[0]) == operators.end()) {
                    queue.push_back("*");
                }
            }

            queue.push_back(string(1, token));
            startedExpression = true;

            if (token == ')') {
                startedExpression = false;
            }
        }
        else if (find(operators.begin(), operators.end(), token) != operators.end()) {
            if (token == '-' && (startedExpression || queue.empty() && buffer.empty())) {
                buffer += token;
                startedExpression = !startedExpression;
            }
            else {
                if (!buffer.empty()) {
                    queue.push_back(buffer);
                    buffer.clear();
                }
                queue.push_back(string(1, token));
                startedExpression = true;
            }
        }
        else {
            buffer += token;
            startedExpression = false;
        }
    
    }

    if (!buffer.empty()) {
        queue.push_back(buffer);
    }

    return queue;
}

queue<string> shuntingYard(vector<string> & parsing) {
    queue<string> output;  // cola para la salida posfija
    stack<string> operatorStack;  // pila para los operadores

    for (string token : parsing) {
        // Si el token es un número, lo añadimos directamente a la salida
        if (isdigit(token[0])) {
            output.push(token);
        }
        // Si el token es una función, lo añadimos a la pila de operadores
        else if (find(functions.begin(), functions.end(), token) != functions.end()) {
            operatorStack.push(token);
        }
        // Si el token es un operador, lo procesamos según su jerarquía
        else if (find(operators.begin(), operators.end(), token[0]) != operators.end()) {
            while (!operatorStack.empty() && operatorStack.top()[0] != '(' &&
                   hierarchy[token[0]] <= hierarchy[operatorStack.top()[0]]) {
                output.push(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.push(token);
        }
        // Si el token es un paréntesis abierto, lo añadimos a la pila de operadores
        else if (token[0] == '(') {
            operatorStack.push(token);
        }
        // Si el token es un paréntesis cerrado, procesamos hasta el paréntesis abierto
        else if (token[0] == ')') {
            while (!operatorStack.empty() && operatorStack.top()[0] != '(') {
                output.push(operatorStack.top());
                operatorStack.pop();
            }
            if (!operatorStack.empty() && operatorStack.top()[0] == '(') {
                operatorStack.pop();
            }
            // Si hay una función en la pila de operadores, la añadimos a la salida
            if (!operatorStack.empty() && find(functions.begin(), functions.end(), operatorStack.top()) != functions.end()) {
                output.push(operatorStack.top());
                operatorStack.pop();
            }
        }
    }

    // Procesamos los operadores restantes
    while (!operatorStack.empty()) {
        if (operatorStack.top()[0] == '(' || operatorStack.top()[0] == ')') {
            cout << "SYNTAX ERROR" << endl;
            exit(-1);
        }
        output.push(operatorStack.top());
        operatorStack.pop();
    }

    return output;
}

double RPN(queue<string> & parsing, CalculadoraClient &client, std::shared_ptr<TTransport> &transport) {
    double result;
    stack<double> operationsStack;
    double arg1, arg2;
    string operationToken;
    errorCode _return;
    bool esNegativo = false;
    while (!parsing.empty()) {
        esNegativo = false;
        operationToken = parsing.front();
        parsing.pop();

        if (operationToken.size() > 1 && operationToken[0] == '-') {
            esNegativo = true;
        }

        if (find(functions.begin(), functions.end(), operationToken) == functions.end() &&  (find(operators.begin(), operators.end(), operationToken[0]) == operators.end()) || esNegativo) {
                cout << operationToken;
                
                operationsStack.push(stod(operationToken));
        }
        else {
            if (find(functions.begin(), functions.end(), operationToken) != functions.end() || operationToken[0] == '!') {
                arg1 = operationsStack.top();
                operationsStack.pop();

                if (operationToken == "cos") {
                    operationsStack.push(client.cosin(arg1));
                }
                else if (operationToken == "sin") {
                    operationsStack.push(client.sin(arg1));
                }
                else if (operationToken == "tan") {
                    operationsStack.push(client.tan(arg1));
                }
                else if (operationToken == "sqr") {
                    client.root(_return, arg1);

                    if (_return.code != CalculadoraCPP::error::OK) {
                        cout << _return.message << endl;
                        transport->close();
                        exit(-1);
                    }
                    
                    operationsStack.push(_return.result);
                }
                else if (operationToken == "arcsin") {
                    operationsStack.push(client.arcsin(arg1));
                }
                else if (operationToken == "arccos") {
                    operationsStack.push(client.arccos(arg1));
                }
                else if (operationToken == "arctan") {
                    operationsStack.push(client.arctan(arg1));
                }
                else if (operationToken[0] == '!') {
                    client.factorial(_return, arg1);

                    if (_return.code != CalculadoraCPP::error::OK) {
                        cout << _return.message << endl;
                        transport->close();
                        exit(-1);
                    }
                    
                    operationsStack.push(_return.result);
                }
                else if (operationToken == "abs") {
                    operationsStack.push(client.absolute(arg1));
                }
            } 
            else if (find(operators.begin(), operators.end(), operationToken[0]) != operators.end() && operationToken[0] != '!') {
                arg2 = operationsStack.top();
                operationsStack.pop();
                
                arg1 = operationsStack.top();
                operationsStack.pop();

                if (operationToken[0] == '+') {
                    operationsStack.push(client.sum(arg1, arg2));
                }
                else if (operationToken[0] == '-') {
                    operationsStack.push(client.substract(arg1, arg2));
                }
                else if (operationToken[0] == '*') {
                    operationsStack.push(client.mult(arg1, arg2));
                }
                else if (operationToken[0] == '/') {
                    client.div(_return, arg1, arg2);

                    if (_return.code != CalculadoraCPP::error::OK) {
                        cout << _return.message << endl;
                        transport->close();
                        exit(-1);
                    }

                    operationsStack.push(_return.result);
                }
                else if (operationToken[0] == '^') {
                    operationsStack.push(client.power(arg1, arg2));
                }
            }
        } 
    }
    result = operationsStack.top();
    return result;
}

int main() {
    std::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
    std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

    CalculadoraClient client(protocol);

    try {
        transport->open();
        client.ping();
        int opcion;
        cout << "Introduce el modo de la calculadora que quieres usar." << endl;
        cout << "\t1 - Cálculo algebraico." << endl;
        cout << "\t2 - Cambio de base." << endl;
        cout << "\t3 - Ecuaciones." << endl;
        cout << "\t4 - Vectores." << endl;
        cout << "\t5 - Matrices." << endl;
        cout << "\t6 - Operaciones varias." << endl;
        cout << "\t7 - Apagar calculadora." << endl;
        cin >> opcion;

        while (opcion < 1 || opcion > 7){
            cout << "Opción incorrecta." << endl;
            cout << "Introduce el modo de la calculadora que quieres usar." << endl;
            cout << "\t1 - Cálculo algebraico." << endl;
            cout << "\t2 - Cambio de base." << endl;
            cout << "\t3 - Ecuaciones." << endl;
            cout << "\t4 - Vectores." << endl;
            cout << "\t5 - Matrices." << endl;
            cout << "\t6 - Operaciones varias." << endl;
            cout << "\t7 - Apagar calculadora." << endl;
            cin >> opcion;
        }

        if (opcion == 1){
            string expresion;
            cout << " ___________________________________________________________" << endl;
            cout << "|                                                           |" << endl;
            cout << "|                  CALCULADORA  ALGEBRAICA                  |" << endl;
            cout << "|___________________________________________________________|" << endl;
            cout << "|                                                           |" << endl;
            cout << "|                   OPERACIONES ADMITIDAS                   |" << endl;
            cout << "|___________________________________________________________|" << endl;
            cout << "|                                                           |" << endl;
            cout << "|  a + b                                                    |" << endl;
            cout << "|  a - b                                                    |" << endl;
            cout << "|  a * b                                                    |" << endl;
            cout << "|  a / b                                                    |" << endl;
            cout << "|  a ^ b                                                    |" << endl;
            cout << "|  cos(a)                                                   |" << endl;
            cout << "|  sin(a)                                                   |" << endl;
            cout << "|  tan(a)                                                   |" << endl;
            cout << "|  sqr(a)                                                   |" << endl;
            cout << "|  a ^ (n / m) ===> raíz de orden n/m                       |" << endl;
            cout << "|  arcsin(a)                                                |" << endl;
            cout << "|  arctan(a)                                                |" << endl;
            cout << "|  arccos(a)                                                |" << endl;
            cout << "|  a!                                                       |" << endl;
            cout << "|  abs(a)                                                   |" << endl;
            cout << "|___________________________________________________________|" << endl;
            
            cout << "Introduce la expresión algebraica a evaluar: ";
            cin >> ws;
            std::getline(std::cin, expresion);
            cout << expresion << endl;

            vector<string> parsing = parse(expresion);

            for (string token : parsing) { 
                cout << token << " ";
            }

            cout << endl;

            queue<string> equation = shuntingYard(parsing);

            double result = RPN(equation, client, transport);

            while (!equation.empty()) {
                cout << equation.front() << " ";
                equation.pop();
            }

            cout << endl;

            cout << expresion << endl << endl << result << endl;
        }
        else if (opcion == 2){
            char initialBase, nextBase; 
            int32_t num;
            string result, conversion;
            // Introducimos la base inicial y comprobamos que sea correcta

            cout << "¿En qué base está tu número inicial? (D/B/H): ";
            cin >> initialBase;
            initialBase = toupper(initialBase);

            while (initialBase != 'D' && initialBase != 'B' && initialBase != 'H') {
                cout << "Base incorrecta." << endl;
                cout << "¿En qué base está el número inicial? (D/B/H): ";
                cin >> initialBase;
            }

            //Decimal
            if (initialBase == 'D') {
                cout << "Introduce el número en base 10: ";
                cin >> num;

                cout << "¿A qué base quieres pasar el número? (B/H): ";
                cin >>  nextBase;
                nextBase = toupper(nextBase);

                while (nextBase != 'B' && nextBase != 'H') {
                    cout << "Base incorrecta" << endl;
                    cout << "¿A qué base quieres pasar el número? (B/H): ";
                    cin >>  nextBase;
                    nextBase = toupper(nextBase);
                }

                if (nextBase == 'B') {
                    client.DecToBin(result, num);
                }
                else if (nextBase == 'H') {
                    client.DecToHex(result, num);
                }
            }
            else if (initialBase == 'B') {
                cout << "Introduce el número en base 2: ";
                cin >> num;

                cout << "¿A qué base quieres pasar el número? (D/H): ";
                cin >>  nextBase;
                nextBase = toupper(nextBase);

                while (nextBase != 'D' && nextBase != 'H') {
                    cout << "Base incorrecta" << endl;
                    cout << "¿A qué base quieres pasar el número? (D/H): ";
                    cin >>  nextBase;
                    nextBase = toupper(nextBase);
                }

                conversion = to_string(num);

                if (nextBase == 'D') {
                    num = client.BinToDec(conversion);
                }
                else if (nextBase == 'H') {
                    client.BinToHex(result, conversion);
                }
            }
            else {
                cout << "Introduce el número en base 16: ";
                cin >> conversion;

                cout << "¿A qué base quieres pasar el número? (D/B): ";
                cin >>  nextBase;
                nextBase = toupper(nextBase);

                while (nextBase != 'D' && nextBase != 'B') {
                    cout << "Base incorrecta" << endl;
                    cout << "¿A qué base quieres pasar el número? (D/B): ";
                    cin >>  nextBase;
                    nextBase = toupper(nextBase);
                }

                if (nextBase == 'D') {
                    num = client.HexToDec(conversion);
                }
                else if (nextBase == 'B') {
                    client.HexToBin(result, conversion);
                }
            }
            if (initialBase == 'D') {
                cout << to_string(num) + " = " + result << endl;
            }
            else {
                if (nextBase == 'D') {
                    cout << conversion << " = " << to_string(num) << endl;
                }
                else {
                    cout << conversion << " = " << result << endl;
                }
            }
        }
        else if (opcion == 3){
            char continueDefining = 'Y';
            int opcionEcuacion, operation, eq1, eq2, numEc;
            double a, b, c, x, y, z, independiente;
            errorCode _return;
            vector<double> solutions;
            vector<double> equation;
            vector<vector<double>> equationSystem;
            map<string, double> _systemSolutions;
            string tipo;
            vector<double> components;

            while (continueDefining == 'Y') {
                cout << "Definir ecuación" << endl;
                cout << "1:EquationA\t2:EquationB" << endl;
                cout << "3:EquationC\t4:EquationD" << endl;
                cout << "5:Sistema de ecuación lineal" << endl;
                cin >> opcionEcuacion;

                while (opcionEcuacion < 1 || opcionEcuacion > 5) {
                    cout << "Opción no reconocida" << endl;
                    cout << "Definir ecuación" << endl;
                    cout << "1:EquationA\t2:EquationB" << endl;
                    cout << "3:EquationC\t4:EquationD" << endl;
                    cout << "5:Sistema de ecuación lineal" << endl;
                    cin >> opcionEcuacion;
                }

                if (opcionEcuacion >= 1 && opcionEcuacion <= 4) {
                    cout << "Introduce el término de segundo grado: ";
                    cin >> a;
                    cout << "\nIntroduce el término de primer grado: ";
                    cin >> b;
                    cout << "\nIntroduce el término independiente: ";
                    cin >> c;

                    components.clear();

                    components.push_back(a);
                    components.push_back(b);
                    components.push_back(c);
                    client.defineEquation(opcionEcuacion - 1, components);
                    cout << "\n¿Quiere definir otra ecuación? (Y/N): ";
                    cin >> continueDefining;
                    continueDefining = toupper(continueDefining);

                    while (continueDefining != 'Y' && continueDefining != 'N') {
                        cout << "\nOpción no reconocida" << endl;
                        cout << "\n¿Quiere definir otra ecuación? (Y/N): ";
                        cin >> continueDefining;
                        continueDefining = toupper(continueDefining);
                    }
                }
                else {
                    continueDefining = 'N';
                }
            }

            if (opcionEcuacion >= 1 && opcionEcuacion <= 4) {
                cout << "¿Qué operación quieres realizar?" << endl;
                cout << "\t1 - Suma de ecuaciones" << endl;
                cout << "\t2 - Resta de ecuaciones" << endl;
                cout << "\t3 - Multiplicación de ecuaciones" << endl;
                cout << "\t4 - Resolución de ecuaciones" << endl;
            
                cin >> operation;

                while (operation < 1 || operation > 4) {
                    cout << "Operación no reconocida" << endl;
                    cout << "¿Qué operación quieres realizar?" << endl;
                    cout << "\t1 - Suma de ecuaciones" << endl;
                    cout << "\t2 - Resta de ecuaciones" << endl;
                    cout << "\t3 - Multiplicación de ecuaciones" << endl;
                    cout << "\t4 - Resolución de ecuaciones" << endl;
                
                    cin >> operation;
                }

                if (operation >= 1 && operation <= 3) {
                    cout << "Introduce el índice (1, 2, 3, 4) de la primera ecuación: ";
                    cin >> eq1;
                    cout << endl;

                    cout << "Introduce el índice (1, 2, 3, 4) de la segunda ecuación: ";
                    cin >> eq2;
                    cout << endl;

                    if (operation == 1) {
                        client.sumEquation(_return, eq1 - 1, eq2 - 1);
                    }
                    else if (operation == 2) {
                        client.substractEquation(_return, eq1 - 1, eq2 - 1);
                    }
                    else {
                        client.multEquation(_return, eq1 - 1, eq2 - 1);
                    }
                }
                else {
                    cout << "Introduce el índice (1, 2, 3, 4) de la ecuación: ";
                    cin >> eq1;
                    cout << endl;

                    client.solveEquation(_return, eq1 - 1);
                }
                if (_return.code != error::OK) {
                    cout << _return.message << endl;
                }
                else {
                    if (operation == 4) {
                        cout << "Las soluciones son: ";
                        for (size_t element = 0; element < _return.eq.size(); ++element) {
                            cout << _return.eq[element] << " ";
                        }
                        cout << endl;
                    }
                    else {
                        for (size_t element = 0; element < _return.eq.size(); ++element) {
                            cout << _return.eq[element] << " ";
                        }
                        cout << endl;
                    }
                }
            }
            else {
                cout << "¿Cuántas ecuaciones tiene tu sistema? (2-3): ";
                cin >> numEc;
                cout << endl;
                while (numEc < 2 || numEc > 3) {
                    cout << "Cantidad equivocada" << endl;
                    cout << "¿Cuántas ecuaciones tiene tu sistema? (2-3): ";
                    cin >> numEc;
                    cout << endl;
                }

                for (int eqIndex = 0; eqIndex < numEc; ++eqIndex) {
                    equation.clear();
                    cout << "Introduce la X de la ecuación " << eqIndex + 1 << ": ";
                    cin >> x;
                    cout << "\nIntroduce la Y de la ecuación " << eqIndex + 1 << ": ";
                    cin >> y;
                    cout << endl;

                    equation.push_back(x);
                    equation.push_back(y);
                    

                    if (numEc == 3) {
                        cout << "Introduce la Z de la ecuación " << eqIndex + 1 << ": ";
                        cin >> z;
                        equation.push_back(z);
                    }

                    cout << "Introduce el término independiente de la ecuación " << eqIndex + 1 << ": ";
                    cin >> independiente;
                    cout << endl;
                    equation.push_back(independiente);

                    equationSystem.push_back(equation);
                }

                client.defineSystem(numEc, equationSystem);
                client.solveSystem(_systemSolutions);

                tipo = systemMappedTypes[int(_systemSolutions["Tipo"])];

                if (tipo == "SCD") {
                    cout << "El sistema es de tipo SCD y tiene la siguiente solución: " << endl;
                    for (map<string, double>::iterator it = _systemSolutions.begin(); it != _systemSolutions.end(); ++it) {
                        if (it->first != "Tipo")
                            cout << it->first << ": " << it->second << endl;
                    }
                }
                else if (tipo == "SCI") {
                    cout << "El sistema es de tipo SCI, por tanto, tiene infinitas soluciones" << endl;
                }
                else {
                    cout << "El sistema es de tipo SI, por tanto, no tiene solución" << endl;
                }
            }
        }
        else if (opcion == 4){
            char continueDefining = 'Y';
            int opcionVector, operation, vect1, vect2;
            double x, y, z;
            errorCode _return;
            vector<double> components;

            while (continueDefining == 'Y') {
                cout << "Definir vector" << endl;
                cout << "1:VectorA\t2:VectorB" << endl;
                cout << "3:VectorC\t4:VectorD" << endl;

                cin >> opcionVector;

                while (opcionVector < 1 || opcionVector > 4) {
                    cout << "Opción no reconocida" << endl;
                    cout << "Definir vector" << endl;
                    cout << "1:VectorA\t2:VectorB" << endl;
                    cout << "3:VectorC\t4:VectorD" << endl;

                    cin >> opcionVector;
                }

                cout << "Introduce la coordenada X: ";
                cin >> x;

                cout << "\nIntroduce la coordenada Y: ";
                cin >> y;
                
                cout << "\nIntroduce la coordenada Z: ";
                cin >> z;
                components.clear();
                components.push_back(x);
                components.push_back(y);
                components.push_back(z);

                client.defineVector(opcionVector - 1, components);

                cout << "¿Quieres definir otro vector? Y/N: ";
                cin >> continueDefining;

                continueDefining = toupper(continueDefining);

                while (continueDefining != 'Y' && continueDefining != 'N') {
                    cout << "Opción no reconocida" << endl;
                    cout << "¿Quieres definir otro vector? Y/N: ";
                    cin >> continueDefining;

                    continueDefining = toupper(continueDefining);

                }
            }

            cout << "¿Qué operación quieres realizar?" << endl;
            cout << "\t1 - Suma de vectores" << endl;
            cout << "\t2 - Resta de vectores" << endl;
            cout << "\t3 - Multiplicación de vectores" << endl;

            cin >> operation;

            while (operation < 1 || operation > 3) {
                cout << "Opción no reconocida" << endl;
                cout << "¿Qué operación quieres realizar?" << endl;
                cout << "\t1 - Suma de vectores" << endl;
                cout << "\t2 - Resta de vectores" << endl;
                cout << "\t3 - Multiplicación de vectores" << endl;

                cin >> operation;
            }

            cout << "Introduce el índice (1, 2, 3, 4) del primer vector: ";
            cin >> vect1;
            cout << endl;

            cout << "Introduce el índice (1, 2, 3, 4) del segundo vector: ";
            cin >> vect2;
            cout << endl;

            if (operation == 1) {
                client.sumVector(_return, vect1 - 1, vect2 - 1);
            }
            else if (operation == 2) {
                client.substractVector(_return, vect1 - 1, vect2 - 1);
            }
            else {
                client.multVector(_return, vect1 - 1, vect2 - 1);
            }

            if (_return.code != error::OK) {
                cout << _return.message << endl;
            }
            else {
                for (size_t element = 0; element < _return.vect.size(); ++element) {
                    cout << _return.vect[element] << " ";
                }

                cout << endl;
            }
        }
        else if (opcion == 5){
            char continueDefining = 'Y';
            int opcionMatrix, operation, mat1, mat2;
            errorCode _return;
            vector<vector<double>> matrix;
            vector<vector<double>> subMatrix;
            vector<double> components;
            int power;
            double value;

            while (continueDefining == 'Y') {
                cout << "Definir matriz" << endl;
                cout << "1:MatrizA\t2:MatrizB" << endl;
                cout << "3:MatrizC\t4:MatrizD" << endl;

                cin >> opcionMatrix;

                while (opcionMatrix < 1 || opcionMatrix > 4) {
                    cout << "Opción no reconocida" << endl;
                    cout << "Definir matriz" << endl;
                    cout << "1:MatrizA\t2:MatrizB" << endl;
                    cout << "3:MatrizC\t4:MatrizD" << endl;

                    cin >> opcionMatrix;
                }
                matrix.clear();
                for (int row = 0; row < 4; ++row) {
                    components.clear();
                    for (int col = 0; col < 4; ++col) {
                        cout << "Introduce el elemento de la fila " << row + 1 << " y columna " << col + 1 << " de la matriz " << opcionMatrix << ": ";
                        cin >> value;
                        cout << endl;
                        components.push_back(value);
                    }
                    matrix.push_back(components);
                }

                client.defineMatrix(opcionMatrix - 1, matrix);

                cout << "¿Quiere definir otra matriz? Y/N: ";
                cin >> continueDefining;
                continueDefining = toupper(continueDefining);

                while (continueDefining != 'Y' && continueDefining != 'N') {
                    cout << "\nOpción no reconocida" << endl;
                    cout << "¿Quiere definir otra matriz? Y/N: ";
                    cin >> continueDefining;
                    continueDefining = toupper(continueDefining);
                }
            }

            cout << "¿Qué operación quiere realizar?" << endl;
            cout << "\t1 - Suma de matrices" << endl;
            cout << "\t2 - Resta de matrices" << endl;
            cout << "\t3 - Multiplicación de matrices" << endl;
            cout << "\t4 - Potencia de una matriz" << endl;
            cout << "\t5 - Determinante de una matriz" << endl;
            cout << "\t6 - Inversa de una matriz" << endl;
            cout << "\t7 - Transpuesta de una matriz" << endl;

            cin >> operation;

            while (operation < 1 || operation > 7) {
                cout << "Operación no reconocida" << endl;
                cout << "¿Qué operación quiere realizar?" << endl;
                cout << "\t1 - Suma de matrices" << endl;
                cout << "\t2 - Resta de matrices" << endl;
                cout << "\t3 - Multiplicación de matrices" << endl;
                cout << "\t4 - Potencia de una matriz" << endl;
                cout << "\t5 - Determinante de una matriz" << endl;
                cout << "\t6 - Inversa de una matriz" << endl;
                cout << "\t7 - Transpuesta de una matriz" << endl;

                cin >> operation;
            }

            if (operation >= 1 && operation <= 3) {
                cout << "Introduce el índice (1, 2, 3, 4) de la primera matriz: ";
                cin >> mat1;

                cout << "\nIntroduce el índice (1, 2, 3, 4) de la segunda matriz: ";
                cin >> mat2;

                if (operation == 1) {
                    client.sumMatrix(_return, mat1 - 1, mat2 - 1);
                }
                else if (operation == 2) {
                    client.substractMatrix(_return, mat1 - 1, mat2 - 1);
                }
                else {
                    client.multMatrix(_return, mat1 - 1, mat2 - 1);
                }
            }
            else if (operation == 4) {      //Potencia
                cout << "Introduce el índice (1, 2, 3, 4) de la matriz: ";
                cin >> mat1;

                cout << "\nIntroduce la potencia: ";
                cin >> power;

                client.powerMatrix(_return, mat1 - 1, power);
            }
            else if (operation == 5) {      //Determinante
                cout << "Introduce el índice (1, 2, 3, 4) de la matriz: ";
                cin >> mat1;

                client.determinant(_return, mat1 - 1);
            }
            else if (operation == 6) {      //Inversa
                cout << "Introduce el índice (1, 2, 3, 4) de la matriz: ";
                cin >> mat1;

                client.inverseMatrix(_return, mat1 - 1);
            }
            else if (operation == 7) {      //Transpuesta
                cout << "Introduce el índice (1, 2, 3, 4) de la matriz: ";
                cin >> mat1;

                client.transposeMatrix(_return, mat1 - 1);
            }

            if (_return.code != error::OK) {
                cout << _return.message << endl;
            }
            else {
                if (operation != 5) {
                    for (size_t row = 0; row < _return.matrix[0].size(); ++row) {
                        for (size_t col = 0; col < _return.matrix[0].size(); ++col) 
                            cout << _return.matrix[row][col] << " ";
                        cout << endl;
                    }
                }
                else {
                    cout << _return.det << endl;
                }
            }
        }
        else if (opcion == 6){
            errorCode _return;
            int opcionMisc, numFactoriza, numMod, mod, numFactorial;
            cout << "Selecciona la opción que quieras hacer: " << endl;
            cout << "\t1 - Factorización en números primos de un número" << endl;
            cout << "\t2 - Módulo de un número" << endl;
            cout << "\t3 - Factorial de un número" << endl;

            cin >> opcionMisc;

            while (opcionMisc < 1 || opcionMisc > 3) {
                cout << "Opción incorrecta" << endl;
                cout << "Selecciona la opción que quieras hacer: " << endl;
                cout << "\t1 - Factorización en números primos de un número" << endl;
                cout << "\t2 - Módulo de un número" << endl;
                cout << "\t3 - Factorial de un número" << endl;
                cin >> opcionMisc;
            }

            if (opcionMisc == 1) {
                cout << "Introduce el número que quieres factorizar: ";
                cin >> numFactoriza;

                cout << numFactoriza << endl;

                client.factorizacion(_return, numFactoriza); 

                if (_return.code != error::OK) {
                    cout << _return.message << endl;
                }
                else {
                    for (size_t number = 0; number < _return.factors.size() - 1; ++number) {
                        cout << _return.factors[number] << " x ";
                    }
                    cout << _return.factors[_return.factors.size() - 1] << endl;
                }

            }
            else if (opcionMisc == 2) {
                cout << "Introduce el número al que quieres hacerle el módulo: ";
                cin >> numMod;
                cout << "\nIntroduce el módulo: ";
                cin >> mod;
                cout << "\n";

                client.modulo(_return, numMod, mod);

                if (_return.code != error::OK) {
                    cout << _return.message << endl;
                }
                else {
                    cout << numMod << " % " << mod << " = " << _return.result << endl;
                }
            }
            else if (opcionMisc == 3) {
                cout << "Introduce el número al que le quieras hacer el factorial: ";
                cin >> numFactorial;
                cout << endl;

                client.factorial(_return, numFactorial);

                if (_return.code != error::OK) {
                    cout << _return.message << endl;
                }
                else {
                    cout << numFactorial << "! = " << _return.result << endl;
                }
            }
        }
        else if (opcion == 7){
            cout << "Saliendo de la calculadora . . ." << endl;
        }


        transport->close();
    } catch (TException & e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}