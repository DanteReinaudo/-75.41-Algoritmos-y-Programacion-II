#include<stdio.h>
int main(){
    int i,entero,factorial=1;
    printf("Ingrese un numero entero, y el programa calculara su factorial.\n");
    scanf("%d",&entero);
    if (entero<0) factorial=0;
    else if (entero==0) factorial=1;
    else{
        for (i=1; i<= entero ;i++){
            factorial=factorial*i;
            }
        }
    printf("El factorial de %d es %d", entero, factorial);
    return 0;
}
