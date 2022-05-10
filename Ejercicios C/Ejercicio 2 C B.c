#include<stdio.h>
int main(){
    int entero,factorial;
    printf("El programa permite calcular el factorial de un numero dado.\n");
    printf("Ingrese un entero: \n")
    scanf("%d",&entero);
    int factorial(int n) {
        if(n < 0) return 0;
        else if(n > 1) return n*factorial(n-1);
        return 1;
        }
}
