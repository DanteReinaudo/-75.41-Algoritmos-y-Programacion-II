#define  _POSIX_C_SOURCE 200809L
#include "pila.h"
#include "strutil.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// Defino Variable Enum:
typedef enum operadores{
    suma,
    resta,
    multiplicacion,
    division,
    exponencial,
    logaritmo,
    raiz,
    ternario,
    espacio,
    invalido
}operacion;

/* Recibe un string lo compara con los operadores definidos
   y le asigna un numero entero para identificar cada operacion
   devuelve 0 si no el string no es ninguno de los operadores */
operacion asigna_operador(char* op){
	if (strcmp(op,"+") == 0) return suma;
	if (strcmp(op,"-") == 0) return resta;
	if (strcmp(op,"*") == 0) return multiplicacion;
	if (strcmp(op,"/") == 0) return division;
	if (strcmp(op,"^") == 0) return exponencial;
	if (strcmp(op,"log") == 0) return logaritmo;
	if (strcmp(op,"sqrt") == 0) return raiz;
	if (strcmp(op,"?") == 0) return ternario;
	if (strcmp(op,"") == 0) return espacio;
	return invalido;
}

/* Comprueba errores matematicos y devuelve true si hay un error */
bool comprueba_error(long a, long b, int op){
	if (b==0 && op == division){
		return true;
	}
	if (a<0 && op == raiz){
		return true;
	}
	if (b<2 && op == logaritmo){
		return true;
	}
	if (b<0 && op == exponencial){
		return true;
	}
	if (a==0 && b==0 && op == exponencial){
		return true;
	}
	return false;
}

/* Recibe el entero asociado a un operador
   y realiza la cuenta correspondiente */
long operacion_binaria(long a,long b,operacion op){
	if (op == suma) return (a+b);
	if (op == resta) return (a-b);
	if (op == multiplicacion) return (a*b);
	if (op == division) return (a/b);
	if (op == exponencial){
		double res_Pow = pow((double)a,(double)b);
		return (long) res_Pow;
	}
	double res_Log = (log((double)a) / log((double)b));
	return (long) res_Log;
}

long funcion_raiz(long a){
	double res_Sqrt = sqrt((double)a);
	return (long) res_Sqrt;
}

bool calcula_raiz(pila_t* pila, int op, long* res){

	long* a = pila_desapilar(pila);
	bool errores = comprueba_error(*a,0,op);
	if (errores == true){
		free(res);
		free(a);
		return false;
	}
	*res = funcion_raiz(*a);
	free(a);
	bool apilo = pila_apilar(pila,res);
	return (apilo);
}

bool calcula_binarias (pila_t* pila, int op , long* res){

	long* b = pila_desapilar(pila);

	if (pila_esta_vacia(pila)){
		free(res);
		free(b);
		return false;
	}

	long* a = pila_desapilar(pila);

	bool errores = comprueba_error(*a,*b,op);
	if (errores == true){
		free(res);
		free(b);
		free(a);
		return false;
	}

	*res = operacion_binaria(*a,*b,op);
	bool apilo = pila_apilar(pila,res);
	free(b);
	free(a);
	return(apilo);
}

bool calcula_ternarias(pila_t* pila, int op, long* res){

	long* c = pila_desapilar(pila);

	if (pila_esta_vacia(pila)){
		free(res);
		free(c);
		return false;
	}

	long* b = pila_desapilar(pila);

	if (pila_esta_vacia(pila)){
		free(res);
		free(c);
		free(b);
		return false;
	}

	long* a = pila_desapilar(pila);

	*res = (*a ? *b : *c);
	bool apilo = pila_apilar(pila,res);
	free(c);
	free(b);
	free(a);
	return (apilo);
}
/* Comprueba y valida tanto errores matematicos como de sintaxis
   si todo esta en orden realiza la operacion y apila en los resultados */
bool apila_comprueba (operacion op, pila_t* pila){

	if (pila_esta_vacia(pila)) return false;
	long* res = malloc(sizeof(long));
	if (res == NULL) return false;

	if (op != ternario && op != raiz) return calcula_binarias(pila,op,res);

	if (op == raiz) return calcula_raiz(pila,op,res);

	if (op == ternario) return calcula_ternarias(pila,op,res);

	return false;
}

//Valida si la expresion es numerica
bool valida_numeros(char* cadena){
	bool es_numero = true;
	int inicio = 0;
	if (cadena[0] == '-') inicio = 1;
	size_t largo = strlen(cadena);
	for (int i = inicio; i < largo; i++){
		if (isdigit(cadena[i]) == 0) es_numero = false;
	}
	return es_numero;
}

/* Recibe una arreglo de cadenas, comprueba desde el inicio,
   Si es un numero lo agrega a la pila.
   Si es un operador, realiza la operacion correspondiente con los
   ultimos elementos de la pila, desapila la cantidad de operandos
   utilizados y apila el resultado de dicha operacion.
   Si es un espacio en blanco lo ignora y sigue ejecutandose.
   Devuelve false si hubo algu error, y true si pudo ejecutarse normalmente. */
bool calculadora_polaca (pila_t* pila,char** datos){
	size_t cont = 0;
	bool apilo,condiciones;
	while (datos[cont] != NULL){
		bool excepcion = false;
		if (atol(datos[cont]) == 0 && strcmp(datos[cont],"0") == 0 ) excepcion = true;
		if (atol(datos[cont]) != 0 || excepcion == true) {
			bool es_numerico = valida_numeros(datos[cont]);
			if (es_numerico == true){
				long* numero = malloc(sizeof(long));
				if (numero == NULL) return false;
				*numero = atol(datos[cont]);
				apilo = pila_apilar(pila,numero);
				if (apilo == false){
					free(numero);
					return false;
				}
			}else return false;
		}
		else{
			operacion op = asigna_operador(datos[cont]);
			if (op == invalido) return false;
			else if (op != espacio ){
				condiciones = apila_comprueba(op,pila);
				if (condiciones == false) return false;
			}
		}
		cont++;
	}
	return true;
}

/* Imprime por pantalla el resultado de la operacion o ERROR
   en caso de que sea necesario. */
void muestra_por_pantalla(char** datos){
	bool condiciones = true;
	pila_t* resultados = pila_crear();
	if (resultados == NULL) condiciones = false;
	condiciones = calculadora_polaca(resultados,datos);
	long* valor_final = pila_desapilar(resultados);
	bool pila_vacia = pila_esta_vacia(resultados);
	if (condiciones == false || pila_vacia == false){
		fprintf(stdout,"ERROR \n");
	}else{
		fprintf(stdout,"%ld %s",*valor_final,"\n");
	}
	free(valor_final);
	while (pila_esta_vacia(resultados) == false){
		void* dato = pila_desapilar(resultados);
		free(dato);
	}
	pila_destruir(resultados);
}

// Lee la informacion por entrada normal estandar
// y realiza las operaciones correspondientes.
void obtener_informacion(){
	size_t capacidad = 0;
	char* linea = NULL;
	char sep = ' ';
	while (getline(&linea,&capacidad,stdin) != EOF){
		char** sin_salto = split(linea,'\n');
		char** ecuacion = split(sin_salto[0],sep);
		muestra_por_pantalla(ecuacion);
		free_strv(ecuacion);
		free_strv(sin_salto);
	}
	free(linea);
}

int main(){
	obtener_informacion();
	return 0;
}
