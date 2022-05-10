#ifndef __CSV__H_
#define __CSV__H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "structs.h"
#include "mensajes.h"
#include "strutil.h"

// Importante: Esto no es un TDA, son funciones auxiliares utilizadas en el TDA clinica,
// puestas en un archivo aparte para modularizar y poder debuguear mas comodamente.

// Recibe el nombre de un archivo csv con la informacion sobre los doctores de una
// clinica. Crea un abb con la informacion alli encontrada, siendo la clave el nombre
// del doctor y el dato un puntero a un struct doctor.
// Adicionalmente crea un hash de especialidades, cuya clave es el nombre de la
// especialidad y su dato un puntero al struct especialidad.
// Imprime por pantalla en caso de haber un error con la lectura de los archivos.
// Post: Devuelve un abb de los doctores, y almacena las especialidades en un hash,
// o NULL si hubo algun problema en la creacion o lectura del archivo.
abb_t* csv_crear_estructura_doctor(const char* ruta_csv,hash_t* hash);

// Recibe el nombre de un archivo csv con la informacion sobre los paciente de una
// clinica. Crea un hash con la informacion alli encontrada, siendo la clave el nombre
// del paciente y el dato el año de ingreso a la clinica.
// Adicionalmente crea un hash de especialidades, cuya clave es el nombre de la
// especialidad y su dato un puntero al struct especialidad.
// Imprime por pantalla en caso de haber un error con la lectura de los archivos
// o si uno de los años no es un valor valido.
// Post: Devuelve un hash de los pacientes, o NULL si hubo un porblema en la creacion
// lectura de archivo o si un año no era un valor valido.
hash_t* csv_crear_estructura_pacientes(const char* ruta_csv);


#endif
