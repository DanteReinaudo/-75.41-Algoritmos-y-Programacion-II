#include "clinica.h"


/* ******************************************************************
 *                     ESTRUCTURA PRINCIPAL
 * *****************************************************************/

 struct clinica{
	abb_t* doctores;
	hash_t* pacientes;
	hash_t* especialidades;
};

/* ******************************************************************
 *                      FUNCIONES AUXILIARES
 * *****************************************************************/
bool validar_prioridad(char* prioridad){
	return (strcmp(prioridad,"URGENTE") == 0) || (strcmp(prioridad,"REGULAR") == 0);
}

void mostrar_mensaje_paciente(char* nombre_paciente, long cant_pacientes, char* nombre_especialidad){
	printf(PACIENTE_ATENDIDO, nombre_paciente);
	printf(CANT_PACIENTES_ENCOLADOS,cant_pacientes,nombre_especialidad);
}

/* ******************************************************************
 *                           PRIMITIVAS
 * *****************************************************************/

clinica_t* crear_clinica(char** argv){
	clinica_t* clinica = malloc(sizeof(clinica_t));
	if (!clinica) return NULL;
	hash_t* hash_especialidades = hash_crear(w_destruir_especialidad);
	if(!hash_especialidades){
		free(clinica);
		return NULL;
	}
	clinica->doctores = csv_crear_estructura_doctor(argv[1],hash_especialidades);
	if(!clinica->doctores){
		hash_destruir(hash_especialidades);
		free(clinica);
		return NULL;
	}
	clinica->pacientes = csv_crear_estructura_pacientes(argv[2]);
	if(!clinica->pacientes){
		hash_destruir(hash_especialidades);
		abb_destruir(clinica->doctores);
		free(clinica);
		return NULL;
	}
	clinica->especialidades = hash_especialidades;
	return clinica;
}


void pedir_turno_paciente(clinica_t* clinica, char* nombre, char* nombre_especialidad , char* prioridad){

	if (!hash_pertenece(clinica->pacientes,nombre)){
		printf(ENOENT_PACIENTE,nombre);
		return;
	}
	especialidad_t* especialidad = hash_obtener(clinica->especialidades,nombre_especialidad);
	if (!especialidad){
		printf(ENOENT_ESPECIALIDAD,nombre_especialidad);
		return;
	}

	if (!validar_prioridad(prioridad)){
		printf(ENOENT_URGENCIA,prioridad);
		return;
	}
	char* nombre_paciente = strdup(nombre);
	if (strcmp(prioridad,"URGENTE") == 0){
		encolar_paciente_urgencias(especialidad,nombre_paciente);
	}else{
		int* anio = hash_obtener(clinica->pacientes,nombre);
		encolar_paciente_regulares(especialidad,nombre_paciente,anio);
	}
	printf(PACIENTE_ENCOLADO,nombre);
	long cant_pacientes = cantidad_pacientes_especialidad(especialidad);
	printf(CANT_PACIENTES_ENCOLADOS,cant_pacientes,nombre_especialidad);
}

void atender_siguiente_paciente(clinica_t* clinica, char* nombre_doc){
	if(!abb_pertenece(clinica->doctores,nombre_doc)){
		printf(ENOENT_DOCTOR, nombre_doc);
		return;
	}
	doctor_t* doctor = abb_obtener(clinica->doctores, nombre_doc);
	especialidad_t* especialidad = hash_obtener(clinica->especialidades, conseguir_especialidad_doctor(doctor));
	if(hay_pacientes_urgentes(especialidad)){
		atiende_doctor(doctor);
		char* paciente_desencolado = desencolar_urgente(especialidad);
		mostrar_mensaje_paciente(paciente_desencolado, cantidad_pacientes_especialidad(especialidad), nombre_especialidad(especialidad));
		free(paciente_desencolado);
	}else{
		if(!hay_pacientes_regulares(especialidad)){
			printf(SIN_PACIENTES);
			return;
		}
		atiende_doctor(doctor);
		paciente_t* paciente_desencolado = desencolar_regular(especialidad);
		mostrar_mensaje_paciente(nombre_paciente(paciente_desencolado), cantidad_pacientes_especialidad(especialidad), nombre_especialidad(especialidad));
		destruir_paciente(paciente_desencolado);
	}
}

bool visitar(const char* clave, void* dato, void* extra){
	lista_insertar_ultimo((lista_t*)extra,dato);
	return true;
}

bool mostrar_doctor(const char* clave, void* dato, void* extra){
	printf(INFORME_DOCTOR, *(size_t*)extra, nombre_doctor((doctor_t*)dato), conseguir_especialidad_doctor((doctor_t*)dato)
	, pacientes_doctor((doctor_t*)dato));
	*(size_t*) extra+=1;
	return true;
}

void recorrer_doctores_por_rangos(clinica_t* clinica, char* minimo, char* maximo){
	size_t contador = 1;
	lista_t* lista_doctores = lista_crear();
	abb_in_order_por_rangos(clinica->doctores, visitar,lista_doctores,minimo,maximo);
	printf(DOCTORES_SISTEMA,lista_largo(lista_doctores));
	lista_iter_t* iterador_lista = lista_iter_crear(lista_doctores);
	while(!lista_iter_al_final(iterador_lista)){
		doctor_t* doctor = lista_iter_ver_actual(iterador_lista);
		printf(INFORME_DOCTOR, contador, nombre_doctor(doctor), conseguir_especialidad_doctor(doctor),pacientes_doctor(doctor));
		lista_iter_avanzar(iterador_lista);
		contador++;
	}
	lista_iter_destruir(iterador_lista);
	lista_destruir(lista_doctores,NULL);
}

void informe_doctores(clinica_t* clinica,char* inicio,char* fin){
	bool hay_inicio = strcmp(inicio,"") == 0 ? false : true;
	bool hay_fin = strcmp(fin,"") == 0 ? false : true;
	if(!hay_inicio && !hay_fin){
		size_t contador = 1;
		printf(DOCTORES_SISTEMA,abb_cantidad(clinica->doctores));
		abb_in_order(clinica->doctores, mostrar_doctor, &contador);
		return;
	}
	//FALTARIAN CASOS BORDE
	if(!hay_inicio){
		inicio = "AAAAAAAAAA";
	}
	if(!hay_fin){
		fin = "ZZZZZZZZZZZZ";
	}
	recorrer_doctores_por_rangos(clinica, inicio, fin);
	return;
}


void destruir_clinica(clinica_t* clinica){
	abb_destruir(clinica->doctores);
	hash_destruir(clinica->pacientes);
	hash_destruir(clinica->especialidades);
	free(clinica);
}
