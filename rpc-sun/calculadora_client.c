/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "calculadora.h"
#include <stdio.h>

struct parse_part{
	float number;
	char operation;
};

struct parsing{
	struct parse_part* parse;
	int size;
};

void
dirprog_1(char *host)
{
	CLIENT *clnt;
	readdir_res  *result_1;
	nametype readdir_1_arg1;

#ifndef	DEBUG
	clnt = clnt_create (host, DIRPROG, DIRVER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = readdir_1(readdir_1_arg1, clnt);
	if (result_1 == (readdir_res *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


void
calculadoraprog_1(char *host, struct parsing parse/*, float n1, char operation, float n2*/)
{
	CLIENT *clnt;
	float  *result_1;
	float sum_1_arg1;
	float sum_1_arg2;
	float  *result_2;
	float substract_1_arg1;
	float substract_1_arg2;
	float  *result_3;
	float mult_1_arg1;
	float mult_1_arg2;
	float  *result_4;
	float div_1_arg1;
	float div_1_arg2;
	float  *result_5;
	float power_1_arg1;
	float power_1_arg2;
	float  *result_6;
	float sqr_1_arg1;
	float  *result_7;
	float sin_1_arg1;
	float  *result_8;
	float cos_1_arg1;
	float  *result_9;
	float tan_1_arg1;

#ifndef	DEBUG
	clnt = clnt_create (host, CALCULADORAPROG, CALCULADORAVER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

for (int i = 0; i < parse.size; ++i){
	if (parse.parse[i].operation != 'l'){
		printf("%c", parse.parse[i].operation);
	}
	else{

		printf("%f", parse.parse[i].number);
	}
}
exit(-1);

	/* Operation switch code goes here */
	/*
	float *stack;
	int top = -1;
	stack = (float*)malloc(parse->size*sizeof(float));
	char op;
	float num;
	float n1, n2;
	char comparison = 'l';

	for (int i = 0; i < parse->size; ++i){
		op = parse->parse[i].operation;
		num = parse->parse[i].number;

			printf("%c", op);
		if (op == comparison){			//Es un operando
			top++;
			stack[top] = num;
			printf("%f", stack[top]);
			exit(-1);
		}
		else{
			if (op == '+' || op == '-' || op == '/' || op == '*'){
				// if (top < 1){
				// 	clnt_perror(clnt, "SYNTAX ERROR");
				// }
						
				n1 = stack[top - 1];
				n2 = stack[top];

				switch(op){
					case '+':
						stack[top - 1] = *sum_1 (n1, n2, clnt);
						top--;
					break;

					case '-':
						stack[top - 1] = *substract_1 (n1, n2, clnt);
						top--;
					break;

					case '*':
						stack[top - 1] = *mult_1 (n1, n2, clnt);
						top--;
					break;

					case '/':
						if (n2 != 0){
							stack[top - 1] = *div_1 (n1, n2, clnt);
							
						}
						else{
							clnt_perror(clnt, "SYNTAX ERROR");
						}
					break;
				}
			}
		}
	}
	printf("He llegao %f", stack[top + 1]);
	exit(-1);

	if (top == 0){
		printf("El resultado de la expresión algebraica es: %f\n", stack[0]);
	}
	else if (top > 0){
		clnt_perror(clnt, "SYNTAX ERROR");
	}*/
	/*
	switch(operation){
		case '+':
			result_1 = sum_1 (n1, n2, clnt);
			printf("%f + %f = %f\n", n1, n2, *result_1);
		break;
		case '-':
			result_2 = substract_1 (n1, n2, clnt);
			printf("%f - %f = %f\n", n1, n2, *result_2);
		break;
		case '*':
			result_3 = mult_1 (n1, n2, clnt);
			printf("%f * %f = %f\n", n1, n2, *result_3);
		break;
		case '/':
			if (n2 != 0){
				result_4 = div_1 (n1, n2, clnt);
				printf("%f / %f = %f\n", n1, n2, *result_4);
			}
			else{
				clnt_perror(clnt, "SYNTAX ERROR");
			}
		break;
		case 'p':
			result_5 = power_1 (n1, n2, clnt);
			printf("%f ^ %f = %f\n", n1, n2, *result_5);
		break;
		case 'c':
			result_6 = cos_1 (n1, clnt);
			printf("cos(%f) = %f\n", n1, *result_6);
		break;
		case 't':
			result_7 = tan_1 (n1, clnt);
			printf("tan(%f) = %f\n", n1, *result_7);
		break;
		case 's':
			result_8 = sin_1 (n1, clnt);
			printf("sin(%f) = %f\n", n1, *result_8);
		break;
		case 'r':
			result_9 = sqr_1 (n1, clnt);
			printf("sqr(%f) = %f\n", n1, *result_9);
		break;
	}
	*/
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


void
calculadoraprogequ_2(char *host, char operation, equation eq1, equation eq2, int num)
{
	CLIENT *clnt;
	equation  *result_1;
	equation sumeq_2_arg1;
	equation sumeq_2_arg2;
	equation  *result_2;
	equation substracteq_2_arg1;
	equation substracteq_2_arg2;
	equation  *result_3;
	equation multeq_2_arg1;
	equation multeq_2_arg2;
	equation  *result_4;
	equation solve_2_arg1;

#ifndef	DEBUG
	clnt = clnt_create (host, CALCULADORAPROGEQU, CALCULADORAEQUVER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	/* Operation switch code goes here */
	switch(operation){
		case '+':
			result_1 = sumeq_2 (eq1, eq2, clnt);
			printf("La suma de las 2 ecuaciones es: ");
			for (int i = 0; i < result_1->equation_len; ++i){
				printf("%f ", result_1->equation_val[i]);
			}
			printf("\n");

		break;

		case '-':
			result_2 = substracteq_2 (eq1, eq2, clnt);
			printf("La resta de las 2 ecuaciones es: ");
			for (int i = 0; i < result_2->equation_len; ++i){
				printf("%f ", result_2->equation_val[i]);
			}
			printf("\n");
		break;

		case '*':
			result_3 = multeq_2 (eq1, eq2, clnt);
			printf("El producto de las 2 ecuaciones es: ");
			for (int i = 0; i < result_3->equation_len; ++i){
				printf("%f ", result_3->equation_val[i]);
			}
			printf("\n");
		break;

		case 's':
			result_4 = solve_2 (eq1, clnt);
			printf("Las soluciones a la ecuación dada son: ");
			for (int i = 0; i < result_4->equation_len; ++i){
				printf("%f ", result_4->equation_val[i]);
			}
			printf("\n");
		break;
	}

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


void
calculadoraprogvect_3(char *host, char operation, equation vect1, equation vect2, int number, int power)
{
	CLIENT *clnt;
	equation  *result_1;
	equation sumvec_3_arg1;
	equation sumvec_3_arg2;
	equation  *result_2;
	equation substractvec_3_arg1;
	equation substractvec_3_arg2;
	equation  *result_3;
	equation multvec_3_arg1;
	equation multvec_3_arg2;
	equation  *result_4;
	equation powervec_3_arg1;
	int powervec_3_arg2;

#ifndef	DEBUG
	clnt = clnt_create (host, CALCULADORAPROGVECT, CALCULADORAVECTVER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	/* Operation switch code goes here */
	switch(operation){
		case '+':
			printf("La suma de ambos vectores es:\n");
			result_1 = sumvec_3 (vect1, vect2, clnt);
			printf("(");
			for (int i = 0; i < result_1->equation_len; ++i){
				printf("%f", result_1->equation_val[i]);
				if (i < result_1->equation_len - 1){
					printf(", ");
				}
			}
			printf(")\n");
		break;

		case '-':
			printf("La resta de ambos vectores es:\n");
			result_2 = substractvec_3 (vect1, vect2, clnt);
			printf("(");
			for (int i = 0; i < result_2->equation_len; ++i){
				printf("%f", result_2->equation_val[i]);
				if (i < result_2->equation_len - 1){
					printf(", ");
				}
			}
			printf(")\n");
		break;

		case '*':
			printf("El producto de ambos vectores es:\n");
			result_3 = multvec_3 (vect1, vect2, clnt);
			printf("(");
			for (int i = 0; i < result_3->equation_len; ++i){
				printf("%f", result_3->equation_val[i]);
				if (i < result_3->equation_len - 1){
					printf(", ");
				}
			}
			printf(")\n");
		break;

		case 'p':
			printf("La potencia de ambos vectores es:\n");
			result_4 = powervec_3 (vect1, power, clnt);
			printf("(");
			for (int i = 0; i < result_4->equation_len; ++i){
				printf("%f", result_4->equation_val[i]);
				if (i < result_4->equation_len - 1){
					printf(", ");
				}
			}
			printf(")\n");
		break;
	}

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


void
calculadoraprogmat_4(char *host, char operation, matrix mat1, matrix mat2, int num, int power)
{
	CLIENT *clnt;
	matrix  *result_1;
	matrix summat_4_arg1;
	matrix summat_4_arg2;
	matrix  *result_2;
	matrix substractmat_4_arg1;
	matrix substractmat_4_arg2;
	matrix  *result_3;
	matrix multmat_4_arg1;
	matrix multmat_4_arg2;
	matrix  *result_4;
	matrix powermat_4_arg1;
	int powermat_4_arg2;

#ifndef	DEBUG
	clnt = clnt_create (host, CALCULADORAPROGMAT, CALCULADORAMATVER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	/* Operation switch code goes here */
	switch(operation){
		case '+':
			result_1 = summat_4 ((mat1), mat2, clnt);
			printf("La suma de ambas matrices es:\n");
			
			for (int i = 0; i < 4; i++){
				for (int j = 0; j < 4; j++){
					printf("%i ", (int)result_1->matrix_val[(4 * i) + j]);
				}
				printf("\n");
			}
		break;

		case '-':
			printf("La resta de ambas matrices es:\n");
			result_2 = substractmat_4 ((mat1), mat2, clnt);
			for (int i = 0; i < 4; i++){
				for (int j = 0; j < 4; j++){
					printf("%i ", (int)result_2->matrix_val[(4 * i) + j]);
				}
				printf("\n");
			}
		break;

		case '*':
			printf("El producto de ambas matrices es:\n");
			result_3 = multmat_4 ((mat1), mat2, clnt);
			for (int i = 0; i < 4; i++){
				for (int j = 0; j < 4; j++){
					printf("%i ", (int)result_3->matrix_val[(4 * i) + j]);
				}
				printf("\n");
			}
		break;

		case 'p':
			printf("La potencia de la matriz es:\n");
			result_4 = powermat_4 ((mat1), power, clnt);
			for (int i = 0; i < 4; i++){
				for (int j = 0; j < 4; j++){
					printf("%i ", (int)result_4->matrix_val[(4 * i) + j]);
				}
				printf("\n");
			}
		break;
	}

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


void
calculadoraprogmisc_5(char *host, int factNum, float number1, float module, char operation)
{
	CLIENT *clnt;
	decompose  *result_1;
	int fact_5_arg1;
	float  *result_2;
	float mod_5_arg1;
	float mod_5_arg2;

#ifndef	DEBUG
	clnt = clnt_create (host, CALCULADORAPROGMISC, CALCULADORAMISCVER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	switch(operation){
		case 'f':
			result_1 = fact_5 (factNum, clnt);
			printf("La factorización en primos de %i es:\n", factNum);
			for (int i = 0; i < result_1->decompose_len; ++i){
				if (i > 0 && i < result_1->decompose_len){
					printf(" x ");
				}
				printf("%i", (int)result_1->decompose_val[i]);
			}
			printf("\n");
		break;

		case '%':
			if (module > 0){
			result_2 = mod_5 (number1, module, clnt);

			printf("%f mod %f = %f\n", number1, module, *result_2);
			}
			else{
				clnt_perror(clnt, "SYNTAX ERROR");
			}
		break;
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}

struct parsing
shuntingYardAlgorithmFixed(char * parse, const int SIZE){
	struct parse_part parsingStack[SIZE];
	struct parse_part parsingQueue[SIZE];
	struct parsing finalParse;
	char numberAux[SIZE];

	int index_parse = 0;
	int front = 0;
	int top = 0;
	char *number;
	
	for (int i = 0; i < SIZE; i++){
			parsingStack[i].operation = 'l';
			parsingQueue[i].operation = 'l';
	}

	for (int i = 0; i < SIZE; i++){
		char token = parse[i];
		//Si metemos un carácter numérico o un punto (por los decimales)
		//llenamos un array del que rescataremos el número completo
		if ((token >= '0' && token <= '9') || token == '.'){
				numberAux[index_parse] = token;
				index_parse++;
		}

		if (token == 'c' || token == 't' || token == 's' || token == 'r'){
			parsingStack[top].operation = token;
			top++;
		}

		if (token == '+' || token == '-' || token == '*' || token == '/' || token == 'p'){
			//Tenemos un número completo, por lo que lo metemos en la cola
			
			if (index_parse > 0){
				number = (char *)malloc(index_parse*sizeof(char));
				
				for (int i = 0; i < index_parse; i++){
					number[i] = numberAux[i];
				}
				parsingQueue[front].number = atof(number);
				front++;
				index_parse = 0;
			}

			//Mientras haya otro operador en el tope y si parse[i] es asociativo por
			//izquierda y menor o igual jerarquicamente o asociativo derecho y 
			//precedencia menor en la jerarquia
			while(parsingStack[top - 1].operation != '(' && parsingStack[top - 1].operation != 'l' && top > 0 && 
				 ((token == '*' && (parsingStack[top - 1].operation == '*' || parsingStack[top - 1].operation == '/'   || parsingStack[top - 1].operation == 'p')) ||
				 (token == '/'  && (parsingStack[top - 1].operation == '*' || parsingStack[top - 1].operation == '/'   || parsingStack[top - 1].operation == 'p')) ||
				 (token == '+'  && (parsingStack[top - 1].operation == '*' || parsingStack[top - 1].operation == '/'   || parsingStack[top - 1].operation == '-' || parsingStack[top - 1].operation == '+' || parsingStack[top - 1].operation == 'p')) ||
				 (token == '-'  && (parsingStack[top - 1].operation == '*' || parsingStack[top - 1].operation == '/'   || parsingStack[top - 1].operation == '+' || parsingStack[top - 1].operation == '-' || parsingStack[top - 1].operation == 'p')))){
					parsingQueue[front].operation = parsingStack[top - 1].operation;
					parsingStack[top - 1].operation = 'l';
					front++;
					top--;
			}
				
			//Ahora tenemos que meter en la pila el operador	
			parsingStack[top].operation = token;		
			top++;
		}

		if (token == '('){
			parsingStack[top].operation = token;
			top++;
		}

		if (token == ')'){
			if (index_parse > 0){
				number = (char*) malloc (index_parse*sizeof(char));
				for (int i = 0; i < index_parse; i++){
					number[i] = numberAux[i];
				}
				parsingQueue[front].number = atof(number);
				front++;
				index_parse = 0;
			}
			while (parsingStack[top - 1].operation != '(' && top > 0){
				parsingQueue[front].operation = parsingStack[top - 1].operation;
				parsingStack[top - 1].operation = 'l';
				top--;
				front++;
			}
			if (top > 0){
				parsingStack[top - 1].operation = 'l';
				top--;
			}
			if (parsingStack[top - 1].operation == 'c' || 
				parsingStack[top - 1].operation == 't' ||
				parsingStack[top - 1].operation == 's' ||
				parsingStack[top - 1].operation == 'r' ){
					parsingQueue[front].operation = parsingStack[top - 1].operation;
					front++;
					top--;
				}
		}
	}
	char token;
	if (index_parse > 0){
		number = (char*) malloc (index_parse*sizeof(char));
		for (int i = 0; i < index_parse; i++){
			number[i] = numberAux[i];
		}
		parsingQueue[front].number = atof(number);
		front++;
		index_parse = 0;
	}

	while (top > 0){
		token = parsingStack[top - 1].operation;
		top--;

		parsingQueue[front].operation = token;
		front++;
	}
	struct parse_part finalQueue[front];

	for (int i = 0; i < front; ++i){
		finalQueue[i].number = parsingQueue[i].number;
		finalQueue[i].operation = parsingQueue[i].operation;
	}
	finalParse.parse = finalQueue;
	finalParse.size = front;
	
	return finalParse;
}

int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host sequence\n", argv[0]);
		exit (1);
	}
	host = argv[1];

	char operation;
	int option;


	//4 vectores de 3 dimensiones
	equation vectores[4];

	//4 ecuaciones de 3 términos
	equation equations[4];

	// 4 matrices de 4x4
	matrix matrixes[4];

	int vectDefinidos[4], ecDefinidas[4], matricesDefinidas[4];
	int opcionEcuaciones = -1, opcionVectores = -1, opcionMisc = -1;
	int opcionMatrices = -1;
	int seguirVectores = 1, seguirEcuaciones = 1, seguirMatrices = 1, seguirMisc = -1;
	int numEc = 0, numVect = 0, numMatriz = 0;
	int opcionCuenta = -1, vectcuenta1 = -1, vectcuenta2 = -1, eccuenta1 = -1, eccuenta2 = -1, matcuenta1 = -1, matcuenta2 = -1;
	char cont = 'l';
	float miscNumber1 = -1, miscNumber2 = 0;
	int radianes = 0;
	char radianesAceptacion = 'n';
	int power = -1;
	int factNum = -1;
	int sequenceTam = -1;

	// dirprog_1(host);

	printf("¿Qué modo de la calculadora quieres usar?\n");
	printf("\t1 - Cálculo de una secuencia numérica\n");
	printf("\t2 - Cálculo con ecuaciones\n");
	printf("\t3 - Cálculo con vectores\n");
	printf("\t4 - Cálculo de matrices\n");
	printf("\t5 - Miscelánea\n");
	printf("\t6 - Salir\n");
	scanf("%d", &option);

	while (option <= 0 || option >= 7){
		printf("Programa no disponible\n");
		printf("¿Qué modo de la calculadora quieres usar?\n");
		printf("\t1 - Cálculo de una secuencia numérica\n");
		printf("\t2 - Cálculo con ecuaciones\n");
		printf("\t3 - Cálculo con vectores\n");
		printf("\t4 - Cálculo de matrices\n");
		printf("\t5 - Miscelánea\n");
		printf("\t6 - Salir\n");
		scanf("%d", &option);

	}


	if (option == 1){
		printf(" ___________________________________________\n");
		printf("|                                           |\n");
		printf("|       MODO DE USO DE LA CALCULADORA       |\n");
		printf("|___________________________________________|\n");
		printf("|                                           |\n");
		printf("| p  potencia                               |\n");
		printf("| *  multiplicacion                         |\n");
		printf("| +  suma                                   |\n");
		printf("| -  resta                                  |\n");
		printf("| r  raiz cuadrada                          |\n");
		printf("| s  seno                                   |\n");
		printf("| t  tangente                               |\n");
		printf("| c  coseno                                 |\n");
		printf("|___________________________________________|\n");
		float n1, n2;
		char c;

		char sequence[128];
		printf("Introduce la expresión algorítmica: ");
		scanf("%s", &sequence);
		
		int tam = 0;

		for (int i = 0; sequence[i] != '\0'; i++){
			tam += 1;
		}

		struct parsing parsing;
		
		// struct parse_part *parsing;
		parsing = shuntingYardAlgorithmFixed(sequence, tam);
		// printf("Introduce la secuencia: ");
		// scanf("%f %c %f", &n1, &c, &n2);
		// for (int i = 0; i < parsing.size; ++i){
		// 	if (parsing.parse[i].operation != 'l'){
		// 		printf("%c\n", parsing.parse[i].operation);
		// 	}
		// 	else{
		// 		printf("%f\n", parsing.parse[i].number);
		// 	}
		// }

		// exit(-1);

		// calculadoraprog_1(host, parsing/*n1, c, n2*/);
		CLIENT *clnt;
		#ifndef	DEBUG
			clnt = clnt_create (host, CALCULADORAPROG, CALCULADORAVER, "udp");
			if (clnt == NULL) {
				clnt_pcreateerror (host);
				exit (1);
			}
		#endif	/* DEBUG */

		float stack[parsing.size];
		int top = 0;
		char op;
		float num, arg1, arg2;
		float *result;

		printf("El paso de infijo a posfijo es:\n");
		for (int i = 0; i < parsing.size; ++i){
			if (parsing.parse[i].operation != 'l'){
				printf("%c\n", parsing.parse[i].operation);
			}
			else{
				printf("%f\n", parsing.parse[i].number);

			}
		}

		for (int i = 0; i < parsing.size; ++i){
			num = parsing.parse[i].number;
			op = parsing.parse[i].operation;
			arg1 = stack[top - 2];
			arg2 = stack[top - 1];

			if (op == '+' || op == '-' || op == '*' || op == '/' || op == 'p'){			//No es un operando
				

				if (op == '+'){
					stack[top - 2] = *sum_1 (arg1, arg2, clnt);
					top--;
				}
				else if (op == '-'){
					stack[top - 2] = *substract_1 (arg1, arg2, clnt);
					top--;
				}
				else if (op == '*'){
					stack[top - 2] = *mult_1 (arg1, arg2, clnt);
					top--;
				}
				else if (op == '/'){
					if (arg2 == 0){
						clnt_perror(clnt, "SYNTAX ERROR");
						exit(-1);
					}
					stack[top - 2] = *div_1 (arg1, arg2, clnt);
					top--;
				}
				else if (op == 'p'){
					stack[top - 2] = *power_1 (arg1, arg2, clnt);
					top--;
				}
			}
			else if (op == 'c' || op == 's' || op == 't' || op == 'r'){
				
				if (op == 'c'){
					stack[top - 1] = *cos_1 (arg2, clnt);
					top--;
				}
				else if (op == 's'){
					stack[top - 1] = *sin_1 (arg2, clnt);
					top--;
				}
				else if (op == 't'){
					stack[top - 1] = *tan_1 (arg2, clnt);
					top--;
				}
				else if (op == 'r'){
					stack[top - 1] = *sqr_1 (arg2, clnt);
					top--;
				}
			}
			else{

				// printf("%f\n", num);
				stack[top] = num;
				top++;
			}
		}
			// if (op != 'l'){
			// 	if (op == '+' || op == '-' || op == '*' || op == '/'){
			// 		// if (top <= 1){
			// 		// 	clnt_perror(clnt, "SYNTAX ERROR");
			// 		// 	exit(-1);
			// 		// }
			// 		arg1 = stack[top - 2];
			// 		arg2 = stack[top - 1];

			// 		if (op == '+'){
			// 			stack[top - 2] = *sum_1 (arg1, arg2, clnt);
			// 			top--;
			// 		}
			// 		else if (op == '-'){
			// 			stack[top - 2] = *substract_1 (arg1, arg2, clnt);
			// 			top--;
			// 		}
			// 		else if (op == '*'){
			// 			stack[top - 2] = *mult_1 (arg1, arg2, clnt);
			// 			top--;
			// 		}
			// 		else if (op == '/'){
			// 			if (arg2 == 0){
			// 				clnt_perror(clnt, "SYNTAX ERROR");
			// 			}
			// 			stack[top - 2] = *div_1 (arg1, arg2, clnt);
			// 			top--;
			// 		}
			// 	}
			// }
			// else{
			// 	printf("ey\n");
			// 	stack[top] = num;
			// 	top++;
			// }
		printf("La salida del programa es:\n");
		printf("\n%f\n", stack[0]);

	/* Operation switch code goes here */
	/*
	float *stack;
	int top = -1;
	stack = (float*)malloc(parse->size*sizeof(float));
	char op;
	float num;
	float n1, n2;
	char comparison = 'l';

	for (int i = 0; i < parse->size; ++i){
		op = parse->parse[i].operation;
		num = parse->parse[i].number;

			printf("%c", op);
		if (op == comparison){			//Es un operando
			top++;
			stack[top] = num;
			printf("%f", stack[top]);
			exit(-1);
		}
		else{
			if (op == '+' || op == '-' || op == '/' || op == '*'){
				// if (top < 1){
				// 	clnt_perror(clnt, "SYNTAX ERROR");
				// }
						
				n1 = stack[top - 1];
				n2 = stack[top];

				switch(op){
					case '+':
						stack[top - 1] = *sum_1 (n1, n2, clnt);
						top--;
					break;

					case '-':
						stack[top - 1] = *substract_1 (n1, n2, clnt);
						top--;
					break;

					case '*':
						stack[top - 1] = *mult_1 (n1, n2, clnt);
						top--;
					break;

					case '/':
						if (n2 != 0){
							stack[top - 1] = *div_1 (n1, n2, clnt);
							
						}
						else{
							clnt_perror(clnt, "SYNTAX ERROR");
						}
					break;
				}
			}
		}
	}
	printf("He llegao %f", stack[top + 1]);
	exit(-1);

	if (top == 0){
		printf("El resultado de la expresión algebraica es: %f\n", stack[0]);
	}
	else if (top > 0){
		clnt_perror(clnt, "SYNTAX ERROR");
	}*/
	/*
	switch(operation){
		case '+':
			result_1 = sum_1 (n1, n2, clnt);
			printf("%f + %f = %f\n", n1, n2, *result_1);
		break;
		case '-':
			result_2 = substract_1 (n1, n2, clnt);
			printf("%f - %f = %f\n", n1, n2, *result_2);
		break;
		case '*':
			result_3 = mult_1 (n1, n2, clnt);
			printf("%f * %f = %f\n", n1, n2, *result_3);
		break;
		case '/':
			if (n2 != 0){
				result_4 = div_1 (n1, n2, clnt);
				printf("%f / %f = %f\n", n1, n2, *result_4);
			}
			else{
				clnt_perror(clnt, "SYNTAX ERROR");
			}
		break;
		case 'p':
			result_5 = power_1 (n1, n2, clnt);
			printf("%f ^ %f = %f\n", n1, n2, *result_5);
		break;
		case 'c':
			result_6 = cos_1 (n1, clnt);
			printf("cos(%f) = %f\n", n1, *result_6);
		break;
		case 't':
			result_7 = tan_1 (n1, clnt);
			printf("tan(%f) = %f\n", n1, *result_7);
		break;
		case 's':
			result_8 = sin_1 (n1, clnt);
			printf("sin(%f) = %f\n", n1, *result_8);
		break;
		case 'r':
			result_9 = sqr_1 (n1, clnt);
			printf("sqr(%f) = %f\n", n1, *result_9);
		break;
	}
	*/
		#ifndef	DEBUG
			clnt_destroy (clnt);
		#endif	 /* DEBUG */
	}
	else if (option == 2){
		while(seguirEcuaciones == 1){
			printf("¿Qué quieres hacer?\n");
			printf("\t1- Definir ecuación 1\n");
			printf("\t2- Definir ecuación 2\n");
			printf("\t3- Definir ecuación 3\n");
			printf("\t4- Definir ecuación 4\n");
			scanf("%i", &opcionEcuaciones);
			while (opcionEcuaciones > 4 || opcionEcuaciones < 1){
				printf("Opción no correcta.\n");
				printf("¿Qué quieres hacer?\n");
				printf("\t1- Definir ecuación 1\n");
				printf("\t2- Definir ecuación 2\n");
				printf("\t3- Definir ecuación 3\n");
				printf("\t4- Definir ecuación 4\n");
				scanf("%i", &opcionEcuaciones);
			}

			equations[opcionEcuaciones - 1].equation_len = 3;
			equations[opcionEcuaciones - 1].equation_val = (float*)malloc(3*sizeof(float));

			printf("Define la ecuación %i introduciendo ÚNICAMENTE los términos de la ecuación, de forma a*x² + b*x + c, solo hace falta introducir a, b y c separadas por un espacio:\n", (opcionEcuaciones));
			scanf("%f %f %f", &equations[opcionEcuaciones - 1].equation_val[0], &equations[opcionEcuaciones - 1].equation_val[1], &equations[opcionEcuaciones - 1].equation_val[2]);
			ecDefinidas[opcionEcuaciones - 1] = 1;

			numEc++;
			if (numEc >= 1){
				printf("¿Quiere definir otra ecuación? Y/N\n");
				scanf(" %c", &cont);

				if (cont == 'N' || cont == 'n'){
					seguirEcuaciones = 0;
				}
			}
		}

		printf("¿Qué operación quiere hacer?\n");
		printf("\t1- Sumar ecuaciones\n");
		printf("\t2- Restar ecuaciones\n");
		printf("\t3- Multiplicar ecuaciones\n");
		printf("\t4- Resolver ecuación\n");
		scanf("%i", &opcionCuenta);

		while(opcionCuenta <= 0 || opcionCuenta >= 5){
			printf("Operación incorrecta\n");
			printf("¿Qué operación quiere hacer?\n");
			printf("\t1- Sumar ecuaciones\n");
			printf("\t2- Restar ecuaciones\n");
			printf("\t3- Multiplicar ecuaciones\n");
			printf("\t4- Resolver ecuación\n");
			scanf("%i", &opcionCuenta);
		}

		if (opcionCuenta >=1 && opcionCuenta <= 3){
			if (opcionCuenta == 1){
				operation = '+';
			}
			else if (opcionCuenta == 2){
				operation = '-';
			}
			else{
				operation = '*';
			}
			printf("Primera ecuación (1, 2, 3, 4): ");
			scanf("%i", &eccuenta1);
			printf("\nSegunda ecuación (1, 2, 3, 4): ");
			scanf("%i", &eccuenta2);
			

			if (ecDefinidas[eccuenta1 - 1] != 1 || ecDefinidas[eccuenta2 - 1] != 1 ){
				printf("SYNTAX ERROR\n");
				exit(-1);
			}

		}
		else if (opcionCuenta == 4){
			printf("Selecciona la ecuación (1, 2, 3, 4): ");

			operation = 's';
			scanf("%i", &eccuenta1);

			if (ecDefinidas[eccuenta1 - 1] != 1){
				printf("SYNTAX ERROR\n");
				exit(-1);
			}

			eccuenta2 = 1;
		}
		calculadoraprogequ_2 (host, operation, equations[eccuenta1 - 1], equations[eccuenta2 - 1], eccuenta1);
	}
	else if (option == 3){
		while(seguirVectores == 1){
					printf("¿Qué quieres hacer?\n");
					printf("\t1- Definir vector 1\n");
					printf("\t2- Definir vector 2\n");
					printf("\t3- Definir vector 3\n");
					printf("\t4- Definir vector 4\n");
					scanf("%i", &opcionVectores);
					while (opcionVectores > 4 || opcionVectores < 1){
						printf("Opción no correcta.\n");
						printf("¿Qué quieres hacer?\n");
						printf("\t1- Definir vector 1\n");
						printf("\t2- Definir vector 2\n");
						printf("\t3- Definir vector 3\n");
						printf("\t4- Definir vector 4\n");
						scanf("%i", &opcionVectores);
					}


					vectores[opcionVectores - 1].equation_len = 3;
					vectores[opcionVectores - 1].equation_val = (float*)malloc(3*sizeof(float));

					printf("Define el vector %i introduciendo ÚNICAMENTE los términos de la ecuación, de forma a*x² + b*x + c, solo hace falta introducir a, b y c separadas por un espacio:\n", (opcionVectores));
					scanf("%f %f %f", &vectores[opcionVectores - 1].equation_val[0], &vectores[opcionVectores - 1].equation_val[1], &vectores[opcionVectores - 1].equation_val[2]);
					numVect++;
					vectDefinidos[opcionVectores - 1] = 1;
					if (numVect >= 1){
						printf("¿Quiere definir otro vector? Y/N\n");
						scanf(" %c", &cont);
						
						if (cont == 'N' || cont == 'n'){
							seguirVectores = 0;
						}
					}
				}

		printf("¿Qué operación quiere hacer?\n");
		printf("\t1- Sumar vectores\n");
		printf("\t2- Restar vectores\n");
		printf("\t3- Multiplicar vectores (Producto vectorial)\n");
		printf("\t4- Elevar vector a una potencia\n");
		scanf("%i", &opcionCuenta);

		while(opcionCuenta <= 0 || opcionCuenta >= 5){
			printf("Operación incorrecta\n");
			printf("¿Qué operación quiere hacer?\n");
			printf("\t1- Sumar vectores\n");
			printf("\t2- Restar vectores\n");
			printf("\t3- Multiplicar vectores (Producto vectorial)\n");
			printf("\t4- Elevar vector a una potencia\n");
			scanf("%i", &opcionCuenta);

		}

		if (opcionCuenta >=1 && opcionCuenta <= 3){
			if (opcionCuenta == 1){
					operation = '+';
			}
			else if (opcionCuenta == 2){
					operation = '-';
			}
			else if (opcionCuenta == 3){
					operation = '*';
			}
			printf("Primer vector (1, 2, 3, 4): ");
			scanf("%i", &vectcuenta1);
			printf("\nSegundo vector (1, 2, 3, 4): ");
			scanf("%i", &vectcuenta2);

			if (vectDefinidos[vectcuenta1 - 1] != 1 || vectDefinidos[vectcuenta2 - 1] != 1 ){
				printf("SYNTAX ERROR\n");
				exit(-1);
			}
		}
		else if (opcionCuenta == 4){
			operation = 'p';
			printf("Selecciona el vector a elevar  (1, 2, 3, 4): ");
			scanf("%i", &vectcuenta1);

			if (vectDefinidos[vectcuenta1 - 1] != 1){
				printf("SYNTAX ERROR\n");
				exit(-1);
			}
			vectcuenta2 = 0;
			do{
				printf("¿A qué número >= 0 lo quieres elevar?\n");
				scanf("%i", &power);
			}while (power < 0);
		}

		calculadoraprogvect_3 (host, operation, vectores[vectcuenta1 - 1], vectores[vectcuenta2 - 1], opcionVectores, power);

	}
	else if (option == 4){
		while(seguirMatrices == 1){
			printf("¿Qué quieres hacer?\n");
			printf("\t1- Definir matriz 4x4 número 1\n");
			printf("\t2- Definir matriz 4x4 número 2\n");
			printf("\t3- Definir matriz 4x4 número 3\n");
			printf("\t4- Definir matriz 4x4 número 4\n");
			scanf("%i", &opcionMatrices);
			while (opcionMatrices > 4 || opcionMatrices < 1){
					printf("Opción no correcta.\n");
					printf("¿Qué quieres hacer?\n");
					printf("\t1- Definir matriz 4x4 número 1\n");
					printf("\t2- Definir matriz 4x4 número 2\n");
					printf("\t3- Definir matriz 4x4 número 3\n");
					printf("\t4- Definir matriz 4x4 número 4\n");
					scanf("%i", &opcionMatrices);
			}


			matrixes[opcionMatrices - 1].matrix_len = 16;
			matrixes[opcionMatrices - 1].matrix_val = (float*)malloc(16*sizeof(float));

			printf("Introduce los 16 valores la matriz %i separados por un espacio y fila por fila:\n", (opcionMatrices));
				scanf("%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", 
						&matrixes[opcionMatrices - 1].matrix_val[0], &matrixes[opcionMatrices - 1].matrix_val[1], &matrixes[opcionMatrices - 1].matrix_val[2], &matrixes[opcionMatrices - 1].matrix_val[3], 
						&matrixes[opcionMatrices - 1].matrix_val[4], &matrixes[opcionMatrices - 1].matrix_val[5], &matrixes[opcionMatrices - 1].matrix_val[6], &matrixes[opcionMatrices - 1].matrix_val[7], 
						&matrixes[opcionMatrices - 1].matrix_val[8], &matrixes[opcionMatrices - 1].matrix_val[9], &matrixes[opcionMatrices - 1].matrix_val[10], &matrixes[opcionMatrices - 1].matrix_val[11], 
						&matrixes[opcionMatrices - 1].matrix_val[12], &matrixes[opcionMatrices - 1].matrix_val[13], &matrixes[opcionMatrices - 1].matrix_val[14], &matrixes[opcionMatrices - 1].matrix_val[15]);



			numMatriz++;
			matricesDefinidas[opcionMatrices - 1] = 1;
			if (numMatriz >= 1){
				printf("¿Quiere definir otra matriz? Y/N\n");
				scanf(" %c", &cont);
				if (cont == 'N' || cont == 'n'){
					seguirMatrices = 0;
				}
			}
		}

		printf("¿Qué operación quiere hacer?\n");
		printf("\t1- Sumar matrices\n");
		printf("\t2- Restar matrices\n");
		printf("\t3- Multiplicar matrices\n");
		printf("\t4- Elevar matriz a una potencia\n");
		scanf("%d", &opcionCuenta);
		while (opcionCuenta >= 5 || opcionCuenta <= 0){
					printf("Opción no correcta.\n");
					printf("¿Qué operación quiere hacer?\n");
					printf("\t1- Sumar matrices\n");
					printf("\t2- Restar matrices\n");
					printf("\t3- Multiplicar matrices\n");
					printf("\t4- Elevar matriz a una potencia\n");
					scanf("%i", &opcionCuenta);
		}

		if (opcionCuenta >=1 && opcionCuenta < 4){
			if (opcionCuenta == 1){
				operation = '+';
			}
			else if (opcionCuenta == 2){
				operation = '-';
			}
			else if (opcionCuenta == 3){
				operation = '*';
			}

			printf("Primera matriz (1, 2, 3, 4): ");
			scanf("%i", &matcuenta1);
			printf("Segunda matriz (1, 2, 3, 4): ");
			scanf("%i", &matcuenta2);

			if (matricesDefinidas[matcuenta1 - 1] != 1 || matricesDefinidas[matcuenta2 - 1] != 1 ){
				printf("SYNTAX ERROR\n");
				exit(-1);
			}
		}
		else{
			operation = 'p';
			printf("Selecciona la matriz (1, 2, 3, 4): ");
			scanf("%i", &matcuenta1);
			if (matricesDefinidas[matcuenta1 - 1] != 1){
				printf("SYNTAX ERROR\n");
				exit(-1);
			}
			
			matcuenta2 = matcuenta1;
			do{
				printf("¿A qué número >= 0 la quieres elevar? ");
				scanf("%i", &power);
			}while (power < 0);
		}

		calculadoraprogmat_4 (host, operation, matrixes[matcuenta1 - 1], matrixes[matcuenta2 - 1], opcionMatrices, power);

	}
	else if (option == 5){
		printf("¿Qué operación quieres realizar?\n");
		printf("\t1 - Factorización de un número.\n");
		printf("\t2 - Módulo de un número\n");
		scanf("%i", &opcionMisc);

		while (opcionMisc < 1 || opcionMisc > 2){
			printf("Opción incorrecta.\n");
			printf("¿Qué operación quieres realizar?\n");
			printf("\t1 - Factorización de un número.\n");
			printf("\t2 - Módulo de un número\n");
			scanf("%i", &opcionMisc);
		}

		if (opcionMisc == 1){
				operation = 'f';
				do{
					printf("¿Qué número > 0 quieres factorizar? ");
					scanf("%i", &factNum);
				}while(factNum < 0);
				miscNumber1 = 0;
				miscNumber2 = 0;
		}
		else{
			operation = '%';
			do{
				printf("¿A qué número > 0 quieres hacerle el módulo? ");
				scanf("%f", &miscNumber1);

				printf("¿Qué módulo? ");
				scanf("%f", &miscNumber2);
			}while(miscNumber1 < 0 || miscNumber2 <= 0);
			factNum = 0;
		}

		calculadoraprogmisc_5 (host, factNum, miscNumber1, miscNumber2, operation);

	}
	else if (option == 6){
		printf("Saliendo de la calculadora. . .\n");
		exit(0);
	}


	exit (0);
}
