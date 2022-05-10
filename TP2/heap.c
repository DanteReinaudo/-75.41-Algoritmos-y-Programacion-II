#define _POSIX_C_SOURCE 200809L
#include "heap.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define CAP 16
#define COEF_REDIM 2



//Estructura del Heap
struct heap{
	void** datos;
	size_t cap;
	size_t cant;
	cmp_func_t cmp;
};

/* ******************************************************************
 *                       FUNCIONES AUXILIARES
 * *****************************************************************/

// Intercambia dos valores en el arreglo
void swap (void** arreglo,size_t padre, size_t hijo) {
	void* aux = arreglo[padre];
	arreglo[padre] = arreglo[hijo];
	arreglo[hijo]=aux;
}

// Redimension
bool heap_redimensionar(heap_t* heap, size_t nueva_capacidad) {
	void* nuevos_datos = realloc(heap->datos, nueva_capacidad*sizeof(void*));
	if (nuevos_datos == NULL) return false;
	heap->datos = nuevos_datos;
	heap->cap = nueva_capacidad;
	return true;
}

// Calcula la posicion del padre
size_t calcular_pos_padre(size_t pos){
	return (pos -1) / 2;
}

// Calcula el maximo entre el padre o sus hijos, y devuelve la posicion de este
// En caso de no tener hijos devuelve la posicion del padre
size_t calcular_maximo(void** arreglo,cmp_func_t cmp, size_t padre, size_t izq, size_t der, size_t tam){
	if (der < tam){
		if(cmp(arreglo[padre], arreglo[izq]) > 0 && cmp(arreglo[padre], arreglo[der]) > 0){
			return padre;
		}
		return cmp(arreglo[izq], arreglo[der]) > 0 ? izq : der;
	}
	if (izq >= tam) return padre;
	return cmp(arreglo[padre], arreglo[izq]) > 0 ? padre : izq;
}


//DownHeap
void downheap(void** arreglo, size_t tam, size_t padre, cmp_func_t cmp){
	if (padre >= tam) return;
	size_t izq = 2 * padre + 1;
	size_t der = 2 * padre + 2;

	size_t max = calcular_maximo(arreglo, cmp, padre, izq, der, tam);

	if(max != padre){
		swap(arreglo, max, padre);
		downheap(arreglo, tam, max,cmp);
	}
}

//UpHeap
void upheap(void** arreglo, size_t hijo, cmp_func_t cmp){
	if(hijo == 0) return;
	size_t padre = calcular_pos_padre(hijo);
	if(cmp(arreglo[padre], arreglo[hijo]) < 0 ){
		swap(arreglo, padre,hijo);
		upheap(arreglo, padre,cmp);
	}
}

//Heapify
void heapify(void* datos[],size_t n,cmp_func_t cmp){
	for (int i = 0 ; i < n ; i++){
		downheap(datos,n,n-1-i,cmp);
	}
}


/* ******************************************************************
 *                       PRIMITIVAS DEl ABB
 * *****************************************************************/

heap_t *heap_crear(cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	if (heap == NULL) return NULL;
	heap->datos = malloc(CAP*sizeof(void*));
	if (heap->datos == NULL){
		free(heap);
		return NULL;
	}
	heap->cmp = cmp;
	heap->cap = CAP;
	heap->cant = 0;
	return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	if (heap == NULL) return NULL;
	void** datos = malloc(n  * sizeof(void*));
	if (datos == NULL){
		free(heap);
		return NULL;
	}
	heap->cant = n;
	heap->cap = n;
	heap->cmp = cmp;
	memcpy(datos,arreglo,n*sizeof(void*));
	heapify(datos,n,cmp);
	heap->datos = datos;
	return heap;
}

void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)){
	if (destruir_elemento != NULL){
		for (int i = 0 ; i < heap->cant ; i++) destruir_elemento(heap->datos[i]);
	}
	free(heap->datos);
	free(heap);
}

size_t heap_cantidad(const heap_t *heap){
	return heap->cant;
}

bool heap_esta_vacio(const heap_t *heap){
	return heap->cant == 0;
}


bool heap_encolar(heap_t *heap, void *elem){
	//Si esta lleno hay que redimensionar
	if (heap->cant == heap->cap){
		bool redimension = heap_redimensionar(heap,COEF_REDIM * heap->cap);
		if (redimension == false) return false;
	}
	heap->datos[heap->cant] = elem;
	upheap(heap->datos,heap->cant,heap->cmp);
	heap->cant++;
	return true;
}


void *heap_ver_max(const heap_t *heap){
	if (heap_esta_vacio(heap)) return NULL;
	return heap->datos[0];
}

void *heap_desencolar(heap_t *heap){
	if (heap_esta_vacio(heap)) return NULL;
	if  (heap->cant * (2*COEF_REDIM) <= heap->cap && heap->cap > CAP){
		heap_redimensionar(heap,heap->cap / COEF_REDIM);
	}
	void* elem = heap->datos[0];
	heap->cant--;
	if(!heap_esta_vacio(heap)){
		swap(heap->datos, 0, heap->cant);
		downheap(heap->datos, heap->cant, 0, heap->cmp);
	}
	return elem;
}


void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
	heapify(elementos,cant,cmp);
	for (int i = 0 ; i < cant ; i ++){
		swap(elementos,0,cant-1-i);
		downheap(elementos,cant-1-i,0,cmp);
	}
}
