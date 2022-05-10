#include<stdio.h>
int main(){
    int i,cantidad,suma=0;
    float promedio;
    printf("Ingrese una lista de numeros, la cantidad y el programa calcula el promedio.\n");
    printf("Ingrese la cantidad de numeros que va a ingresar:\n");
    scanf("%d",&cantidad);
    int vector[cantidad];
    for(i=0; i<cantidad; i++){
      printf("Introduce el numero %d:", i+1);
      scanf("%d", &vector[i]);
      suma=suma+vector[i];
      }
      printf("%d %d",suma,cantidad);
    promedio=suma/cantidad;
    printf("El promedio es %f",promedio);
    return 0;
}
