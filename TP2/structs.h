#ifndef STRUCTS_H
#define STRUCTS_H

#include <stddef.h>
#include <string.h>
#include "abb.h"
#include "hash.h"
#include "heap.h"
#include "cola.h"


/* ******************************************************************
 *                      ESTRUCTURAS PRINCIPALES
 * *****************************************************************/

struct doctor;
struct paciente;
struct especialidad;

typedef struct doctor doctor_t;
typedef struct paciente paciente_t;
typedef struct especialidad especialidad_t;

/* ******************************************************************
 *                       FUNCIONES DE CREACION
 * *****************************************************************/


// Crea un Doctor recibiendo el nombre y su especialidad.
// Post: devuelve un doctor o NULL si no se pudo crear.
doctor_t *crear_doctor(char* nombre, char* especialidad);

// Crea un Paciente recibiendo el nombre y su año de ingreso a la clinica.
// Post: devuelve un paciente o NULL si no se pudo crear.
paciente_t* crear_paciente(char* nombre,int anio);

// Crea una Especialidad recibiendo su nombre .
// Post: devuelve una especialidad o NULL si no se pudo crear.
especialidad_t* crear_especialidad(char* nombre);

/* ******************************************************************
 *                      FUNCIONES DE DESTRUCCIÒN
 * *****************************************************************/

// Destruye al doctor.
// Pre: el doctor fue creado.
// Post: se eliminaron todos los elementos del doctor y se libero la memoria.
void destruir_doctor(doctor_t* doctor);

// Destruye al paciente.
// Pre: el paciente fue creado.
// Post: se eliminaron todos los elementos del paciente y se libero la memoria.
void destruir_paciente(paciente_t* paciente);

// Destruye la especialidad.
// Pre: la especialidad fue creada.
// Post: se eliminaron todos los elementos de la especialidad y se libero la memoria.
void destruir_especialidad(especialidad_t* especialidad);

// Wrappers de destrucción.
void w_destruir_doctor(void* doctor);

void w_destruir_paciente(void* paciente);

void w_destruir_especialidad(void* especialidad);

/* ******************************************************************
 *                      CAMBALACHE DE FUNCIONES
 * *****************************************************************/

// Añade al doctor a la especialidad pasada por parametro.
void encolar_doctor_en_especialidad(especialidad_t* especialidad, doctor_t* doctor);

// Añade un paciente a la cola de urgenicas.
void encolar_paciente_urgencias(especialidad_t* especialidad, char* nombre);

// Añade un paciente a la lista de espera regular.
bool encolar_paciente_regulares(especialidad_t* especialidad, char* nombre,int* anio);

// Devuelve la cantidad de pacientes en lista de epsera para la especialidad.
long cantidad_pacientes_especialidad(especialidad_t* especialidad);

// Devuelve la especialidad del doctor pasado por parametro.
char* conseguir_especialidad_doctor(doctor_t* doctor);

// Devuelve true si hay pacientes urgentes en lista de espera para la especialidad.
bool hay_pacientes_urgentes(especialidad_t* especialidad);

// Atiende al paciente de urgencias que sigue en la lista de espera.
char* desencolar_urgente(especialidad_t* especialidad);

// Atiende al paciente regular con mayor antiguedad en la clinica.
paciente_t* desencolar_regular(especialidad_t* especialidad);

// Devuelvue el nombre de la especialidad
char* nombre_especialidad(especialidad_t* especialidad);

// Devuelve true si hay pacientes regulares en lista de espera para la especialidad.
bool hay_pacientes_regulares(especialidad_t* especialidad);

// Devuelve el nombre del paciente.
char* nombre_paciente(paciente_t* paciente);

// Devuelve el nombre del doctor.
char* nombre_doctor(doctor_t* doctor);

// Añade una unidad a la cantidad de pacientes atendidos por el doctor.
void atiende_doctor(doctor_t* doctor);
// Devuelve la cantidad de pacientes del doctr
size_t pacientes_doctor(doctor_t* doctor);



#endif
