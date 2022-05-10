#include <stdbool.h>
#include <stddef.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

//Estructura del abb
typedef struct abb abb_t;

//Estructura del iterador del abb
typedef struct abb_iter abb_iter_t;

// Tipo de funcion para comparar clave
typedef int (*abb_comparar_clave_t) (const char *, const char *);

// Tipo de funcion para destruir dato
typedef void (*abb_destruir_dato_t) (void *);

/* ******************************************************************
 *                       PRIMITIVAS DEl ABB
 * *****************************************************************/

/* Crea el abb */
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

/* Guarda un elemento en el abb. De no poder guardarlo devuelve false.
 * Pre: La estructura abb fue inicializada
 * Post: Se almacenó el par (clave, dato)
 */
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

/* Borra un elemento del abb y devuelve el dato asociado.  Devuelve
 * NULL si el dato no estaba.
 * Pre: La estructura abb fue inicializada
 * Post: El elemento fue borrado de la estructura, se lo devolvió,
 * en el caso de que estuviera guardado y se reorganizo la estructura
 * para que siga cumplieando las condiciones de abb.
 */
void *abb_borrar(abb_t *arbol, const char *clave);

/* Obtiene el valor de un elemento del abb, si la clave no se encuentra
 * devuelve NULL.
 * Pre: La estructura abb fue inicializada
 */
void *abb_obtener(const abb_t *arbol, const char *clave);

/* Determina si clave pertenece o no al abb.
 * Pre: La estructura hash fue inicializada
 */
bool abb_pertenece(const abb_t *arbol, const char *clave);

/* Devuelve la cantidad de elementos del abb.
 * Pre: La estructura hash fue inicializada
 */
size_t abb_cantidad(abb_t *arbol);

/* Destruye la estructura liberando la memoria pedida y llamando a la función
 * destruir para cada par (clave, dato).
 * Pre: La estructura abb fue inicializada
 * Post: La estructura abb fue destruida
 */
void abb_destruir(abb_t *arbol);


/* ******************************************************************
 *                     PRIMITIVAS DEL ITERADOR
 * *****************************************************************/

/* Un iterador interno, que funciona usando la función de callback “visitar” que
 * recibe la clave, el valor y un puntero extra, y devuelve true si se debe seguir
 * iterando, false en caso contrario:
 */
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

void abb_in_order_por_rangos(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra, void* minimo, void* maximo);

// Crea iterador externo
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

// Avanza iterador externo
bool abb_iter_in_avanzar(abb_iter_t *iter);

// Devuelve clave actual, esa clave no se puede modificar ni liberar.
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

// Comprueba si terminó la iteración
bool abb_iter_in_al_final(const abb_iter_t *iter);

// Destruye iterador
void abb_iter_in_destruir(abb_iter_t* iter);
