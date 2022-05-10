#include "strutil.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char *substr(const char *str, size_t n){
	char* sub_str = calloc(n+1,sizeof(char));
	if (sub_str == NULL) return NULL;
	strncpy(sub_str,str,n);
	return sub_str;
}

char **split(const char *str, char sep){
	if (str == NULL){
		char** vector_nulo = calloc(1,sizeof(char*));
		return vector_nulo;
	}
	size_t largo = strlen(str);
	size_t pos[largo]; //Arreglo donde guardo las posiciones de la separacion
	size_t cant = 0; // La cantidad de separadores que aparecen
	for (int i = 0;i < largo;i++){
		if (str[i]==sep){
			pos[cant]=i;
			cant++;
		}
	}
	char** str_split = calloc(cant+2,sizeof(char*));
	if (str_split == NULL) return NULL;
	if (cant == 0){
		str_split[0] = substr(str,largo);
		return str_split;
	}
	str_split[0] = substr(str,pos[0]);
	if (str_split[0] == NULL) return NULL;
	for (int i = 1;i < cant ; i++){
		size_t d = pos[i]- pos[i-1] - 1;
		str_split[i] = substr(str+pos[i-1]+1,d);
		if (str_split[i] == NULL) return NULL;
	}
	str_split[cant] = substr(str+pos[cant-1]+1,largo-(pos[cant-1]+1));
	return str_split;
}

char *join(char **strv, char sep){
	size_t cant = 0;
	size_t largo = 0;
	while (strv[cant] != NULL){
		largo = largo + strlen(strv[cant]);
		cant++;
	}
	char* str_join = calloc(largo+cant+1,sizeof(char));
	if(str_join == NULL)return NULL;
	char* inicio = str_join;
	for (size_t i=0; i < cant ; i++){
		strcat(inicio, strv[i]);
		inicio += strlen(strv[i]);
		if(i != cant -1) inicio[i]=sep;
	}
	return str_join;
}


void free_strv(char *strv[]){
	for (size_t cont=0; strv[cont] != NULL; cont++){
		free(strv[cont]);
	}
	free(strv);
}
