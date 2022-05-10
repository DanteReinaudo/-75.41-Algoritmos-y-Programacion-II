#include "heap.h"
#include "testing.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int funcion_comparacion(const void* a, const void* b){
    if(*(int*)a == *(int*)b) return 0;
    if(*(int*)a > *(int*)b) return 1;
    return -1;
}

void prueba_crear_heap_vacio(){
    printf("~~INICIO DE PRUEBA DE HEAP VACIO~~\n");
    heap_t* heap = heap_crear(funcion_comparacion);
    print_test("Prueba heap crear heap vacio", heap);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap ver elemento maximo, es NULL, no existe", !heap_ver_max(heap));
    print_test("Prueba heap vacio esta vacio",  heap_esta_vacio(heap));
    print_test("Prueba heap desencolar elemento, es NULL, no existe", !heap_desencolar(heap));
    heap_destruir(heap, NULL);
}

void prueba_crear_heap_vacio_arr(){
    printf("~~INICIO DE PRUEBA CREAR HEAP DE ARREGLO NULO~~\n");
    heap_t* heap = heap_crear_arr(NULL,0,funcion_comparacion);
    print_test("Prueba heap crear heap con arreglo nulo", heap);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap ver elemento maximo, es NULL, no existe", !heap_ver_max(heap));
    print_test("Prueba heap vacio esta vacio",  heap_esta_vacio(heap));
    print_test("Prueba heap desencolar elemento, es NULL, no existe", !heap_desencolar(heap));
    heap_destruir(heap, NULL);
}

void prueba_crear_heap_arr(){
    printf("~~INICIO DE PRUEBA CREAR HEAP DESDE ARREGLO~~\n");
    int* v1 = malloc(sizeof(int));
	int* v2 = malloc(sizeof(int));
	int* v3 = malloc(sizeof(int));
	int* v4 = malloc(sizeof(int));
	*v1 = 10;
	*v2 = 30;
	*v3 = 20;
	*v4 = 50;
	void** vector = malloc( 4 * sizeof(void*) );
    vector[0] = v1;
    vector[1] = v2;
    vector[2] = v3;
    vector[3] = v4;
    heap_t* heap = heap_crear_arr(vector,3,funcion_comparacion);
    print_test("Prueba crear heap con arreglo", heap);
    print_test("Pruebo si la cantidad de elementos es corrrecta", heap_cantidad(heap) == 3);
    print_test("Pruebo que el elemento maximo es correcto", *(int*) heap_ver_max(heap) == 30);
    print_test("Pruebo que el heap no esta vacio", !heap_esta_vacio(heap));
    print_test("Prueba que puedo desencolar elementos", *(int*) heap_desencolar(heap) == 30);
    print_test("Pruebo si la cantidad de elementos es corrrecta", heap_cantidad(heap) == 2);
    print_test("Pruebo que el elemento maximo es correcto", *(int*) heap_ver_max(heap) == 20);
    print_test("Pruebo que el heap no esta vacio", !heap_esta_vacio(heap));
    print_test("Prueba que puedo encolar elementos", heap_encolar(heap,vector[3]));
    print_test("Pruebo si la cantidad de elementos es corrrecta", heap_cantidad(heap) == 3);
    print_test("Pruebo que el elemento maximo es correcto", *(int*) heap_ver_max(heap) == 50);
    print_test("Pruebo que el heap no esta vacio", !heap_esta_vacio(heap));
    for (int i = 0 ; i < 4 ; i ++){
		free(vector[i]);
	}
    free(vector);
    heap_destruir(heap, NULL);
}

void prueba_heap_heapsort(){
	printf("~~INICIO DE PRUEBA HEAPSORT~~\n");
	void** vector = malloc( 10 * sizeof(void*) );
	if (vector == NULL) free (vector);
	for (int i = 0 ; i < 10 ; i++){
		int* valor = malloc(sizeof(int));
		//genero valores desordenados
		if (i%2 == 0) *valor = (i*i - i);
        if (i%2 == 1) *valor = -i + 3;
        vector[i] = valor;
	}
	int vector_ordenado[]= {-6,-4,-2,0,0,2,2,12,30,56};
	heap_sort(vector,10,funcion_comparacion);
	for (int i = 0 ; i < 10 ; i++){
		print_test("El valor coincide con el esperado: ", (vector_ordenado[i] == *(int*)vector[i]));
	}
	for (int i = 0 ; i < 10 ; i++){
		free(vector[i]);
	}
	free(vector);
}

void prueba_heap_insertar(){
	printf("~~INICIO DE PRUEBA DE INSERTAR EN HEAP~~\n");
    heap_t* heap = heap_crear(funcion_comparacion);
    int vector[] = {1,2,3};

    print_test("Prueba heap encolar un valor", heap_encolar(heap,&vector[1]));
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap ver elemento maximo, es el correcto", *(int*) heap_ver_max(heap) == vector[1]);
    print_test("Prueba heap con un elemento no esta vacio", !heap_esta_vacio(heap));

    print_test("Prueba heap encolar otro valor", heap_encolar(heap,&vector[2]));
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);
    print_test("Prueba heap ver elemento maximo, es el correcto", *(int*) heap_ver_max(heap) == vector[2]);

	print_test("Prueba heap encolar otro valor", heap_encolar(heap,&vector[0]));
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 3);
    print_test("Prueba heap ver elemento maximo, es el correcto", *(int*) heap_ver_max(heap) == vector[2]);

    heap_destruir(heap, NULL);

}


void prueba_heap_desencolar(){
	printf("~~INICIO DE PRUEBA DE DESENCOLAR EN HEAP~~\n");
    heap_t* heap = heap_crear(funcion_comparacion);
    int vector[] = {1,2,2,5,0};
    print_test("Pruebo si se creo el heap", heap);

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba heap encolar un valor", heap_encolar(heap,&vector[0]));
    print_test("Pruebo que el heap no esta vacio", !heap_esta_vacio(heap));
    print_test("Prueba si la cantidad de elementos es correcta", heap_cantidad(heap) == 1);
    print_test("Pruebo si el elemento maximo, es el correcto", *(int*) heap_ver_max(heap) == vector[0]);


    print_test("Pruebo que el elemento desencolado es el correcto", *(int*)heap_desencolar(heap) == vector[0]);
    print_test("Pruebo que cantidad de elementos es 0 despues de desencolar", heap_cantidad(heap) == 0);
    print_test("Prueba heap esta vacio despues de desencolar el unico elemento encolado ", heap_esta_vacio(heap));
    print_test("Pruebo que no hay maximo", !heap_ver_max(heap));

	/* Inserta varios valores y luego los borra */

	// Encolo el 2
    print_test("Prueba heap encolar un valor", heap_encolar(heap,&vector[1]));
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap ver elemento maximo, es el correcto", *(int*) heap_ver_max(heap) == vector[1]);
    print_test("Prueba heap con un elemento no esta vacio", !heap_esta_vacio(heap));

    // Encolo otro 2
    print_test("Prueba heap encolar otro valor", heap_encolar(heap,&vector[2]));
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);
    print_test("Prueba heap ver elemento maximo, es el correcto", *(int*) heap_ver_max(heap) == vector[2]);
    print_test("Prueba heap no esta vacio", !heap_esta_vacio(heap));

    // Encolo el 5
    print_test("Prueba heap encolar otro valor", heap_encolar(heap,&vector[3]));
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 3);
    print_test("Prueba heap ver elemento maximo, es el correcto", *(int*) heap_ver_max(heap) == vector[3]);
    print_test("Prueba heap no esta vacio", !heap_esta_vacio(heap));

    //Desencolo el 5
    print_test("Pruebo que el elemento desencolado es el correcto", *(int*)heap_desencolar(heap) == vector[3]);
    print_test("Pruebo que cantidad de elementos es 2 despues de desencolar", heap_cantidad(heap) == 2);
    print_test("Prueba heap ver elemento maximo, es el correcto", *(int*) heap_ver_max(heap) == vector[2]);
    print_test("Prueba heap no esta vacio", !heap_esta_vacio(heap));

    // Desencolo el 2
    print_test("Pruebo que el elemento desencolado es el correcto", *(int*)heap_desencolar(heap) == vector[2]);
    print_test("Pruebo que cantidad de elementos es 1 despues de desencolar", heap_cantidad(heap) == 1);
    print_test("Prueba heap ver elemento maximo, es el correcto", *(int*) heap_ver_max(heap) == vector[1]);
    print_test("Prueba heap no esta vacio", !heap_esta_vacio(heap));

    // Encolo el 0
    print_test("Prueba heap encolar otro valor", heap_encolar(heap,&vector[4]));
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);
    print_test("Prueba heap ver elemento maximo, es el correcto", *(int*) heap_ver_max(heap) == vector[1]);
    print_test("Prueba heap no esta vacio", !heap_esta_vacio(heap));

    heap_destruir(heap, NULL);
}

void prueba_heap_destruir_con_funcion(){
	printf("~~INICIO DE PRUEBA DESTRUIR HEAP FUNCION DESTRUCCION~~\n");

	heap_t* heap = heap_crear(funcion_comparacion);
	print_test("Pruebo si se creo el heap", heap);

	//Declaro valores
	int* v1 = malloc(sizeof(int));
	int* v2 = malloc(sizeof(int));
	int* v3 = malloc(sizeof(int));
	*v1 = 10;
	*v2 = 30;
	*v3 = 20;

	//Encolo
	print_test("Prueba heap encolar un valor", heap_encolar(heap,v1));
	print_test("Prueba heap encolar un valor", heap_encolar(heap,v2));
	print_test("Prueba heap encolar un valor", heap_encolar(heap,v3));

	heap_destruir(heap,free);
	print_test("Preuba heap se destruyo correctamente", true);

}

void prueba_heap_volumen(size_t largo){
	printf("~~INICIO DE PRUEBA VOLUMEN EN HEAP~~\n");

	// Creo Heap
	heap_t* heap = heap_crear(funcion_comparacion);
	print_test("Pruebo si se creo el heap", heap);
	int* valores[largo];

	//Inserto varias elementos en el heap
	bool inserto_bien = true;
	bool comprueba_max = true;
	bool comprueba_cant = true;
	bool comprueba_vacio = true;
	for(int i=0; i<largo;i++){
		valores[i] = malloc(sizeof(int));
		*valores[i] = i;
		inserto_bien &= heap_encolar(heap,valores[i]);
		comprueba_max &= (heap_ver_max(heap) == valores[i]);
		comprueba_cant &= (heap_cantidad(heap) == i+1);
		comprueba_vacio &= !heap_esta_vacio(heap);
	}
	// Verifico que que la prueba se realizo correctamente
	print_test("Prueba se insertaron todos los elementos correctamente ", inserto_bien);
	print_test("Prueba el maximo por cada iteracion fue el correcto", comprueba_max);
	print_test("Prueba la cantidad de elementos del heap por cada iteracion fue correcta", comprueba_cant);
	print_test("Prueba la lista no esta vacia", comprueba_vacio);

	//Desencolo todos los elementos
	comprueba_max = true;
	comprueba_cant = true;
	comprueba_vacio = true;
	bool desencolo_bien = true;

	for(int i=0 ; i<largo ; i++){
		int* maximo = heap_desencolar(heap);
		if (*maximo != 0){
			desencolo_bien &= (*maximo == *valores[largo-i-1]);
			comprueba_max &= (*(int*)heap_ver_max(heap) == largo-i-2);
			comprueba_cant &= (heap_cantidad(heap) == largo-i-1);
			comprueba_vacio &= !heap_esta_vacio(heap);
		}
		free(maximo);
	}

	// Verifico que la prueba se realizo correctamente
	print_test("Prueba se eliminaron todos los elementos correctamente", desencolo_bien);
	print_test("Prueba el maximo por cada iteracion fue el correcto", comprueba_max);
	print_test("Prueba la cantidad de elementos por cada iteracion fue correcto", comprueba_cant);
	print_test("Prueba que no hay maximo", heap_ver_max(heap) == NULL);
	print_test("Prueba el largo de la lista es 0",heap_cantidad(heap) == 0);
	print_test("Prueba lista esta vacia",heap_esta_vacio(heap));

	heap_destruir(heap,free);

	// Creo otro Heap
	heap_t* heap1 = heap_crear(funcion_comparacion);
	print_test("Pruebo si se creo el heap", heap1);
	int* valores1[largo];

	//Inserto varias elementos en el heap
	inserto_bien = true;
	comprueba_max = true;
	comprueba_cant = true;
	comprueba_vacio = true;
	for(int i=0; i<largo;i++){
		valores1[i] = malloc(sizeof(int));
		*valores1[i] = -i;
		inserto_bien &= heap_encolar(heap1,valores1[i]);
		comprueba_max &= (heap_ver_max(heap1) == valores1[0]);
		comprueba_cant &= (heap_cantidad(heap1) == i+1);
		comprueba_vacio &= !heap_esta_vacio(heap1);
	}
	// Verifico que que la prueba se realizo correctamente
	print_test("Prueba se insertaron todos los elementos correctamente ", inserto_bien);
	print_test("Prueba el maximo por cada iteracion fue el correcto", comprueba_max);
	print_test("Prueba la cantidad de elementos del heap por cada iteracion fue correcta", comprueba_cant);
	print_test("Prueba la lista no esta vacia", comprueba_vacio);

	heap_destruir(heap1,free);
}

void pruebas_heap_alumno(){
    prueba_crear_heap_vacio();
    prueba_heap_insertar();
    prueba_heap_desencolar();
    prueba_heap_destruir_con_funcion();
    prueba_heap_volumen(420);
    prueba_crear_heap_vacio_arr();
    prueba_crear_heap_arr();
    prueba_heap_heapsort();
}
