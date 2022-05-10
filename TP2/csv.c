#define _POSIX_C_SOURCE 200809L //getline
#include "csv.h"
#define SEPARADOR ','


/* ******************************************************************
 *                      FUNCIONES AUXILIARES
 * *****************************************************************/

static void eliminar_fin_linea(char* linea) {
	size_t len = strlen(linea);
	if (linea[len - 1] == '\n') {
		linea[len - 1] = '\0';
	}
}

bool valida_numeros(char* cadena){
	bool es_numero = true;
	int inicio = 0;
	size_t largo = strlen(cadena);
	for (int i = inicio; i < largo; i++){
		if (isdigit(cadena[i]) == 0) es_numero = false;
	}
	return es_numero;
}

bool validar_anio(char* cadena){
	if(atoi(cadena) == 0 && strcmp(cadena, "0") != 0) return false;
	bool es_numerico = valida_numeros(cadena);
	return es_numerico;
}

/* ******************************************************************
 *                      FUNCIONES PRINCIPALES
 * *****************************************************************/

abb_t* csv_crear_estructura_doctor(const char* ruta_csv, hash_t* hash_especialidad){
	FILE* archivo = fopen(ruta_csv, "r");
	if (!archivo){
		printf(ENOENT_ARCHIVO, ruta_csv);
		return NULL;
	}

	abb_t* abb = abb_crear(strcmp,w_destruir_doctor);
	if (!abb) {
		fclose(archivo);
		return NULL;
	}
	char* linea = NULL;
	size_t c = 0;
	while (getline(&linea, &c, archivo) > 0) {
		eliminar_fin_linea(linea);
		char** campos = split(linea, SEPARADOR);
		//Si no existe la especialidad en el hash
		char* nombre_doc = strdup(campos[0]);
		char* especialidad_doc = strdup(campos[1]);
		doctor_t* doctor = crear_doctor(nombre_doc,especialidad_doc);
		if(!hash_pertenece(hash_especialidad,especialidad_doc)){
			//La creo
			especialidad_t* especialidad = crear_especialidad(especialidad_doc);
			if(!especialidad){
				fclose(archivo);
				free_strv(campos);
				abb_destruir(abb);
				free(linea);
				return NULL;
			}
			//Encolo el doctor en esa especialidad
			encolar_doctor_en_especialidad(especialidad,doctor);
			//Guardo la especialidad
			hash_guardar(hash_especialidad,especialidad_doc,especialidad);
		} else {
			//Si existe, obtengo la especialidad en el hash
			especialidad_t* especialidad = hash_obtener(hash_especialidad,especialidad_doc);
			//Y encolo al doctor en esa especialidad
			encolar_doctor_en_especialidad(especialidad,doctor);
		}
		abb_guardar(abb, nombre_doc,doctor);
		free_strv(campos);
	}
	free(linea);
	fclose(archivo);
	return abb;
}


hash_t* csv_crear_estructura_pacientes(const char* ruta_csv){
	FILE* archivo = fopen(ruta_csv, "r");
	if (!archivo) {
		printf(ENOENT_ARCHIVO, ruta_csv);
		return NULL;
	}

	hash_t* hash = hash_crear(free);
	if (!hash) {
		fclose(archivo);
		return NULL;
	}

	char* linea = NULL;
	size_t c = 0;
	while (getline(&linea, &c, archivo) > 0) {
		eliminar_fin_linea(linea);
		char** campos = split(linea, SEPARADOR);
		bool es_numero = validar_anio(campos[1]);
		if (es_numero == false){
			printf(ENOENT_ANIO, campos[1]);
			fclose(archivo);
			hash_destruir(hash);
			free_strv(campos);
			free(linea);
			return NULL;
		}
		int* anio = malloc(sizeof(int));
		*anio = atoi(campos[1]);
		hash_guardar(hash,campos[0],anio);
		free_strv(campos);
	}
	free(linea);
	fclose(archivo);
	return hash;
}
