#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *substr(const char *str, size_t n){
    //Le agrego uno mas asi puedo poner el fin de cadena
    size_t largo_str = strlen(str);
    char *buffer;
    if (n > largo_str){
        n = largo_str;
    }
    buffer = malloc(sizeof(char*) * n + 1);
    if(!buffer) return NULL;
    for (size_t i = 0; i < n; i++){
        buffer[i] = str[i];
    }
    buffer[n] = '\0';


    return buffer;
}

char **split(const char *str, char sep){
    size_t largo_str = strlen(str);
    size_t cant_separador = 0;
    //Cuento la cantidad de veces que aparece el caracter separador
    for (size_t i = 0; i < largo_str; i++)
    {
        if(*(str + i) == sep){
            cant_separador++;
        }
    }
    //Voy a necesitar dos posiciones mas en el array, una para una cadena mas y otra para el NULL
    size_t largo_arr = (cant_separador + 2);
    char **arr = malloc(sizeof(char*) * largo_arr);
    //Alojo memoria para cada cadena dinamica con un largo del largo del string ingresado como maximo
    for (size_t i = 0; i < largo_arr - 1; i++)
    {
        //Para evitar hacer calloc con 0 bytes, que no tendria sentido
        if(largo_str == 0){
            largo_str = 1;
        }
        arr[i] = calloc(sizeof(char*) , (largo_str));
    }
    
    if(!arr) return NULL;
    int cont_ocurrencias = 0;
    size_t j = 0;//Inicializo un indice para recorrer cada cadena dinamica correctamente
    for (size_t i = 0; i < largo_str; i++)
    {
        if(*(str + i) != sep){
            //Si el caracter no es un separador, lo agrego
            arr[cont_ocurrencias][j]  = *(str + i);
            j++;
        } else {
            //Si es un separador significa que termine la palabra, entonces
            //Asigno fin de cadena
            arr[cont_ocurrencias][j] = '\0';
            //Aumento las ocurrencias para escribir otra palabra
            cont_ocurrencias++;
            //Reinicio el contador para recorrer la cadena dinamica correctamente
            j = 0;
        }
    }
    //Asigno NULL al ultimo elemento
    arr[largo_arr - 1] = NULL;
    return arr;
    // El mayor for es hasta el largo del string, entonces la primitiva tiene complejidad o(n)
}


char *join(char **strv, char sep){
    // if(strv == NULL){
    //     char *bufer = calloc(sizeof(char*),1);
    //     bufer[0] = '\0';
    //     return bufer;
    // }
    size_t largo_tot = 0;
    for (size_t i = 0; strv[i] != NULL; i++)
    {
        largo_tot += strlen(strv[i]);
        largo_tot++;//A cada iteracion le sumo uno mas por el separador que voy a tener, y uno mas al final por el fin de cadena
    }
    if(strv[0] == NULL) largo_tot = 1;
    char *bufer = calloc(sizeof(char*), largo_tot);

    size_t contador = 0;
    //Recorro cada elemento del array
    for (size_t i = 0; strv[i] != NULL; i++){
        size_t largo = strlen(strv[i]);
        //Calculo el largo para saber hasta donde recorrer por cada elemento
        for (size_t j = 0; j < largo; j++){
            //Recorro y voy copiando en el bufer
            bufer[contador] = strv[i][j];
            contador++;
        }
        //Cuando salgo del for significa que tengo que concatenar el separador que quiero poner
        //Si el contador esta al final del bufer significa que tengo que poner un fin de linea y no un separador
        if(contador == largo_tot - 1){
            bufer[contador] = '\0';
        } else{
            //Si el separador es el fin de cadena, en el medio no lo tengo que copiar porque me cortaria la cadena cuando la tiene que unir
            if(sep != '\0'){
                bufer[contador] = sep;
                contador++;
            }
        }
        
    }
    if(strv == NULL) bufer[0] = '\0';
    return bufer;
    
}

void free_strv(char *strv[]){
    for (size_t i = 0; strv[i] != NULL; i++)
    {
        free(strv[i]);
    }
    free(strv);
}

//  int main(){  
//      /*char **arr = split("abc,def", ',');
//      for (size_t i = 0; arr[i] != NULL; i++)
//      {
//          printf("%zu %s\n",i, arr[i]);
//      }*/
//      //char *resul = join(NULL, ',');
//      char *resul = substr("hola", 2);
//      printf("%s\n", resul);
//      free(resul);
//      //printf("LARGO RESUL: %zu\n", strlen(resul));
//      //printf("Resultado:%s\n", resul);
//      //free_strv(arr);
//      //free(resul);  
//      return 0;
//  }