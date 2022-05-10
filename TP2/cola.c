#include "cola.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


/* Definicion de estructura auxiliar: Nodo */

typedef struct nodo{
	void* dato;
	struct nodo* prox;
}nodo_t;


/* Definición del struct Cola. */

struct cola {
	nodo_t* prim;
	nodo_t* ult;
};


/* Funciones Auxiliares: Crear Nodo */

nodo_t* crear_nodo(void* valor){
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if (nodo == NULL) return NULL;
	nodo->dato = valor;
	nodo->prox = NULL;
	return nodo;
	}


/* *****************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/



cola_t* cola_crear(void){
	cola_t* cola = malloc(sizeof(cola_t));
	if (cola == NULL) return NULL;
	cola->prim = NULL;
	cola->ult = NULL;
	return cola;
}


void cola_destruir(cola_t *cola, void (*destruir_dato)(void*)){
	while (cola->prim != NULL){
		void* dato = cola_desencolar(cola);
		if (*destruir_dato != NULL) destruir_dato(dato);
	}
	free(cola);
}


bool cola_esta_vacia(const cola_t *cola){
	return (cola->prim==NULL);
	}


bool cola_encolar(cola_t *cola, void* valor){
	nodo_t* nuevo_nodo = crear_nodo(valor);
	if (nuevo_nodo == NULL) return false;
	if (cola_esta_vacia(cola)) cola->prim = nuevo_nodo;
	else cola->ult->prox  = nuevo_nodo;
	cola->ult = nuevo_nodo;
	return true;
	}


void* cola_ver_primero(const cola_t *cola){
	if (cola_esta_vacia(cola)) return NULL;
	return (cola->prim->dato);
	}


void* cola_desencolar(cola_t *cola){
	if(cola_esta_vacia(cola)) return NULL;
	void* valor = cola->prim->dato;
	nodo_t* nodo_auxiliar = cola->prim->prox;
	free(cola->prim);
	cola->prim = nodo_auxiliar;
	return valor;
	}
