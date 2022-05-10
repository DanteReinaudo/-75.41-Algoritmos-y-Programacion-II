#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * ******************************************************************/

/* Funciones de Pruebas */
void prueba_lista_vacia(){
	printf("~~INICIO DE PRUEBA DE LISTA VACIA~~\n");

	// Creo Lista
	lista_t* lista1 = lista_crear();

	//Verifico si la lista fue creada
	print_test("La lista fue creada", lista1 != NULL);

	// Pruebo que al crear una lista esta vacia
	print_test("La lista esta vacia", lista_esta_vacia(lista1));

	// Pruebo que el largo es 0 en una lista vacia
	print_test("El largo de la lista es 0", lista_largo(lista1)==0);

	//Pruebo no puedo ver el primero ya que la lista esta vacia
	print_test("No existe el primero", lista_ver_primero(lista1)==NULL);

	//Pruebo no puedo ver el ultimo ya que la lista esta vacia
	print_test("No existe el ultimo", lista_ver_ultimo(lista1)==NULL);

	// Pruebo que no puedo borrar elementos de una lista vacio
	print_test("No puedo borrar elementos en una lista vacía", lista_borrar_primero(lista1)==NULL);

	//Destruyo la lista sin pasar una funcion
	lista_destruir(lista1,NULL);
}

void prueba_enlisto_desenlisto(){
	printf("~~INICIO DE PRUEBA DE ENLISTA Y DESENLISTAR~~ \n");

	// Creo la lista
	lista_t* lista2 = lista_crear();

	//Verifico si la lista fue creada
	print_test("La lista fue creada", lista2 != NULL);

	// Declaro elementos a insertar
	int v1 = 5;
	float v2 = 8.5;
	int v3 = 420;
	double v4 = 4.6;

	//Inserto v1 en el primer lugar y compruebo que las condiciones de la lista son correctas
	print_test("Inserto en el primer lugar un puntero a v1", lista_insertar_primero(lista2,&v1));
	print_test("Observo cual es el primero, debe ser v1", lista_ver_primero(lista2) == &v1);
	print_test("Observo cual es el ultimo debe ser v1", lista_ver_ultimo(lista2) == &v1);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista2));
	print_test("Compruebo el largo de la lista, debe ser 1", lista_largo(lista2)==1);


	//Inserto v3 en el ultimo lugar y compruebo que las condiciones de la lista son correctas
	print_test("Inserto en el ultimo lugar un puntero a v3", lista_insertar_ultimo(lista2,&v3));
	print_test("Observo cual es el primero, debe ser v1", lista_ver_primero(lista2) == &v1);
	print_test("Observo cual es el ultimo debe ser v3", lista_ver_ultimo(lista2) == &v3);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista2));
	print_test("Compruebo el largo de la lista, debe ser 2", lista_largo(lista2)==2);

	//Inserto v2 en el primer lugar y compruebo que las condiciones de la lista son correctas
	print_test("Inserto en el primer lugar un puntero a v2", lista_insertar_primero(lista2,&v2));
	print_test("Observo cual es el primero, debe ser v2", lista_ver_primero(lista2) == &v2);
	print_test("Observo cual es el ultimo debe ser v1", lista_ver_ultimo(lista2) == &v3);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista2));
	print_test("Compruebo el largo de la lista, debe ser 3", lista_largo(lista2)==3);

	//Inserto v4 en el ultimo lugar y compruebo que las condiciones de la lista son correctas
	print_test("Inserto en el ultimo lugar un puntero a v4", lista_insertar_ultimo(lista2,&v4));
	print_test("Observo cual es el primero, debe ser v2", lista_ver_primero(lista2) == &v2);
	print_test("Observo cual es el ultimo debe ser v4", lista_ver_ultimo(lista2) == &v4);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista2));
	print_test("Compruebo el largo de la lista, debe ser 4", lista_largo(lista2)==4);

	// Comprueba que puedo insertar el NULL en el primer lugar y se mantienen las condiciones de la lista
	print_test("Inserto un puntero NULL en el primer lugar", lista_insertar_primero(lista2,NULL));
	print_test("Observo cual es el primero, debe ser NULL", lista_ver_primero(lista2) == NULL);
	print_test("Observo cual es el ultimo debe ser v4", lista_ver_ultimo(lista2) == &v4);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista2));
	print_test("Compruebo el largo de la lista, debe ser 5", lista_largo(lista2)==5);

	// Comprueba que puedo insertar el NULL en el ultimo lugar y se mantienen las condiciones de la lista
	print_test("Inserto un puntero NULL en el ultimo lugar", lista_insertar_ultimo(lista2,NULL));
	print_test("Observo cual es el primero, debe ser NULL", lista_ver_primero(lista2) == NULL);
	print_test("Observo cual es el ultimo debe ser NULL", lista_ver_ultimo(lista2) == NULL);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista2));
	print_test("Compruebo el largo de la lista, debe ser 6", lista_largo(lista2)==6);

	//Elimino nodo a nodo y compruebo que se mantengan las condiciones de la lista
	print_test("Elimino el primero, debe ser NULL", lista_borrar_primero(lista2) == NULL);
	print_test("Observo cual es el primero, debe ser el puntero a v2", lista_ver_primero(lista2) == &v2);
	print_test("Observo cual es el ultimo debe ser NULL", lista_ver_ultimo(lista2) == NULL);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista2));
	print_test("Compruebo el largo de la lista, debe ser 5", lista_largo(lista2)==5);

	print_test("Elimino el primero, debe ser v2", lista_borrar_primero(lista2) == &v2);
	print_test("Observo cual es el primero, debe ser el puntero a v1", lista_ver_primero(lista2) == &v1);
	print_test("Observo cual es el ultimo debe ser NULL", lista_ver_ultimo(lista2) == NULL);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista2));
	print_test("Compruebo el largo de la lista, debe ser 4", lista_largo(lista2)==4);

	print_test("Elimino el primero, debe ser v1", lista_borrar_primero(lista2) == &v1);
	print_test("Observo cual es el primero, debe ser el puntero a v3", lista_ver_primero(lista2) == &v3);
	print_test("Observo cual es el ultimo debe ser NULL", lista_ver_ultimo(lista2) == NULL);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista2));
	print_test("Compruebo el largo de la lista, debe ser 3", lista_largo(lista2)==3);

	print_test("Elimino el primero, debe ser v3", lista_borrar_primero(lista2) == &v3);
	print_test("Observo cual es el primero, debe ser el puntero a v4", lista_ver_primero(lista2) == &v4);
	print_test("Observo cual es el ultimo debe ser NULL", lista_ver_ultimo(lista2) == NULL);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista2));
	print_test("Compruebo el largo de la lista, debe ser 2", lista_largo(lista2)==2);

	print_test("Elimino el primero, debe ser v4", lista_borrar_primero(lista2) == &v4);
	print_test("Observo cual es el primero, debe ser el puntero NULL", lista_ver_primero(lista2) == NULL);
	print_test("Observo cual es el ultimo debe ser NULL", lista_ver_ultimo(lista2) == NULL);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista2));
	print_test("Compruebo el largo de la lista, debe ser 1", lista_largo(lista2)==1);

	print_test("Elimino el primero, debe ser NULL", lista_borrar_primero(lista2) == NULL);

// Compruebo que al insertar varios elementos y eliminarlos la lista se comporta como recien creada
	// Pruebo que la lista esta vacia
	print_test("Compruebo que la lista esta vacia", lista_esta_vacia(lista2));

	// Pruebo que el largo es 0
	print_test("Compruebo que el largo de la lista debe ser 0", lista_largo(lista2)==0);

	//Pruebo no puedo ver el primero ya que la lista esta vacia
	print_test("No existe el primero", lista_ver_primero(lista2)==NULL);

	//Pruebo no puedo ver el ultimo ya que la lista esta vacia
	print_test("No existe el ultimo", lista_ver_ultimo(lista2)==NULL);

	// Pruebo que no puedo borrar elementos de una lista vacio
	print_test("No puedo borrar elementos en una lista vacía", lista_borrar_primero(lista2)==NULL);

	//Destruyo la lista sin pasar una funcion
	lista_destruir(lista2,NULL);
}

//Compruebo que al insertar el primer elemento usando lista_insertar_primero() y
//lista_insertar_ultimo() la lista se comporta igual
void prueba_insertar_primero(){
	printf("~~INICIO DE PRUEBA DE INSERTAR EL PRIMER ELEMENTO~~ \n");

	// Creo la lista
	lista_t* lista3 = lista_crear();

	//Verifico si la lista fue creada
	print_test("La lista fue creada", lista3 != NULL);

	// Declaro elemento a insertar
	int n1 = 1;

	//Utilizo lista_insertar_primero() y compruebo que las condiciones de la lista son correctas
	print_test("Inserto en el primer lugar un puntero a v1", lista_insertar_primero(lista3,&n1));
	print_test("Observo cual es el primero, debe ser n1", lista_ver_primero(lista3) == &n1);
	print_test("Observo cual es el ultimo debe ser n1", lista_ver_ultimo(lista3) == &n1);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista3));
	print_test("Compruebo el largo de la lista, debe ser 1", lista_largo(lista3)==1);

	//Elimino el primero y compruebo que se mantengan las condiciones de la lista
	print_test("Elimino el primero, debe ser n1", lista_borrar_primero(lista3) == &n1);
	print_test("Observo que no hay primero", lista_ver_primero(lista3) == NULL);
	print_test("Observo no hay ultimo", lista_ver_ultimo(lista3) == NULL);
	print_test("Compruebo que la lista esta vacia", lista_esta_vacia(lista3));
	print_test("Compruebo el largo de la lista, debe ser 0", lista_largo(lista3)==0);

	//Utilizo lista_insertar_ultimo() y compruebo que las condiciones de la lista son correctas
	print_test("Inserto en el ultimo lugar un puntero a n1", lista_insertar_primero(lista3,&n1));
	print_test("Observo cual es el primero, debe ser n1", lista_ver_primero(lista3) == &n1);
	print_test("Observo cual es el ultimo debe ser n1", lista_ver_ultimo(lista3) == &n1);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista3));
	print_test("Compruebo el largo de la lista, debe ser 1", lista_largo(lista3)==1);

	//Elimino el primero y compruebo que se mantengan las condiciones de la lista
	print_test("Elimino el primero, debe ser n1", lista_borrar_primero(lista3) == &n1);
	print_test("Observo que no hay primero", lista_ver_primero(lista3) == NULL);
	print_test("Observo no hay ultimo", lista_ver_ultimo(lista3) == NULL);
	print_test("Compruebo que la lista esta vacia", lista_esta_vacia(lista3));
	print_test("Compruebo el largo de la lista, debe ser 0", lista_largo(lista3)==0);

	//Destruyo la lista sin pasar una funcion
	lista_destruir(lista3,NULL);
}

void prueba_volumen(){
	printf("~~INICIO DE PRUEBA DE VOLUMEN ~~\n");

	// Creo lista
	lista_t* lista4 = lista_crear();

	//Verifico si la lista fue creada
	print_test("La lista fue creada", lista4 != NULL);

	//Inserto el primer dato
	int ultimo_en_lista = 0;
	print_test("Inserto un puntero",lista_insertar_ultimo(lista4,&ultimo_en_lista));
	print_test("Observo cual es el primero, debe ser el puntero ultimo_en_lista", lista_ver_primero(lista4) == &ultimo_en_lista);
	print_test("Observo cual es el ultimo debe ser el puntero ultimo_en_lista", lista_ver_ultimo(lista4) == &ultimo_en_lista);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista4));
	print_test("Compruebo el largo de la lista, debe ser 1", lista_largo(lista4)==1);

	//Inserto varias elementos usando lista_insertar_primero()
	bool inserto_bien1 = true;
	bool comprueba_primero1 = true;
	bool comprueba_ultimo1 = true;
	bool comprueba_largo1 = true;
	for(int i=1; i<1000;i++){
		void* puntero= &i + i; //Genero punteros distintos para no apilar siempre el mismo
		inserto_bien1 &= lista_insertar_primero(lista4,puntero);
		comprueba_primero1 &= (lista_ver_primero(lista4) == puntero);
		comprueba_ultimo1 &= (lista_ver_ultimo(lista4) == &ultimo_en_lista);
		comprueba_largo1 &= (lista_largo(lista4)==i+1);
	}

	// Verifico que que la prueba se realizo correctamente
	print_test("Se insertaron todos los elementos correctamente ", inserto_bien1);
	print_test("El primero por cada iteracion fue el correcto", comprueba_primero1);
	print_test("El ultimo por cada iteracion fue el correcto", comprueba_ultimo1);
	print_test("El largo de la lista por cada iteracion fue correcto", comprueba_largo1);
	print_test("Comprueba que la lista no esta vacia", !lista_esta_vacia(lista4));

	//Inserto varias elementos usando lista_insertar_ultimo()
	void* primero = lista_ver_primero(lista4);
	size_t largo_inicial=lista_largo(lista4);
	bool inserto_bien2 = true;
	bool comprueba_primero2 = true;
	bool comprueba_ultimo2 = true;
	bool comprueba_largo2 = true;
	for(size_t j=0; j<1000;j++){
		void* puntero= &j + j; //Genero punteros distintos para no apilar siempre el mismo
		inserto_bien2 &= lista_insertar_ultimo(lista4,puntero);
		comprueba_primero2 &= (lista_ver_primero(lista4) == primero);
		comprueba_ultimo2 &= (lista_ver_ultimo(lista4) == puntero);
		comprueba_largo2 &= (lista_largo(lista4)==largo_inicial+j+1);
	}

	// Verifico que que la prueba se realizo correctamente
	print_test("Se insertaron todos los elementos correctamente ", inserto_bien2);
	print_test("El primero por cada iteracion fue el correcto", comprueba_primero2);
	print_test("El ultimo por cada iteracion fue el correcto", comprueba_ultimo2);
	print_test("El largo de la lista por cada iteracion fue correcto", comprueba_largo2);
	print_test("Comprueba que la lista no esta vacia", !lista_esta_vacia(lista4));

	//Elimino todos los elementos
	bool comprueba_ultimo3 = true;
	bool comprueba_largo3 = true;
	bool elimino_bien = true;
	size_t largo=lista_largo(lista4);
	size_t contador = 1;
	void* ultimo = lista_ver_ultimo(lista4);
	while (lista_esta_vacia(lista4) == false){
		comprueba_ultimo3 &= (lista_ver_ultimo(lista4) == ultimo);
		elimino_bien &= (lista_ver_primero(lista4) == lista_borrar_primero(lista4));
		comprueba_largo3 &= (lista_largo(lista4) == largo - contador);
		contador++;
	}
	// Verifico que la prueba se realizo correctamente
	print_test("Se eliminaron todos los elementos correctamente", elimino_bien);
	print_test("El ultimo por cada iteracion fue el correcto", comprueba_ultimo3);
	print_test("El largo de la lista por cada iteracion fue correcto", comprueba_largo3);
	print_test("Compruebo que no hay primero", lista_ver_primero(lista4)==NULL);
	print_test("Compruebo que no hay ultimo", lista_ver_ultimo(lista4)==NULL);
	print_test("El largo de la lista es 0",lista_largo(lista4)==0);
	print_test("La lista esta vacia",lista_esta_vacia(lista4));

	//Destruyo la lista
	lista_destruir(lista4,NULL);
}

void prueba_destruir(){
	printf("~~INICIO DE DESTRUIR PASANDO PUNTERO A FUNCION~~\n");

	// Creo lista
	lista_t* lista5 = lista_crear();

	//Verifico si la lista fue creada
	print_test("La lista fue creada", lista5 != NULL);

	// Declaro elementos a insertar
	int v1 = 200;
	float v2 = 1220.5;

	//Inserto v1 y compruebo que las condiciones de la lista son correctas
	print_test("Inserto en el primer lugar un puntero a v1", lista_insertar_primero(lista5,&v1));
	print_test("Observo cual es el primero, debe ser v1", lista_ver_primero(lista5) == &v1);
	print_test("Observo cual es el ultimo debe ser v1", lista_ver_ultimo(lista5) == &v1);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista5));
	print_test("Compruebo el largo de la lista, debe ser 1", lista_largo(lista5)==1);

	//Inserto v2 y compruebo que las condiciones de la lista son correctas
	print_test("Inserto en el primer lugar un puntero a v2", lista_insertar_primero(lista5,&v2));
	print_test("Observo cual es el primero, debe ser v2", lista_ver_primero(lista5) == &v2);
	print_test("Observo cual es el ultimo debe ser v1", lista_ver_ultimo(lista5) == &v1);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista5));
	print_test("Compruebo el largo de la lista, debe ser 2", lista_largo(lista5)==2);

	//Destruyo la lista
	lista_destruir(lista5,NULL);

	// Creo otra lista
	lista_t* lista6 = lista_crear();

	//Verifico si la lista fue creada
	print_test("La lista fue creada", lista6 != NULL);

	// Declaro elementos a insertar
	int* puntero1 = malloc(100*sizeof(int));
	float* puntero2 = malloc(50*sizeof(float));

	//Inserto puntero1 y compruebo que las condiciones de la lista son correctas
	print_test("Inserto en el primer lugar el puntero1", lista_insertar_primero(lista6,puntero1));
	print_test("Observo cual es el primero, debe ser puntero1", lista_ver_primero(lista6) == puntero1);
	print_test("Observo cual es el ultimo debe ser puntero1", lista_ver_ultimo(lista6) == puntero1);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista6));
	print_test("Compruebo el largo de la lista, debe ser 1", lista_largo(lista6)==1);

	//Inserto puntero2 y compruebo que las condiciones de la lista son correctas
	print_test("Inserto en el primer lugar el puntero2", lista_insertar_primero(lista6,puntero2));
	print_test("Observo cual es el primero, debe ser puntero2", lista_ver_primero(lista6) == puntero2);
	print_test("Observo cual es el ultimo debe ser puntero2", lista_ver_ultimo(lista6) == puntero1);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista6));
	print_test("Compruebo el largo de la lista, debe ser 2", lista_largo(lista6)==2);

	//Destruyo la lista pasando una funcion
	lista_destruir(lista6,*free);

	// Creo lista
	lista_t* lista7 = lista_crear();

	//Verifico si la lista fue creada
	print_test("La lista fue creada", lista5 != NULL);

	//Destruyo la lista vacia pasando NULL
	lista_destruir(lista7,NULL);
	print_test("La lista vacia fue destruida correctamente pasando puntero NULL", true);

	// Creo lista
	lista_t* lista8 = lista_crear();

	//Verifico si la lista fue creada
	print_test("La lista fue creada", lista5 != NULL);

	//Destruyo la lista vacia pasando una funcion
	lista_destruir(lista8,*free);
	print_test("La lista vacia fue destruida correctamente pasando una funcion", true);
}

void prueba_iterador_interno(){
	printf("~~INICIO DE PRUEBAS DEL ITERADOR INTERNO~~\n");
	// Creo lista
	lista_t* lista7 = lista_crear();

	//Verifico si la lista fue creada
	print_test("La lista fue creada", lista7 != NULL);

	//Inserto varios elemenos
	int v1 [] = {1,20,30,77,90};
	lista_insertar_primero(lista7,&v1[2]);
	lista_insertar_ultimo(lista7,&v1[3]);
	lista_insertar_primero(lista7,&v1[1]);
	lista_insertar_ultimo(lista7,&v1[4]);
	lista_insertar_primero(lista7,&v1[0]);

	//Declaro las funciones a iterar
	bool verifica_dato_sin_corte(void* dato, void* extra){
		printf("El numero en esta posicion es: %d. ", *(int*) dato);
		print_test("Coincide con el valor esperado", *(int*) dato == v1[*(int*)extra]);
		*(int*)extra += 1;
		return true;
	}

	bool verifica_dato_con_corte(void* dato, void* extra){
		if (*(int*)extra > 2) return false;
		printf("El numero en esta posicion es: %d. ", *(int*) dato);
		print_test("Coincide con el valor esperado", *(int*) dato == v1[*(int*)extra]);
		*(int*)extra += 1;
		return true;
	}

	bool imprimir_dato(void* dato, void* extra){
		printf("El numero en esta posicion es: %d. \n", *(int*) dato);
		return true;
	}

	//Uso iterador interno sin corte corte
	printf("~~PRUEBO ITERADOR INTERNO SIN CORTE~~\n");
	int contador1=0;
	lista_iterar(lista7,verifica_dato_sin_corte, &contador1);

	//Uso iterador interno con corte corte
	printf("~~PRUEBO ITERADOR INTERNO CON CORTE~~\n");
	int contador2=0;
	lista_iterar(lista7,verifica_dato_con_corte, &contador2);

	//Uso iterador interno pasando NULL como extra y sin corte
	printf("~~PRUEBO ITERADOR INTERNO PASANDO NULL~~\n");
	lista_iterar(lista7,imprimir_dato, NULL);

	//Destruyo la lista pasando NULL
	lista_destruir(lista7,NULL);
}

void prueba_iterador_externo(){
	printf("~~INICIO DE PRUEBAS DEL ITERADOR EXTERNO VACIO~~\n");
	// Creo lista
	lista_t* lista8 = lista_crear();

	//Verifico si la lista fue creada
	print_test("La lista fue creada", lista8 != NULL);

	//Creo iterador con lista vacia y verifico que lascondiciones son correctas
	lista_iter_t* iter1 = lista_iter_crear(lista8);
	print_test("El iterador de creado", iter1 != NULL);

	// Compruebo que no puedo ver dato actual
	print_test("No hay dato actual, ya que la lista esta vacia", lista_iter_ver_actual(iter1) == NULL);

	// Compruebo que estoy al final
	print_test("Compruebo que estoy al final, ya que esta vacia", lista_iter_al_final(iter1));

	//Compruebo que no puedo seguir avanzando
	print_test("Compruebo que no puedo avanzar ya que estoy al final", !lista_iter_avanzar(iter1));

	//Destruyo el iterador
	lista_iter_destruir(iter1);

	//Inserto varios elemenos
	printf("INICIO DE PRUEBAS DEL ITERADOR EXTERNO CON ELEMENTOS\n");
	int v1 [] = {1,3,5,7};
	lista_insertar_primero(lista8,&v1[1]);
	lista_insertar_ultimo(lista8,&v1[2]);
	lista_insertar_primero(lista8,&v1[0]);
	lista_insertar_ultimo(lista8,&v1[3]);

	//Creo iterador externo
	lista_iter_t* iter2 = lista_iter_crear(lista8);
	print_test("El iterador fue creado", iter2 != NULL);

	// Observo que estoy en la primer posicion
	print_test("El dato actual es 1", lista_iter_ver_actual(iter2) == &v1[0]);
	print_test("Compruebo que no estoy al final", !lista_iter_al_final(iter2));

	//Avanzo a la siguiente posicion y compruebo las condiciones
	print_test("Compruebo que puedo seguir avanzando", lista_iter_avanzar(iter2));
	print_test("El dato actual es 3", lista_iter_ver_actual(iter2) == &v1[1]);
	print_test("Compruebo que no estoy al final", !lista_iter_al_final(iter2));

	//Avanzo a la siguiente posicion y compruebo las condiciones
	print_test("Compruebo que puedo seguir avanzando", lista_iter_avanzar(iter2));
	print_test("Compruebo que no estoy al final", !lista_iter_al_final(iter2));
	print_test("El dato actual es 5", lista_iter_ver_actual(iter2) == &v1[2]);


	//Avanzo a la siguiente posicion y compruebo las condiciones
	print_test("Compruebo que puedo seguir avanzando", lista_iter_avanzar(iter2));
	print_test("Compruebo que no estoy al final", !lista_iter_al_final(iter2));
	print_test("El dato actual es 7", lista_iter_ver_actual(iter2) == &v1[3]);


	//Avanzo a la siguiente posicion y compruebo las condiciones
	print_test("Compruebo que puedo seguir avanzando", lista_iter_avanzar(iter2));
	print_test("Compruebo que estoy  al final", lista_iter_al_final(iter2));
	print_test("No existe dato actual", lista_iter_ver_actual(iter2) == NULL);
	print_test("Compruebo que no puedo seguir avanzando", !lista_iter_avanzar(iter2));

	//Destruyo el iterador
	lista_iter_destruir(iter2);

	//Destruyo la lista pasando NULL
	lista_destruir(lista8,NULL);
}

void prueba_iterador_externo_insertar(){
	printf("~~INICIO DE PRUEBAS DE INSERCION CON ITERADOR EXTERNO ~~\n");
	// Creo lista
	lista_t* lista9 = lista_crear();

	//Verifico si la lista fue creada
	print_test("La lista fue creada", lista9 != NULL);

	//Creo iterador con lista vacia y verifico que lascondiciones son correctas
	lista_iter_t* iter1 = lista_iter_crear(lista9);
	print_test("El iterador de creado", iter1 != NULL);

	//Inserto un elemento y compruebo que las condiciones sean correctas
	int v1 = 1;
	print_test("Inserto en el primer lugar v1", lista_iter_insertar(iter1,&v1));
	print_test("Observo cual es el primero, debe ser v1", lista_ver_primero(lista9) == &v1);
	print_test("Observo cual es el ultimo debe ser  v1", lista_ver_ultimo(lista9) == &v1);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista9));
	print_test("Compruebo el largo de la lista, debe ser 1", lista_largo(lista9)==1);
	print_test("Compruebo que que el dato actual es v1", lista_iter_ver_actual(iter1) == &v1);
	print_test("Compruebo que no estoy al final", !lista_iter_al_final(iter1));

	// Avanzo a la siguiente posicion
	int v2 = 30;
	print_test("Compruebo que puedo seguir avanzando", lista_iter_avanzar(iter1));
	print_test("Compruebo que estoy al final", lista_iter_al_final(iter1));
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista9));
	print_test("Inserto en el ultimo lugar a v2", lista_iter_insertar(iter1,&v2));
	print_test("Observo cual es el primero, debe ser v1", lista_ver_primero(lista9) == &v1);
	print_test("Observo cual es el ultimo debe ser  v2", lista_ver_ultimo(lista9) == &v2);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista9));
	print_test("Compruebo el largo de la lista, debe ser 2", lista_largo(lista9)==2);
	print_test("Compruebo que que el dato actual es v2", lista_iter_ver_actual(iter1) == &v2);
	print_test("Compruebo que no estoy al final", !lista_iter_al_final(iter1));

	//Destruyo el iterador
	lista_iter_destruir(iter1);
	print_test("Destruyo el iterador externo", true);
 	print_test("Observo cual es el primero, debe ser v1", lista_ver_primero(lista9) == &v1);
	print_test("Observo cual es el ultimo debe ser  v2", lista_ver_ultimo(lista9) == &v2);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista9));
	print_test("Compruebo el largo de la lista, debe ser 2", lista_largo(lista9)==2);

	//Inserto nuevos elementos sin usar iterador
	int v0 = 0;
	int v3 = 360;
	print_test("Inserto en el primer lugar el v0", lista_insertar_primero(lista9,&v0));
	print_test("Observo cual es el primero, debe ser v0", lista_ver_primero(lista9) == &v0);
	print_test("Observo cual es el ultimo debe ser v2", lista_ver_ultimo(lista9) == &v2);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista9));
	print_test("Compruebo el largo de la lista, debe ser 3", lista_largo(lista9)==3);
	print_test("Inserto en el ultimo lugar el v3", lista_insertar_ultimo(lista9,&v3));
	print_test("Observo cual es el primero, debe ser v0", lista_ver_primero(lista9) == &v0);
	print_test("Observo cual es el ultimo debe ser v3", lista_ver_ultimo(lista9) == &v3);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista9));
	print_test("Compruebo el largo de la lista, debe ser 4", lista_largo(lista9)==4);

	//Creo otro iterador
	lista_iter_t* iter2 = lista_iter_crear(lista9);
	print_test("El iterador de creado", iter2 != NULL);

	//Compruebo que estoy en la primera posicion
	print_test("El dato actual es v0", lista_iter_ver_actual(iter2) == &v0);
	print_test("Compruebo que no estoy al final", !lista_iter_al_final(iter2));

	//Inserto en la primera posicion
	int v4= 10;
	print_test("Inserto en el primer lugar v4", lista_iter_insertar(iter2,&v4));
	print_test("Observo cual es el primero, debe ser v4", lista_ver_primero(lista9) == &v4);
	print_test("Observo cual es el ultimo debe ser  v3", lista_ver_ultimo(lista9) == &v3);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista9));
	print_test("Compruebo el largo de la lista, debe ser 5", lista_largo(lista9)==5);
	print_test("Compruebo que que el dato actual es v4", lista_iter_ver_actual(iter2) == &v4);
	print_test("Compruebo que no estoy al final", !lista_iter_al_final(iter2));

	//Avanzo
	print_test("Compruebo que puedo seguir avanzando", lista_iter_avanzar(iter2));
	print_test("El dato actual es v0", lista_iter_ver_actual(iter2) == &v0);
	print_test("Compruebo que no estoy al final", !lista_iter_al_final(iter2));
	print_test("Compruebo que puedo seguir avanzando", lista_iter_avanzar(iter2));
	print_test("El dato actual es v1", lista_iter_ver_actual(iter2) == &v1);
	print_test("Compruebo que no estoy al final", !lista_iter_al_final(iter2));
	print_test("Compruebo que puedo seguir avanzando", lista_iter_avanzar(iter2));
	print_test("El dato actual es v2", lista_iter_ver_actual(iter2) == &v2);
	print_test("Compruebo que no estoy al final", !lista_iter_al_final(iter2));

	//Inserto en el medio
	int v5 = 100;
	print_test("Inserto en el medio a v5", lista_iter_insertar(iter2,&v5));
	print_test("Observo cual es el primero, debe ser v4", lista_ver_primero(lista9) == &v4);
	print_test("Observo cual es el ultimo debe ser  v3", lista_ver_ultimo(lista9) == &v3);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista9));
	print_test("Compruebo el largo de la lista, debe ser 6", lista_largo(lista9)==6);
	print_test("Compruebo que que el dato actual es v5", lista_iter_ver_actual(iter2) == &v5);
	print_test("Compruebo que no estoy al final", !lista_iter_al_final(iter2));

	//Avanzo
	print_test("Compruebo que puedo seguir avanzando", lista_iter_avanzar(iter2));
	print_test("El dato actual es v2", lista_iter_ver_actual(iter2) == &v2);
	print_test("Compruebo que no estoy al final", !lista_iter_al_final(iter2));
	print_test("Compruebo que puedo seguir avanzando", lista_iter_avanzar(iter2));
	print_test("El dato actual es v3", lista_iter_ver_actual(iter2) == &v3);
	print_test("Compruebo que no estoy al final", !lista_iter_al_final(iter2));
	print_test("Compruebo que puedo seguir avanzando", lista_iter_avanzar(iter2));
	print_test("Compruebo que estoy al final", lista_iter_al_final(iter2));
	print_test("Compruebo que no hay dato actual", lista_iter_ver_actual(iter2) == NULL);

	//Inserto en la ultima posicion
	int v6 = 420;
	print_test("Inserto en la ultima posicion a v6", lista_iter_insertar(iter2,&v6));
	print_test("Observo cual es el primero, debe ser v4", lista_ver_primero(lista9) == &v4);
	print_test("Observo cual es el ultimo debe ser  v6", lista_ver_ultimo(lista9) == &v6);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista9));
	print_test("Compruebo el largo de la lista, debe ser 7", lista_largo(lista9)==7);
	print_test("Compruebo que que el dato actual es v6", lista_iter_ver_actual(iter2) == &v6);
	print_test("Compruebo que no estoy al final", !lista_iter_al_final(iter2));
	print_test("Compruebo que puedo seguir avanzando", lista_iter_avanzar(iter2));
	print_test("Compruebo que estoy al final", lista_iter_al_final(iter2));
	print_test("Compruebo que no hay dato actual", lista_iter_ver_actual(iter2) == NULL);

	//Destruyo el iterador
	lista_iter_destruir(iter2);

	//Destruyo la lista pasando NULL
	lista_destruir(lista9,NULL);
}

void prueba_iterador_externo_borrar(){
	printf("~~INICIO DE PRUEBAS DE ELIMINACION con ITERADOR EXTERNO ~~\n");
	// Creo lista
	lista_t* lista10 = lista_crear();

	//Verifico si la lista fue creada
	print_test("La lista fue creada", lista10 != NULL);

	//Creo un iterador y compruebo que no puedo eliminar ya que esta vacia
	lista_iter_t* iter1 = lista_iter_crear(lista10);
	print_test("El iterador de creado", iter1 != NULL);
	print_test("No hay dato actual, ya que la lista esta vacia", lista_iter_ver_actual(iter1) == NULL);
	print_test("Compruebo que estoy al final, ya que esta vacia", lista_iter_al_final(iter1));
	print_test("Compruebo que no puedo avanzar ya que estoy al final", !lista_iter_avanzar(iter1));
	print_test("Compruebo que no puedo eliminar datos ya que la lista esta vacia", lista_iter_borrar(iter1)==NULL);

	//Inserto un unico elemento y lo borro
	int n1 = 10;
	print_test("Inserto en el primer lugar a n1", lista_iter_insertar(iter1,&n1));
	print_test("Observo cual es el primero, debe ser n1", lista_ver_primero(lista10) == &n1);
	print_test("Observo cual es el ultimo debe ser  n1", lista_ver_ultimo(lista10) == &n1);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista10));
	print_test("Compruebo el largo de la lista, debe ser 1", lista_largo(lista10)==1);
	print_test("Compruebo que que el dato actual es n1", lista_iter_ver_actual(iter1) == &n1);
	print_test("Compruebo que no estoy al final", !lista_iter_al_final(iter1));
	print_test("Elimino el valor en esta posicion ", lista_iter_borrar(iter1) == &n1);
	print_test("Observo que no hay primero", lista_ver_primero(lista10) == NULL);
	print_test("Observo que no hay ultimo", lista_ver_ultimo(lista10) == NULL);
	print_test("Compruebo el largo de la lista, debe ser 0", lista_largo(lista10)==0);
	print_test("Compruebo que no hay dato actual", lista_iter_ver_actual(iter1) == NULL);
	print_test("Compruebo que la lista esta vacia", lista_esta_vacia(lista10));
	print_test("Compruebo que estoy al final", lista_iter_al_final(iter1));

	//Destruyo el iterador
	lista_iter_destruir(iter1);
	print_test("Elimino este iterador", true);

	//Agrego elementos a la lista
	int v1 [] = {0,1,420,2,3};
	lista_insertar_primero(lista10,&v1[1]);
	lista_insertar_ultimo(lista10,&v1[2]);
	lista_insertar_primero(lista10,&v1[0]);
	lista_insertar_ultimo(lista10,&v1[3]);
	lista_insertar_ultimo(lista10,&v1[4]);

	//Creo iterador
	lista_iter_t* iter2 = lista_iter_crear(lista10);
	print_test("El iterador de creado", iter2 != NULL);

	//Compruebo que estoy en la primera posicion y elimino este dato
	print_test("El dato actual es la primera posicion de v1", lista_iter_ver_actual(iter2) == &v1[0]);
	print_test("Compruebo que no estoy al final", !lista_iter_al_final(iter2));
	print_test("Observo cual es el primero", lista_ver_primero(lista10) == &v1[0]);
	print_test("Observo cual es el ultimo", lista_ver_ultimo(lista10) == &v1[4]);
	print_test("Compruebo el largo de la lista, debe ser 5", lista_largo(lista10)==5);
	print_test("Elimino el valor en la primer posicion de v1", lista_iter_borrar(iter2) == &v1[0]);
	print_test("Observo cual es el primero, debe ser la segunda posicion de v1", lista_ver_primero(lista10) == &v1[1]);
	print_test("Observo cual es el ultimo", lista_ver_ultimo(lista10) == &v1[4]);
	print_test("Compruebo el largo de la lista, debe ser 4", lista_largo(lista10)==4);
	print_test("Compruebo que que el dato actual es la segunda posicion de v1", lista_iter_ver_actual(iter2) == &v1[1]);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista10));
	print_test("Compruebo que no estoy al final", !lista_iter_al_final(iter2));

	//Avanzo en la lista y elimino este dato
	print_test("Compruebo que puedo seguir avanzando", lista_iter_avanzar(iter2));
	print_test("El dato actual es la tercer posicion de v1", lista_iter_ver_actual(iter2) == &v1[2]);
	print_test("Compruebo que no estoy al final", !lista_iter_al_final(iter2));
	print_test("Elimino el valor en esta posicion de v1", lista_iter_borrar(iter2) == &v1[2]);
	print_test("Observo cual es el primero", lista_ver_primero(lista10) == &v1[1]);
	print_test("Observo cual es el ultimo", lista_ver_ultimo(lista10) == &v1[4]);
	print_test("Compruebo el largo de la lista, debe ser 3", lista_largo(lista10)==3);
	print_test("Compruebo que el dato actual", lista_iter_ver_actual(iter2) == &v1[3]);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista10));
	print_test("Compruebo que no estoy al final", !lista_iter_al_final(iter2));

	//Avanzo en la lista y elimino este dato
	print_test("Elimino el valor en esta posicion de v1", lista_iter_borrar(iter2) == &v1[3]);
	print_test("Observo cual es el primero", lista_ver_primero(lista10) == &v1[1]);
	print_test("Observo cual es el ultimo", lista_ver_ultimo(lista10) == &v1[4]);
	print_test("Compruebo el largo de la lista, debe ser 2", lista_largo(lista10)==2);
	print_test("Compruebo que que el dato actual", lista_iter_ver_actual(iter2) == &v1[4]);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista10));
	print_test("Compruebo que no estoy al final", !lista_iter_al_final(iter2));

	//Elimino el el dato en la ultima posicion
	print_test("Elimino el valor en esta posicion de v1", lista_iter_borrar(iter2) == &v1[4]);
	print_test("Observo cual es el primero", lista_ver_primero(lista10) == &v1[1]);
	print_test("Observo cual es el ultimo", lista_ver_ultimo(lista10) == &v1[1]);
	print_test("Compruebo el largo de la lista, debe ser 1", lista_largo(lista10)==1);
	print_test("Compruebo que el dato actual", lista_iter_ver_actual(iter2) == NULL);
	print_test("Compruebo que la lista no esta vacia", !lista_esta_vacia(lista10));
	print_test("Compruebo que estoy al final", lista_iter_al_final(iter2));
	print_test("Compruebo que no puedo eliminar porque estoy al final", lista_iter_borrar(iter2) == NULL);

	//Destruyo el iterador
	lista_iter_destruir(iter2);

	//Destruyo la lista pasando NULL
	lista_destruir(lista10,NULL);
}

void pruebas_lista_alumno() {
	prueba_lista_vacia();
	prueba_enlisto_desenlisto();
	prueba_insertar_primero();
	prueba_volumen();
	prueba_destruir();
	prueba_iterador_interno();
	prueba_iterador_externo();
	prueba_iterador_externo_insertar();
	prueba_iterador_externo_borrar();
}
