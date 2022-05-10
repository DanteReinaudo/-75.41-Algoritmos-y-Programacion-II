#ifndef CLINICA_H
#define CLINICA_H
#define _POSIX_C_SOURCE 200809L
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "structs.h"
#include "csv.h"
#include "lista.h"
#include "mensajes.h"


/* ******************************************************************
 *                   ESTRUCTURA DE LA CLINICA
 * *****************************************************************/

struct especialidad;
typedef struct clinica clinica_t;

/* ******************************************************************
 *                    PRIMITIVAS DE LA CLINICA
 * *****************************************************************/

// Crea la clinica, recibe por parametro un arreglo de strings
// con los nombres de los archivos csv de doctores y pacientes.
// Post: devuelve una nueva clinica con la informacion de los doctores y pacientes
// o NULL si hubo alguna falla en la creación.
clinica_t* crear_clinica(char** argv);

// Destruye la clinica.
// Pre: la clinica fue creada.
// Post: se eliminaron todos los elementos de la clinica y se libero la memoria.
void destruir_clinica(clinica_t* clinica);

// Recibe por parametro el nombre del paciente, la especialidad y la urgencia.
// Añade al paciente a la cola de espera de dicha especialidad, basandose en la urgencia.
// Muestra por pantalla si se pudo asignar un turno al paciente, o error en caso de que
// los parametros recibidos no sean correctos.
void pedir_turno_paciente(clinica_t* clinica, char* nombre, char* nombre_especialidad , char* prioridad);

// Recibe por parametro el nombre de un doctor, si hay pacientes en lista de espera
// de la especialidad del doctor, se atiende al paciente de urgencia que llego primero
// o el paciente regular con mas antiguedad en caso de no haber urgentes.
// Imprime por pantalla si pudo realizar la operacion, o error en caso de que
// los parametros recibidos no sean correctos.
void atender_siguiente_paciente(clinica_t* clinica, char* nombre_doc);


// Realiza un informe en orden alfabetico de todos los doctores comprendidos
// entre los doctores pasados por parametros.
// Pre: El nombre del doctor "inicio" anteceda alfabeticamente al nombre del doctor "fin"
void informe_doctores(clinica_t* clinica, char* inicio,char* fin);

#endif
