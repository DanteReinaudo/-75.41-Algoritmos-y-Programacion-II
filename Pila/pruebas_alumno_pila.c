#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * ******************************************************************/

void prueba_generica(){
	printf("INICIO DE PRUEBA GENERICA \n");

	// Creo pila
	pila_t* pila1 = pila_crear();

	//Verifico si la pila fue creada
	print_test("La pila fue creada", pila1 != NULL);

	// Pruebo que al crear una pila esta vacia
	print_test("La pila esta vacia", pila_esta_vacia(pila1));

	//Pruebo que no hay tope en una pila recien creado
	print_test("El tope no existe", pila_ver_tope(pila1)==NULL);

	// Pruebo que no puedo desapilar una pila vacio
	print_test("Desapilar una pila vacía", pila_desapilar(pila1)==NULL);

	// Apilo varias veces
	int v1 = 1;
	float v2 = 0.5;
	print_test("Apilo un entero v1 a la pila", pila_apilar(pila1,&v1));
	print_test("Apilo un float v2 a la pila", pila_apilar(pila1,&v2));

	//Compruebo que puedo apilar el puntero NULL
	print_test("Apilo un puntero NULL", pila_apilar(pila1,NULL));

	//Compruebo que el tope es el puntero NULL
	print_test("Observo cual es el tope, debe ser el NULL", pila_ver_tope(pila1) == NULL);

	// Sigo apilando
	char* v3 = "a";
	char* v4 = "HOLA";
	int v5[] = {1,2,3,4};
	print_test("Apilo un char v3 a la pila", pila_apilar(pila1,&v3));
	print_test("Apilo un string v4 a la pila", pila_apilar(pila1, &v4));
	print_test("Apilo un vector v5 a la pila", pila_apilar(pila1,&v5));

	// Pruebo que ahora la pila no esta vacio
	print_test("La pila no esta vacia", !pila_esta_vacia(pila1));

	//Desapilo varias veces
	print_test("Desapilo el ultimo, en este caso es el vector", pila_desapilar(pila1) == v5);
	print_test("Desapilo el ultimo, en este caso es la cadena ",pila_desapilar(pila1) == &v4);
	print_test("Desapilo el ultimo, en este caso es el char", pila_desapilar(pila1) == &v3);

	//Desapilo el NULL
	print_test("Desapilo el ultimo, en este caso es el NULL", pila_desapilar(pila1) == NULL);

	//Pruebo que la pila no esta vacia
	print_test("La pila no esta vacia", !pila_esta_vacia(pila1));

	// Compruebo el tope de la pila
	print_test("Compruebo el tope, en este caso el float", pila_ver_tope(pila1) == &v2);

	//Continuo desapilando
	print_test("Desapilo el ultimo, en este caso es el float", pila_desapilar(pila1) == &v2);
	print_test("Desapilo el ultimo, en este caso es el entero", pila_desapilar(pila1) == &v1);

	//Pruebo que no puedo seguir desapilando
	print_test("Desapilo la pila vacia", pila_desapilar(pila1) == NULL);

	// Compruebo que no hay tope
	print_test("Compruebo que no hay tope", pila_ver_tope(pila1)==NULL);

	// Compruebo que la pila esta vacia
	print_test("La pila esta vacia", pila_esta_vacia(pila1));

	//Destruyo la pila
	pila_destruir(pila1);
}

void prueba_volumen(){
	printf("INICIO DE PRUEBA DE VOLUMEN \n");

	// Creo pila
	pila_t* pila2 = pila_crear();

	//Apilo varias veces
	bool apilo_bien = true;
	bool comprueba_tope = true;
	for(int i=1; i<10000;i++){
		void* puntero= &i + i; //Genero punteros distintos para no apilar siempre el mismo
		apilo_bien &= pila_apilar(pila2,puntero);
		comprueba_tope &= (pila_ver_tope(pila2) == puntero);
	}
	// Verifico que que la prueba se realizo correctamente
	print_test("Se apilaron todos los elementos correctamente ", apilo_bien);
	print_test("El tope de por cada iteracion fue el correcto", comprueba_tope);
	print_test("Comprueba que la pila no esta vacia", !pila_esta_vacia(pila2));

	//Despilo varias veces
	bool desapilo_bien = true;
	while (pila_esta_vacia(pila2) == false){
		//Compruebo tope por cada desapilar
		desapilo_bien &= (pila_ver_tope(pila2)==pila_desapilar(pila2));
	}
	// Verifico que la prueba se realizo correctamente
	print_test("Se desapilaron todos los elementos correctamente", desapilo_bien);
	print_test("Compruebo que no hay tope", pila_ver_tope(pila2)==NULL);
	print_test("La pila esta vacia",pila_esta_vacia(pila2));

	//Destruyo la pila
	pila_destruir(pila2);
}

void prueba_pila_vacia(){
	printf("INICIO DE PRUEBA DE PILA VACIA \n");

	// Creo pila
	pila_t* pila3 = pila_crear();

	//Verifico si la pila fue creada
	print_test("La pila fue creada", pila3 != NULL);

	// Pruebo que al crear una pila esta vacia
	print_test("La pila esta vacia", pila_esta_vacia(pila3));

	//Pruebo que no hay tope en una pila recien creado
	print_test("El tope no existe", pila_ver_tope(pila3)==NULL);

	// Pruebo que no puedo desapilar una pila vacio
	print_test("Desapilar una pila vacía", pila_desapilar(pila3)==NULL);

	//Destruyo la pila
	pila_destruir(pila3);
}

void prueba_apilo_desapilo(){
	printf("INICIO DE PRUEBA DE APILAR Y DESAPILAR \n");

	// Creo pila
	pila_t* pila4 = pila_crear();

	//Verifico si la pila fue creada
	print_test("La pila fue creada", pila4 != NULL);

	// Declaro elementos a apilar
	int v1 = 1;
	int v2 = 50;
	int v3 = 100;

	//Apilo v1 y compruebo que las condiciones de la pila son correctas
	print_test("Apilo un puntero a v1", pila_apilar(pila4,&v1));
	print_test("Observo cual es el tope, debe ser v1", pila_ver_tope(pila4) == &v1);
	print_test("Compruebo que la pila no esta vacia", !pila_esta_vacia(pila4));

	//Apilo v2 y compruebo que las condiciones de la pila son correctas
	print_test("Apilo un puntero a v2 ", pila_apilar(pila4,&v2));
	print_test("Observo cual es el tope, debe ser v2", pila_ver_tope(pila4) == &v2);
	print_test("Compruebo que la pila no esta vacia", !pila_esta_vacia(pila4));

	//Apilo v3 y compruebo que las condiciones de la pila son correctas
	print_test("Apilo un puntero a v3", pila_apilar(pila4,&v3));
	print_test("Observo cual es el tope, debe ser v1", pila_ver_tope(pila4) == &v3);
	print_test("Compruebo que la pila no esta vacia", !pila_esta_vacia(pila4));

	// Comprueba que puedo apilar el NULL
	print_test("Apilo un puntero NULL", pila_apilar(pila4,NULL));

	// Compruebo que la pila no esta vacia
	print_test("La pila no esta vacia", !pila_esta_vacia(pila4));

	//Compruebo que el tope es NULL
	print_test("Observo cual es el tope, debe ser el NULL", pila_ver_tope(pila4) == NULL);

	//Desapilo y compruebo que se mantenga el invariante de pila
	print_test("Desapilo el ultimo, en este debe ser el puntero NULL", pila_desapilar(pila4) == NULL);
	print_test("Observo cual es el tope, debe ser el puntero a v3", pila_ver_tope(pila4) == &v3);
	print_test("Compruebo que la pila no esta vacia", !pila_esta_vacia(pila4));

	print_test("Desapilo el ultimo, en este debe ser el puntero a v3", pila_desapilar(pila4) == &v3);
	print_test("Observo cual es el tope, debe ser el puntero a v2", pila_ver_tope(pila4) == &v2);
	print_test("Compruebo que la pila no esta vacia", !pila_esta_vacia(pila4));

	print_test("Desapilo el ultimo, en este debe ser el puntero a v2", pila_desapilar(pila4) == &v2);
	print_test("Observo cual es el tope, debe ser el puntero a v1", pila_ver_tope(pila4) == &v1);
	print_test("Compruebo que la pila no esta vacia", !pila_esta_vacia(pila4));

	print_test("Desapilo el ultimo, en este debe ser el puntero a v1", pila_desapilar(pila4) == &v1);

	//Compruebo que la pila esta vacia
	print_test("Compruebo que la pila esta vacia", pila_esta_vacia(pila4));

	//Compruebo que no hay tope en pila desapilada hasta vaciarla
	print_test("Observo que ya no hay tope", pila_ver_tope(pila4) == NULL);

	//Compruebo que no puedo seguir desapilando
	print_test("No puedo desapilar una pila vacia", pila_desapilar(pila4) == NULL);

	//Destruyo la pila
	pila_destruir(pila4);
}


void pruebas_pila_alumno() {
	prueba_pila_vacia();
	prueba_apilo_desapilo();
	prueba_volumen();
	prueba_generica();
}
