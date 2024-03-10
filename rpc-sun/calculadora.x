const MAX= 255; /* longitud maxima de la entrada directorio */
typedef string nametype<MAX>; /* entrada directorio */
typedef struct namenode *namelist; /* enlace en el listado */
typedef float equation<5>;
typedef float matrix<16>;
typedef float decompose<MAX>;
/* rpcgen -NCa calculadora.x */
/* sudo rpcbind */
/* rpcinfo */

struct namenode {
	nametype name; /* nombre de la entrada de directorio */
	namelist next ; /* siguiente entrada */
};

/* la siguiente union se utiliza para discriminar entre llamadas con exito y llamadas con errores */
union readdir_res switch (int errno) {
	case 0:
		namelist list; /* sin error: listado del directorio */
	default:
		void; /* con error: nada */
};

program DIRPROG {
	version DIRVER {
		readdir_res READDIR(nametype) = 1;
	} =1;
} = 0x20000155;

program CALCULADORAPROG { /* Para trabajar con números normales */
	version CALCULADORAVER { 

		/**** OPERACIONES BASICAS ****/
		float SUM(float, float) = 1;
		float SUBSTRACT(float, float) = 2;
		float MULT(float, float) = 3;
		float DIV(float, float) = 4;

		/**** OPERACIONES MAS COMPLEJAS ****/
		float POWER(float, float) = 6;
		float SQR(float) = 7;
		float SIN(float) = 8;
		float COS(float) = 9;
		float TAN(float) = 10;
	} = 1;	

} = 0x20000310;


program CALCULADORAPROGEQU { /* Para trabajar con ecuaciones */
	version CALCULADORAEQUVER { 

		/**** OPERACIONES BASICAS ****/
		equation SUMEQ(equation, equation) = 1;
		equation SUBSTRACTEQ(equation, equation) = 2;
		equation MULTEQ(equation, equation) = 3;
		equation SOLVE(equation) = 4;
	} = 2;	

} = 0x20000465;

program CALCULADORAPROGVECT { /* Para trabajar con vectores */
	version CALCULADORAVECTVER { 

		/**** OPERACIONES BASICAS ****/
		equation SUMVEC(equation, equation) = 1;
		equation SUBSTRACTVEC(equation, equation) = 2;
		equation MULTVEC(equation, equation) = 3;

		/**** OPERACIONES MAS COMPLEJAS ****/
		equation POWERVEC(equation, int) = 4;
	} = 3;	

} = 0x20000620;


program CALCULADORAPROGMAT { /* Para trabajar con matrices */
	version CALCULADORAMATVER { 
		/**** OPERACIONES BASICAS ****/
		matrix SUMMAT(matrix, matrix) = 1;
		matrix SUBSTRACTMAT(matrix, matrix) = 2;
		matrix MULTMAT(matrix, matrix) = 3;

		/**** OPERACIONES MAS COMPLEJAS ****/
		matrix POWERMAT(matrix, int) = 4;
	} = 4;	

} = 0x20000775;

program CALCULADORAPROGMISC { /* Para trabajar con lo demás */
	version CALCULADORAMISCVER { 

		/**** OPERACIONES BASICAS ****/
		decompose FACT(int) = 1;
		float MOD(float, float) = 2;
	} = 5;	

} = 0x20000775;