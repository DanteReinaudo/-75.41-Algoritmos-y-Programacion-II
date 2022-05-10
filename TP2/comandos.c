#define _POSIX_C_SOURCE 200809L

#include "funciones_tp2.h"

#define COMANDO_PEDIR_TURNO "PEDIR_TURNO"
#define COMANDO_ATENDER "ATENDER_SIGUIENTE"
#define COMANDO_INFORME "INFORME"

void eliminar_fin_linea(char* linea) {
	size_t len = strlen(linea);
	if (linea[len - 1] == '\n') {
		linea[len - 1] = '\0';
	}
}

size_t calcular_cant_parametros(char** parametros){
    size_t cont_parametros = 0;
    for (size_t i = 0; parametros[i] != NULL; i++){
        cont_parametros++;
    }
    return cont_parametros;
}

void procesar_comando(const char* comando,char** parametros, clinica_t* clinica) {
    size_t cant_parametros = calcular_cant_parametros(parametros);
	if (strcmp(comando, COMANDO_PEDIR_TURNO) == 0) {
        if(cant_parametros != 3){
            printf(ENOENT_PARAMS,comando);
            return;
        }
		pedir_turno_paciente(clinica,parametros[0],parametros[1],parametros[2]);
	} else if (strcmp(comando, COMANDO_ATENDER) == 0) {
        if(cant_parametros != 1){
            printf(ENOENT_PARAMS,comando);
            return;
        }
		atender_siguiente_paciente(clinica, parametros[0]);
	} else if (strcmp(comando, COMANDO_INFORME) == 0) {
        if(cant_parametros != 2){
            printf(ENOENT_PARAMS,comando);
            return;
        }
		informe_doctores(clinica, parametros[0], parametros[1]);
	} else {
        printf(ENOENT_CMD, comando);
	}
}

void procesar_entrada(clinica_t* clinica){
	char* linea = NULL;
	size_t c = 0;
	while (getline(&linea, &c, stdin) > 0) {
		eliminar_fin_linea(linea);
		char** campos = split(linea, ':');
		if (campos[1] == NULL) {
			printf(ENOENT_FORMATO, linea);
			free_strv(campos);
			continue;
		}
		char** parametros = split(campos[1], ',');
		procesar_comando(campos[0], parametros, clinica);
		free_strv(parametros);
		free_strv(campos);
	}
	free(linea);
}