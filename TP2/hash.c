#define _POSIX_C_SOURCE 200809L
#include "hash.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CAP  23
#define COEF_REDIM 2

//Definicion de variable enum

typedef enum estados_campo_hash{
    vacio,
    ocupado,
    borrado
}estados;

// Estructura auxiliar: Campo Hash

typedef struct campo_hash{
	char* clave;
	void* valor;
	estados estado;
}campo_hash_t;

// Los structs deben llamarse "hash" y "hash_iter".

struct hash{
	size_t cant_ocupados;
	size_t cant_borrados;
	size_t capacidad;
	campo_hash_t* campos;
	void (*borrar)(void*);
};

struct hash_iter{
	const hash_t* hash;
	size_t actual;
};

// Funciones Auxiliares:


//Calcula el factor de carga
float factor_de_carga(hash_t* hash){
	float cantidad_total = (float) (hash->cant_borrados + hash->cant_ocupados);
	float factor_carga = cantidad_total / (float)hash->capacidad;
	return factor_carga;
}

//Funcion de hash sdbm para hashing simple, se puede mejorar
unsigned int funcion_hash(char* clave){
	unsigned int hash = 0;
	int c;
	while ((c = *clave++)){
		hash = c + (hash << 6) + (hash << 16) - hash;
	}
	return hash;
}

//Calcula la posicion de la clave:
size_t asigna_posicion(char* clave,size_t capacidad){
	size_t posicion = funcion_hash(clave) % (int) capacidad;

	return posicion;
}

bool redimension(hash_t* hash, size_t nueva_cap){
	size_t capacidad_vieja = hash->capacidad;
	hash->capacidad = nueva_cap;
	hash->cant_borrados = 0;
	campo_hash_t* campos_aux = hash->campos;
	campo_hash_t* campos_nuevo = malloc(nueva_cap * sizeof(campo_hash_t));
	if (campos_nuevo == NULL) return false;
	for (int i = 0; i < nueva_cap; i++) campos_nuevo[i].estado = vacio;
	hash->campos = campos_nuevo;
	for (size_t i = 0; i < capacidad_vieja; i++){
		if(campos_aux[i].estado == ocupado){
			size_t nueva_pos = asigna_posicion(campos_aux[i].clave, hash->capacidad);
			if(hash->campos[nueva_pos].estado == ocupado){
				while (hash->campos[nueva_pos].estado == ocupado){
					if(nueva_pos == hash->capacidad - 1) nueva_pos = 0;
					else nueva_pos++;
            	}
			}
			hash->campos[nueva_pos].estado = ocupado;
			hash->campos[nueva_pos].clave = campos_aux[i].clave;
			hash->campos[nueva_pos].valor = campos_aux[i].valor;
		}
	}
	free(campos_aux);
	return true;
}

size_t buscar_campo_en_hash(const hash_t* hash, size_t pos, char* copia_clave, bool* no_encontro){
	while (hash->campos[pos].estado != vacio){
		if (hash->campos[pos].estado == ocupado){
			if (strcmp(hash->campos[pos].clave, copia_clave) == 0){
				return pos;
			}
		}
		if (pos == hash->capacidad - 1) pos = 0;
		else pos++;
	}
	*no_encontro = true;
	return pos;
}
/* PRIMITIVAS DEL HASH */

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
	hash_t* hash = malloc(sizeof(hash_t));
	if (hash == NULL) return NULL;
	hash->campos = malloc(CAP * sizeof(campo_hash_t));
	if (hash->campos == NULL){
		free(hash);
		return NULL;
	}
	hash->capacidad = CAP;
	hash->cant_ocupados = 0;
	hash->cant_borrados = 0;
	hash->borrar = destruir_dato;
	for (int i = 0; i < hash->capacidad; i++) hash->campos[i].estado = vacio;
	return hash;
}


bool hash_guardar(hash_t *hash, const char *clave, void *dato){
    if(factor_de_carga(hash) > 0.75){
		size_t nueva_cap = hash->capacidad * COEF_REDIM;
		if (!redimension(hash, nueva_cap)) return false;
    }
	char *copia_clave = strdup(clave);
	size_t pos = asigna_posicion(copia_clave, hash->capacidad);
	bool clave_repetida = false;
	while (hash->campos[pos].estado == ocupado && clave_repetida == false ){
		if(strcmp(hash->campos[pos].clave, copia_clave) == 0) clave_repetida = true;
		else{
			if(pos == hash->capacidad - 1) pos = 0;
			else pos++;
		}
	}
	if (clave_repetida == false){
		hash->campos[pos].clave = copia_clave;
		hash->campos[pos].valor = dato;
		hash->campos[pos].estado = ocupado;
		hash->cant_ocupados++;
	} else {
        if(hash->borrar != NULL) hash->borrar(hash->campos[pos].valor);
        hash->campos[pos].valor = dato;
		free(copia_clave);
    }
    return true;
}

void *hash_borrar(hash_t *hash, const char *clave){
	if(hash->cant_ocupados == 0) return	NULL;
	if(factor_de_carga(hash) < 0.2 && hash->capacidad > CAP){
		size_t nueva_cap = hash->capacidad / COEF_REDIM;
		redimension(hash, nueva_cap);
	}
	bool no_encontrado = false;
	char* copia_clave = strdup(clave);
	size_t pos = asigna_posicion(copia_clave, hash->capacidad);
	size_t pos_campo_buscado = buscar_campo_en_hash(hash, pos, copia_clave, &no_encontrado);
	if(!no_encontrado){
		hash->campos[pos_campo_buscado].estado = borrado;
		hash->cant_borrados ++;
		hash->cant_ocupados --;
		void* dato = hash->campos[pos_campo_buscado].valor;
		free(copia_clave);
		free(hash->campos[pos_campo_buscado].clave);
		hash->campos[pos_campo_buscado].clave = NULL;
		hash->campos[pos_campo_buscado].valor= NULL;
		return dato;
	}
	free(copia_clave);
    return NULL;
}

void *hash_obtener(const hash_t *hash, const char *clave){
	if(hash->cant_ocupados == 0) return	NULL;
	bool no_encontrado = false;
	char* copia_clave = strdup(clave);
	size_t pos = asigna_posicion(copia_clave, hash->capacidad);
	size_t pos_campo_buscado = buscar_campo_en_hash(hash, pos, copia_clave, &no_encontrado);
	if(!no_encontrado){
		free(copia_clave);
		return hash->campos[pos_campo_buscado].valor;
	}
	free(copia_clave);
	return NULL;
}

bool hash_pertenece(const hash_t *hash, const char *clave){
	if(hash->cant_ocupados == 0) return	false;
	bool no_encontrado = false;
	char* copia_clave = strdup(clave);
	size_t pos = asigna_posicion(copia_clave, hash->capacidad);
	buscar_campo_en_hash(hash, pos, copia_clave, &no_encontrado);
	if(!no_encontrado){
		free(copia_clave);
		return true;
	}
	free(copia_clave);
	return false;
}

size_t hash_cantidad(const hash_t *hash){
	return (hash->cant_ocupados);
}

void hash_destruir(hash_t *hash){
	for (int i = 0; i < hash->capacidad; i++){
		if (hash->campos[i].estado == ocupado){
			if (hash->borrar != NULL){
				hash->borrar(hash->campos[i].valor);
			}
			free(hash->campos[i].clave);
		}
	}
	free(hash->campos);
	free(hash);
}

/* Iterador del hash */

hash_iter_t *hash_iter_crear(const hash_t *hash){
	hash_iter_t* hash_iter = malloc(sizeof(hash_iter_t));
	if (hash_iter == NULL) return NULL;
	hash_iter->hash = hash;
	size_t cont = 0;
	while (cont < hash->capacidad && hash->campos[cont].estado != ocupado){
		cont++;
	}
	hash_iter->actual = cont;
	return hash_iter;
}

bool hash_iter_avanzar(hash_iter_t *iter){
	if (hash_iter_al_final(iter)) return false;
	iter->actual++;
	if (hash_iter_al_final(iter)) return false;
	while (iter->hash->campos[iter->actual].estado != ocupado && iter->actual < iter->hash->capacidad){
		iter->actual++;
		if (hash_iter_al_final(iter)) return false;
	}

	return true;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter){
	if (hash_iter_al_final(iter)) return NULL;
    return iter->hash->campos[iter->actual].clave;
}

bool hash_iter_al_final(const hash_iter_t *iter){
	return (iter->actual == iter->hash->capacidad);
}

void hash_iter_destruir(hash_iter_t* iter){
	free(iter);
}