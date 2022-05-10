// Dante Reinaudo padrón: 102848
// Primer Parcial Algoritmos y Programación II 06/07/2020
// Ejercicios: 1 - 3A (Post Order) - 4 Hash Abierto

#include "lista.h"
#include "hash.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Ejercicio 1

/* A) Esta afirmacion es verdadera. Se puede implementar que permita cambiar
 * la funcion de prioridad de un Heap en 0(n), esto es posible utilizando
 * Heapify. Esta funcion recibe un arreglo de n elementos y crea un heap con
 * dichos elementos. Si yo tomo el heap que quiero modificar como un arreglo, se lo
 * paso a heapify y crea un nuevo heap con la nueva prioridad deseada.
 * Si bien cuando desencolamos downheap es de orden 0(logn),
 * y como se lo aplicamos a los n elementos, esto nos daria que el orden total
 * de 0(n.logn), pero dada esta aplicacion no todos los downheaps tardan el mismo tiempo
 * (no todos son O(logn)) por lo que podemos decir que heapify es 0(n).
 *

 *B) Falso, el procedimiento para desencolar en un heap es quitar el de maxima prioridad
 * (el primero del arreglo, el maximo numero en este caso), luego colocar el elemento
 * de la ultima posicion en el primer lugar, la cual fue desocupada por el desencolado.
 * Luego se aplica downheap con el nuevo "primero". No se a que se refiere con estado
 * resultante pero el arreglo que se muestra no cumple con la condicion de heap,
 * ya que el 6 es mayor a su padre el 5 .

 *C) Verdadero, el Heap es una muy buena forma de implementar una cola de prioridad,
 * ya que obtener el maximo es 0(1) y el resto de las operaciones basicas es 0(logn),
 * esto es mucho mejor que implementarlo sobre un abb o un avl, cuya estructura es
 * mas compleja y mas dificil de mantener. Pero si considero tanto a la pila o la cola
 * como unas colas de prioridad, en donde la maxima prioridad es del ultimo insertado para la pila
 * o el primer insertado para la cola, entonces bajo estas condiciones es mas optimo implementar
 * una pila o una cola, segun sea el caso , que implementar un heap ya que el costo de operaciones
 * del heap es mayor (excepto en encolar para la cola donde ambos tda tiene orden 0(1)).

 */


// Ejercicio 3A Post Order
//Implementar una primitiva lista_t* ab_debajo_de(ab_t* ab, const char* clave) que reciba una clave y devuelva
//todos los elementos debajo del nodo cuya clave es la indicada, en el orden que te corresponda según enunciado. Indicar y
//justificar la complejidad del algoritmo implementado.

typedef struct ab {
	struct ab* izq;
	struct ab* der;
	char* clave;
}ab_t;

//La idea de esta funcion es que busque la clave que se le pasa y devuelve un puntero a dicho ab
// o null en caso de no encontrarlo. Vendria a ser como un ab_obtener.
//No me convence mucho como esta escrita, sobre todo el doble return del final, dudo que ande correctamente.

ab_t* buscar_clave(ab_t* ab, const char* clave){
	if (!ab) return NULL;
	// Si las claves son iguales devuelve el puntero al arbol
	if(strcmp(ab->clave, clave) == 0) return ab;
	return buscar_clave(ab->izq,clave);
	return buscar_clave(ab->der,clave);
}

void ab_obtener_reclutados(ab_t* actual,lista_t* lista){
	if (actual == NULL) return;
	ab_obtener_reclutados(actual->izq,lista);
	ab_obtener_reclutados(actual->der,lista);
	lista_insertar_ultimo(lista,actual->clave);
}

// Si no ecuentra la clave devuelve NULL
// Como no implemente un TDA AB no conozco bien sus primitivas, pero en caso de que
// buscar_clave este mal  asumo que existe una funcion ab_obtener que me devuelve un puntero
// al ab con dicha clave o null si no lo encuentra
lista_t* ab_debajo_de(ab_t* ab, const char* clave){
	if (!ab) return NULL;
	lista_t* lista = lista_crear();
	if (lista == NULL) return NULL;
	// Obtengo el arbol con la clave buscada
	ab_t* raiz_recluta = buscar_clave(ab,clave);
	if (raiz_recluta == NULL){
		lista_destruir(lista,NULL);
		return NULL;
	}
	ab_obtener_reclutados(raiz_recluta,lista);
	return lista;
}

/* La complejidad de este algoritmo es la siguiente:
 * Siendo n la cantidad de elementos del arbol, para obtener el "reclutante" debo recorrer
 * el arbol, como no es un abb no puedo ir descartando hijos, puede estar en cualquier parte,
 * en el peor de los casos sera 0(n) dado que busque por todo el arbol y lo encontre en la
 * ultima posicion o no se encontraba en ele arbol.
 * Una vez encontrado el "reclutante", itero los subarboles hijos, suponiendo que k es la cantidad
 * de personas que llegaron a la red debido a el, este recorrido tardara  0(K)
 * Como N es mayor o igual que K, podemos decir que este algoritmo es 0(n), distinto seria el caso
 * si se tratase de un abb.
 */

// Ejercicio 4
/* Implementar una primitiva del Hash Abierto que permita obtener una lista con las claves y
 * valores existentes dentro del Hash. A fines del ejercicio, pueden suponer que en hash.h ya se
 * encuentra definida una estructura typedef struct {const char* clave; void* dato; }
 * hash_par_t;, y la lista debe ser de punteros a dicha estructura.
 * Indicar y justificar la complejidad del algoritmo implementado.
*/

typedef struct {const char* clave; void* dato; } hash_par_t;

typedef struct hash{
	lista_t** tabla;
	size_t cant;
	size_t tam;
	hash_destruir_dato_t* destruir;
}hash_t;

// Asumo que en el campo hash se almacena el struct par
typedef struct campo_hash{
	char* clave;
	void* valor;
	hash_par_t* par;
}campo_hash_t;

lista_t* hash_claves(const hash_t* hash){
	lista_t* claves = lista_crear();
	if (!claves) return NULL;
	for(size_t i = 0 ; i< hash->tam ; i++){
		lista_iter_t* iter = lista_iter_crear(hash->tabla[i]);
		while(!lista_iter_al_final(iter)){
			campo_hash_t* campo = lista_iter_ver_actual(iter);
			lista_insertar_ultimo(claves,campo->par);
			lista_iter_avanzar(iter);
		}
		lista_iter_destruir(iter);
	}
	return claves;
}

/* La complejidad de este algoritmo es la siguiente:
 * Sea n la la cantidad de elementos almacenados en el hash puedo decir que el orden
 * del algoritmo es 0(n) dado que recorro todos los elementos del hash para buscar el par
 * clave-dato
 */
