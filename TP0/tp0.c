#include "tp0.h"

/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/

void swap (int *x, int *y) {
	int aux =*x;
	*x = *y;
	*y = aux;
}


int maximo(int vector[], int n) {
    if (n==0) return -1;
	int max=vector[0];
	int posicion_max=0;
	for (int i=1;i<n;i++){
		if (max<vector[i]){
			max=vector[i];
			posicion_max=i;
		}
	}
	return posicion_max;
}


int comparar(int vector1[], int n1, int vector2[], int n2) {
    int i = 0;
	while (i < n1 && i < n2 ){
		if(vector1[i]<vector2[i]) return -1;
		else if (vector1[i]>vector2[i]) return 1;
		else i++;
	}
	if (n1<n2) return -1;
	else if(n2<n1) return 1;
	else return 0;
}


void seleccion(int vector[], int n) {
	int posicion_maximo;
	for (int i=0 ; i < n ; i++){
		posicion_maximo=maximo(vector, n-i);
		swap(&vector[n-1-i],&vector[posicion_maximo]);
	}
}
