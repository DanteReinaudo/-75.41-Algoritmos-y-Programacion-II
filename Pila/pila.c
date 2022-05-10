#include "pila.h"
#include <stdlib.h>
#include <stdio.h>
#define CAP 10
#define COEF_REDIM 2


/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};


/* Funciones Auxiliares: Redimensionar */

bool pila_redimensionar(pila_t* pila, size_t nueva_capacidad) {
	void* nuevos_datos = realloc(pila->datos, nueva_capacidad*sizeof(void*));
	if (nuevos_datos == NULL) return false;
	pila->datos = nuevos_datos;
	pila->capacidad = nueva_capacidad;
	return true;
}


/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/


pila_t* pila_crear(void){
	pila_t* pila = malloc(sizeof(pila_t));
	if (pila == NULL) return NULL;
	pila->datos=malloc(CAP*sizeof(void*));
	if (pila->datos==NULL){
		free(pila);
		return NULL;
	}
	pila->capacidad=CAP;
	pila->cantidad=0;
	return pila;
}

void pila_destruir(pila_t *pila){
	free(pila->datos);
	free(pila);
}


bool pila_esta_vacia(const pila_t *pila){
	return (pila->cantidad == 0)? true : false;
}


bool pila_apilar(pila_t *pila, void* valor){
	//Si esta lleno hay que redimensionar
	if (pila->cantidad == pila->capacidad){
		size_t nueva_capacidad = COEF_REDIM * pila->capacidad;
		bool redimension = pila_redimensionar(pila,nueva_capacidad);
		if (redimension == false) return false;
	}
	pila->datos[pila->cantidad]=valor;
	pila->cantidad += 1;
	return true;
}

void* pila_ver_tope(const pila_t *pila){
	if (pila->cantidad == 0) return NULL;
	return pila->datos[pila->cantidad-1];
}

void* pila_desapilar(pila_t *pila){
	if (pila->cantidad == 0) return NULL;
	if  (pila->cantidad * (2*COEF_REDIM) <= pila->capacidad && pila->capacidad > CAP){
		size_t nueva_capacidad = pila->capacidad / COEF_REDIM;
		bool redimension = pila_redimensionar(pila,nueva_capacidad);
		if (redimension == false) return NULL;
	}
	void* tope = pila_ver_tope(pila);
	pila->cantidad -= 1;
	return tope;
}
