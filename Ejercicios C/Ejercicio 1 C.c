#include <stdio.h>
int main(){
    int base,altura,area;
    printf("Este programa permite calcular el area de un rectangulo.\n");
    printf("Ingrese la base del rectangulo:\n");
    scanf("%d",&base);
    printf("Ingrese la altura del rectangulo:\n");
    scanf("%d",&altura);
    area=base*altura;
    printf("El area del rectangulo es %d",area);
    return 0;
}
