#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/* Definicion de estructura auxiliar: Nodo */

typedef struct nodo{
	void* dato;
	struct nodo* prox;
}nodo_t;


/* Definición de la estructura del Iterador Externo. */

struct lista_iter{
	struct nodo* anterior;
	struct nodo* actual;
	struct lista* lista;
};

/* Definición del struct Lista. */

struct lista {
	nodo_t* prim;
	nodo_t* ult;
	size_t largo;
};


/* Funciones Auxiliares: Crear Nodo */

nodo_t* crear_Nodo(void* valor){
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if (nodo == NULL) return NULL;
	nodo->dato = valor;
	nodo->prox = NULL;
	return nodo;
	}


/* *****************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

lista_t *lista_crear(void){
	lista_t* lista = malloc(sizeof(lista_t));
	if (lista == NULL) return NULL;
	lista->prim = NULL;
	lista->ult = NULL;
	lista->largo = 0;
	return lista;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)){
	while (lista->largo != 0){
		void* dato = lista_borrar_primero(lista);
		if (*destruir_dato != NULL) destruir_dato(dato);
	}
	free(lista);
}

bool lista_esta_vacia(const lista_t *lista){
	return (lista->largo == 0);
}

bool lista_insertar_primero(lista_t *lista, void *dato){
	nodo_t* nuevo_nodo = crear_Nodo(dato);
	if (nuevo_nodo == NULL) return false;
	if (lista_esta_vacia(lista)){
		lista->prim = nuevo_nodo;
		lista->ult = nuevo_nodo;
	}else{
		nuevo_nodo->prox = lista->prim;
		lista->prim = nuevo_nodo;
	}
	lista->largo += 1;
	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
	nodo_t* nuevo_nodo = crear_Nodo(dato);
	if (nuevo_nodo == NULL) return false;
	if (lista_esta_vacia(lista)) lista->prim = nuevo_nodo;
	else lista->ult->prox  = nuevo_nodo;
	lista->ult = nuevo_nodo;
	lista->largo += 1;
	return true;
}

void *lista_ver_primero(const lista_t *lista){
	if (lista_esta_vacia(lista)) return NULL;
	return (lista->prim->dato);
}

void *lista_ver_ultimo(const lista_t* lista){
	if (lista_esta_vacia(lista)) return NULL;
	return (lista->ult->dato);
}

void *lista_borrar_primero(lista_t *lista){
	if(lista_esta_vacia(lista)) return NULL;
	void* valor = lista->prim->dato;
	nodo_t* nodo_auxiliar = lista->prim->prox;
	free(lista->prim);
	lista->prim = nodo_auxiliar;
	lista->largo -= 1;
	return valor;
}

size_t lista_largo(const lista_t *lista){
	return (lista->largo);
}

/* *****************************************************************
 *                 PRIMITIVAS DE LOS ITERADORES
 * *****************************************************************/

//Primitiva del iterador interno

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
	size_t contador = 1;
	nodo_t* nodo_actual = lista->prim;
	bool iterar = true;
	while(iterar == true && contador <= lista->largo){
		void* valor = nodo_actual->dato;
		iterar = visitar(valor,extra);
		nodo_actual = nodo_actual->prox;
		contador++;
	}
}

//Primitivas del iterador externo

lista_iter_t *lista_iter_crear(lista_t *lista){
	lista_iter_t* lista_iter = malloc(sizeof(lista_iter_t));
	if (lista_iter == NULL) return NULL;
	lista_iter->actual = lista->prim;
	lista_iter->anterior = NULL;
	lista_iter->lista = lista;
	return lista_iter;
}

bool lista_iter_avanzar(lista_iter_t *iter){
	if (lista_iter_al_final(iter)) return false;
	nodo_t* auxiliar = iter->actual;
	iter->actual = iter->actual->prox;
	iter->anterior = auxiliar;
	return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
	if (iter->actual == NULL) return NULL;
	return(iter->actual->dato);
}

bool lista_iter_al_final(const lista_iter_t *iter){
	if (iter->actual == NULL && iter->anterior == iter->lista->ult) return true;
	return false;
}

void lista_iter_destruir(lista_iter_t *iter){
	free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
	nodo_t* nuevo_nodo = crear_Nodo(dato);
	if (nuevo_nodo == NULL) return false;
	if (iter->anterior != NULL) iter->anterior->prox = nuevo_nodo;
	nuevo_nodo->prox = iter->actual;
	iter->actual = nuevo_nodo;
	iter->lista->largo++;
	if (iter->lista->largo == 1 && iter->anterior == NULL){
		iter->lista->prim = iter->actual;
		iter->lista->ult = iter->actual;
	}else if (nuevo_nodo->prox == iter->lista->prim && iter->anterior == NULL){
		iter->lista->prim = iter->actual;
	}else if (nuevo_nodo->prox == NULL && iter->anterior == iter->lista->ult){
		iter->lista->ult = iter->actual;
	}
	return true;
}

void *lista_iter_borrar(lista_iter_t *iter){
	if (lista_iter_al_final(iter) || lista_esta_vacia(iter->lista)) return NULL;
	nodo_t* nodo_auxiliar = iter->actual;
	void* dato = lista_iter_ver_actual(iter);
	if (iter->anterior != NULL) iter->anterior->prox = iter->actual->prox;
	iter->actual = nodo_auxiliar->prox;
	iter->lista->largo--;
	if (iter->lista->largo == 0){
		iter->lista->prim = NULL;
		iter->lista->ult = NULL;
	}else if (iter->lista->prim == nodo_auxiliar && iter->anterior == NULL){
		iter->lista->prim = iter->actual;
	}else if (nodo_auxiliar->prox == NULL && iter->lista->ult == nodo_auxiliar){
		iter->lista->ult = iter->anterior;
	}
	free(nodo_auxiliar);
	return dato;
}
