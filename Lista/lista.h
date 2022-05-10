#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>
#include <stdbool.h>


/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

// Estructura de la lista
typedef struct lista lista_t;

// Estructura del iterador interno
typedef struct lista_iter lista_iter_t;

/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una Lista.
// Post: devuelve una nueva lista vacía o NULL si no se pudo crear.
lista_t *lista_crear(void);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

// Devuelve verdadero si la lista no tiene elementos insertados, false en caso contrario.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento a la lista en la primer posicion. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, dato se encuentra al principio
// de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento a la lista en la ultima posicion. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, dato se encuentra al final
// de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t *lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t* lista);

// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_borrar_primero(lista_t *lista);

// Devuelve el largo de la lista
// Pre: la lista fue creada
// Post: se devolvio el largo de la lista, 0 si esta vacia.
size_t lista_largo(const lista_t *lista);


/* ******************************************************************
 *                  PRIMITIVAS DE LOS ITERADORES
 * *****************************************************************/

//Primitiva del iterador interno

// Itera la lista recibida por parametro.
// La funcion visitar es definida por el usuario y establece la condicon de corte,
// cuando devuelve false no se debe seguir iterando.
// Recibe un puntero extra utilizado para mantener una memoria entre las sucesivas llamadas,
// o recibe NULL en caso de que no se lo utilice.
// Pre: la lista fue creada
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

//Primitivas del iterador externo

// Crea el iterador externo para la lista pasado por parametro
// Post: devuelve un iterado externo o NULL si no se pudo crear.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza al siguiente elemento de la lista, devuelve false cuando no puede seguir avanzando
// Pre: la lista y el iterador fueron creados
bool lista_iter_avanzar(lista_iter_t *iter);

// Devuelve el dato que esta en la posicion actual del iterador.
// Pre: la lista y el iterador fueron creados
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Devuelve true si el iterador se encuentra al final, una vez que ya salio de la lista
// Pre: la lista y el iterador fueron creados
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador externo
// Pre: la lista y el iterador fueron creados
void lista_iter_destruir(lista_iter_t *iter);

// Inserta el dato entre el anterior y el actual,
// devuelvue un bool para saber si se pudo insertar correctamente
// Pre: la lista y el iterador fueron creados
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Elimina el nodo apuntado por el actual y devuelve el dato alli almacenado
// Pre: la lista y el iterador fueron creados
void *lista_iter_borrar(lista_iter_t *iter);


/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación del alumno.

void pruebas_lista_alumno(void);

#endif // LISTA_H
