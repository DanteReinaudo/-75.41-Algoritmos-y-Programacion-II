#define _POSIX_C_SOURCE 200809L
#include "abb.h"
#include "pila.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Estructura auxiliar: Nodo ABB

typedef struct nodo_abb{
	struct nodo_abb* izq;
	struct nodo_abb* der;
	char* clave;
	void* dato;
}nodo_abb_t;

//Estructura del abb

struct abb{
	nodo_abb_t* raiz;
	size_t cant;
	abb_comparar_clave_t cmp;
	abb_destruir_dato_t destruir;
};

//Estructura del iterador del abb
struct abb_iter{
	pila_t* pila;
};

/* ******************************************************************
 *                       FUNCIONES AUXILIARES
 * *****************************************************************/

//Crear Nodo abb
nodo_abb_t* crear_nodo_abb(char* clave,void* dato){
	nodo_abb_t* nodo_abb = malloc(sizeof(nodo_abb_t));
	if (nodo_abb == NULL) return NULL;
	nodo_abb->clave = clave;
	nodo_abb->dato = dato;
	nodo_abb->izq = NULL;
	nodo_abb->der = NULL;
	return nodo_abb;
}
// Buscar Nodo abb
nodo_abb_t* buscar_nodo_abb(nodo_abb_t* nodo, abb_comparar_clave_t cmp, const char* clave){
	// Si el nodo es NULL no encontro la clave
	if (!nodo) return NULL;
	// Si las claves son iguales devuelve true
	if(cmp(nodo->clave, clave) == 0) return nodo;
	// Si la clave del nodo es mayor a la clave busco por la izq
	if(cmp(nodo->clave, clave) > 0){
		return buscar_nodo_abb(nodo->izq,cmp,clave);
	} else {
		return buscar_nodo_abb(nodo->der,cmp,clave);
	}
}
//busca el padre para insertar
nodo_abb_t* buscar_padre(nodo_abb_t* nodo, abb_comparar_clave_t cmp, const char* clave,bool borrar){
	if(!nodo) return NULL;
	//Comparo
	if(cmp(nodo->clave, clave) == 0) return nodo;
	if(cmp(nodo->clave, clave) > 0){
		if(borrar == true){ //CORRECCIÓN: Este bloque es casi idéntico al de abajo, cómo podrían hacer para reutilizar?
			if(!nodo->izq) return NULL;
			if(cmp(nodo->izq->clave, clave) == 0)	return nodo;
		} else {
			if(!nodo->izq)	return nodo;
		}
		return buscar_padre(nodo->izq, cmp, clave, borrar);
	} else {
		if(borrar == true){
			if(!nodo->der)	return NULL;
			if(cmp(nodo->der->clave, clave) == 0)	return nodo;
		} else {
			if(!nodo->der)	return nodo;
		}
		return buscar_padre(nodo->der, cmp, clave, borrar);
	}
	return NULL;
}

void* borrar_nodo(nodo_abb_t* nodo, abb_destruir_dato_t destruir){
	free(nodo->clave);
	void* dato = nodo->dato;
	free(nodo);
	return dato;
}

//Destruye el arbol recursivamente
void destruir_arbol(nodo_abb_t* nodo, abb_destruir_dato_t destruir){
	if(!nodo) return;
	destruir_arbol(nodo->izq, destruir);
	destruir_arbol(nodo->der, destruir);
	if(destruir != NULL){
		destruir(nodo->dato);
	}
	borrar_nodo(nodo,destruir);
}

//Devuelve la cantidad de hijos del nodo
size_t cant_hijos(nodo_abb_t* nodo){
	if(!nodo->izq && !nodo->der){
		return 0;
	} else {
		if(nodo->izq != NULL && nodo->der != NULL)	return 2;
	}
	return 1;
}


//Busca un reemplazante en el caso de que haay que borrar nodo con 2 hijos
nodo_abb_t* buscar_reemplazante(nodo_abb_t* nodo){
	nodo_abb_t* nodo_temp = nodo->der;
	while(nodo_temp->izq != NULL){
		nodo_temp = nodo_temp->izq;
	}
	return nodo_temp;
}

//Reemplaza el nodo a borrar en caso que tenga 2 hijos
void* reemplazar_nodo(abb_t* arbol,nodo_abb_t* nodo){
	//Busco reemplazante
	nodo_abb_t* reemplazante = buscar_reemplazante(nodo);
	//Me guardo el dato a devolver
	void* dato = nodo->dato;
	//Me guardo la clave del reemplazante
	char* clave_reemplazante = strdup(reemplazante->clave);
	//Borro el reemplazante y me guardo su dato
	void* dato_reemplazante = abb_borrar(arbol, reemplazante->clave);
	//Se lo asigno al nodo que voy a "borrar"
	nodo->dato = dato_reemplazante;
	//Libero la clave del que voy a borrar
	free(nodo->clave);
	//Asigno la nueva clave al nodo
	nodo->clave = clave_reemplazante;
	return dato;
}


void* borrar_nodo_con_1_hijo(nodo_abb_t* nodo, abb_destruir_dato_t destruir){
	nodo_abb_t* nodo_a_borrar = nodo;
	if(!nodo_a_borrar->izq){
		nodo = nodo_a_borrar->der;
	} else {
		nodo = nodo_a_borrar->izq;
	}
	return borrar_nodo(nodo_a_borrar, destruir);
}

/* ******************************************************************
 *                       PRIMITIVAS DEl ABB
 * *****************************************************************/

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	abb_t* abb = malloc(sizeof(abb_t));
	if (abb == NULL) return NULL;
	abb->cant = 0;
	abb->destruir = destruir_dato;
	abb->cmp = cmp;
	abb->raiz = NULL;
	return abb;
}



bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	//creo el nodo
	char* copia_clave = strdup(clave);
	nodo_abb_t* nodo = crear_nodo_abb(copia_clave, dato);
	if(!nodo)	return false;
	//si no hay raiz, lo inserto como raiz
	if(!arbol->raiz){
		arbol->raiz = nodo;
		arbol->cant++;
		return true;
	}
	//Buscamos el padre de donde insertariamos
	nodo_abb_t* padre = buscar_padre(arbol->raiz, arbol->cmp, clave, false);
	//Si es igual la clave reemplazamos el dato
	if(arbol->cmp(padre->clave, clave) == 0) {
		if(arbol->destruir != NULL)	arbol->destruir(padre->dato);
		padre->dato = dato;
		free(copia_clave);
		free(nodo);
		return true;
	}
	arbol->cant++;
	if(arbol->cmp(padre->clave, clave) > 0){
		//Aca inserto hijo izquierdo de padre
		padre->izq = nodo;
	} else {
		padre->der = nodo;
	}
	return true;
}


void *abb_borrar(abb_t *arbol, const char *clave){ //CORRECCIÓN: Hay mucha repetición de código
	if(!arbol->raiz){
		return NULL;
	}
	void* dato;
	nodo_abb_t* nodo = buscar_nodo_abb(arbol->raiz, arbol->cmp, clave);
	if(!nodo) return NULL;
	//Prefiero buscar el padre de la raiz y que sea el mismo a que llamar a buscar padre segun cada caso.
	nodo_abb_t* padre_nodo_a_borrar = buscar_padre(arbol->raiz, arbol->cmp, clave, true);
	if(!padre_nodo_a_borrar) return NULL;

	if(cant_hijos(nodo) == 0){
		arbol->cant--;
		//Caso si es raiz
		if(arbol->cmp(arbol->raiz->clave,clave) == 0){
			dato = borrar_nodo(arbol->raiz, arbol->destruir);
			arbol->raiz = NULL;
			return dato;
		}
		
		if(arbol->cmp(padre_nodo_a_borrar->clave, clave) > 0){
			dato = borrar_nodo(padre_nodo_a_borrar->izq, arbol->destruir);
			padre_nodo_a_borrar->izq = NULL;
		} else {
			dato = borrar_nodo(padre_nodo_a_borrar->der, arbol->destruir);
			padre_nodo_a_borrar->der = NULL;
		}
		return dato;
	}

	if(cant_hijos(nodo) == 1){
		arbol->cant--;
		if(arbol->cmp(arbol->raiz->clave,clave) == 0){
			nodo_abb_t* nodo_temp = (!arbol->raiz->izq) ? arbol->raiz->der : arbol->raiz->izq;
			dato = borrar_nodo(arbol->raiz, arbol->destruir);
			arbol->raiz = nodo_temp;
			return dato;
		}
		//Intento reutilizar este codigo pero se me rompe por completo todo. No termino de entender por que sucede esto.
		if(arbol->cmp(padre_nodo_a_borrar->clave, clave) > 0){
			//return borrar_nodo_con_1_hijo(padre_nodo_a_borrar->izq, arbol->destruir);
			nodo_abb_t* nodo_a_borrar = padre_nodo_a_borrar->izq;
			if(!nodo_a_borrar->izq){
				padre_nodo_a_borrar->izq = nodo_a_borrar->der;
			} else {
				padre_nodo_a_borrar->izq = nodo_a_borrar->izq;
			}
			dato = borrar_nodo(nodo_a_borrar, arbol->destruir);
		} else {
			//return borrar_nodo_con_1_hijo(padre_nodo_a_borrar->der, arbol->destruir);
			nodo_abb_t* nodo_a_borrar = padre_nodo_a_borrar->der;
			if(!nodo_a_borrar->izq){
				padre_nodo_a_borrar->der = nodo_a_borrar->der;
			} else {
				padre_nodo_a_borrar->der = nodo_a_borrar->izq;
			}
			dato = borrar_nodo(nodo_a_borrar, arbol->destruir);
		}
		return dato; 
	} else {
		//Tengo 2 hijos
		if(arbol->cmp(arbol->raiz->clave,clave) == 0){
			return reemplazar_nodo(arbol, arbol->raiz);
		}
		if(arbol->cmp(padre_nodo_a_borrar->clave, clave) > 0){
			return reemplazar_nodo(arbol, padre_nodo_a_borrar->izq);
		} else {
			return reemplazar_nodo(arbol, padre_nodo_a_borrar->der);
		}
	}
}

void *abb_obtener(const abb_t *arbol, const char *clave){
	if (!arbol) return NULL;
	if (!arbol->raiz) return NULL;
	//CORRECCIÓN: ¿Es necesario este if si después van a usar buscar_nodo_abb? CORREGIDO
	nodo_abb_t* nodo_abb = buscar_nodo_abb(arbol->raiz,arbol->cmp,clave);
	if (nodo_abb == NULL) return NULL;
	return nodo_abb->dato;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
	if (!arbol) return false;
	if (!arbol->raiz) return false;
	//CORRECCIÓN: ¿Es necesario este if si después van a usar buscar_nodo_abb? CORREGIDO
	nodo_abb_t* nodo = buscar_nodo_abb(arbol->raiz,arbol->cmp,clave);
	return nodo != NULL;
}

size_t abb_cantidad(abb_t *arbol){
	return arbol->cant; //CORRECCIÓN: Los paréntesis si no son necesarios perjudican la legibilidad CORREGIDO
}

void abb_destruir(abb_t *arbol){
	destruir_arbol(arbol->raiz, arbol->destruir);
	free(arbol);
}

char* devolver_minimo_recursivo(nodo_abb_t* nodo){
	if(!nodo) return NULL;
	while(nodo->izq != NULL){
		nodo = nodo->izq;
	}
	return nodo->clave;
}


/* ******************************************************************
 *                     PRIMITIVAS DEL ITERADOR
 * *****************************************************************/

//Funcion Auxiliar: Iterador Iterno

void abb_iterar(nodo_abb_t* nodo_abb
 , bool visitar(const char *, void *, void *), void * extra, bool* iterar){
	if (nodo_abb == NULL) return;
	if(*iterar == false) return;
	abb_iterar(nodo_abb->izq,visitar,extra,iterar);
	if (*iterar) *iterar = visitar(nodo_abb->clave,nodo_abb->dato,extra);
	abb_iterar(nodo_abb->der,visitar,extra,iterar);
}

void abb_iterar_por_rangos(nodo_abb_t* nodo_abb
 , bool visitar(const char *, void *, void *), void * extra
 , void* minimo, void* maximo){
	if (nodo_abb == NULL) return;
	
	if(strcmp(nodo_abb->clave, minimo) > 0){
		abb_iterar_por_rangos(nodo_abb->izq,visitar,extra, minimo, maximo);
	}

	if(strcmp(nodo_abb->clave, minimo) >= 0 && strcmp(nodo_abb->clave, maximo) <= 0){
		visitar(nodo_abb->clave,nodo_abb->dato,extra);
	}

	if(strcmp(nodo_abb->clave, maximo) < 0){
		abb_iterar_por_rangos(nodo_abb->der,visitar,extra, minimo, maximo);
	}
}

/* Iterador Interno */

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
	bool iterar = true;
	abb_iterar(arbol->raiz,visitar,extra, &iterar);
}

void abb_in_order_por_rangos(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra, void* minimo, void* maximo){
	abb_iterar_por_rangos(arbol->raiz,visitar,extra, minimo, maximo);
}


/* Iterador interno */

void apilar_en_iter(nodo_abb_t* nodo, pila_t* pila){
	while(nodo->izq != NULL){
		pila_apilar(pila,nodo->izq);
		nodo = nodo->izq;
	}
}

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
	abb_iter_t* abb_iter = malloc(sizeof(abb_iter_t));
	if (abb_iter == NULL) return NULL;
	pila_t* pila = pila_crear();
	if (pila == NULL){
		free(abb_iter); //CORRECCIÓN: ¿Por qué está dos veces este chequeo? Deberían chequear la pila CORREGIDO
		return NULL;
	}
	abb_iter->pila = pila;
	if (arbol->raiz == NULL) return abb_iter;
	nodo_abb_t* actual = arbol->raiz;
	pila_apilar(abb_iter->pila,arbol->raiz);
	apilar_en_iter(actual, abb_iter->pila);
	return abb_iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter){
	if (abb_iter_in_al_final(iter)) return false; //COMENTARIO: Buenísimo reutilizando
	nodo_abb_t* actual = pila_desapilar(iter->pila);
	if (actual->der == NULL) return true;
	pila_apilar(iter->pila,actual->der);
	actual = actual->der;
	apilar_en_iter(actual, iter->pila);
	return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
	if (abb_iter_in_al_final(iter)) return NULL;
	nodo_abb_t* actual = pila_ver_tope(iter->pila);
	return actual->clave; //CORRECCIÓN: No son necesarios los paréntesis
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
	return pila_esta_vacia(iter->pila); //CORRECCIÓN: No son necesarios los paréntesis
}

void abb_iter_in_destruir(abb_iter_t* iter){
	pila_destruir(iter->pila);
	free(iter);
}