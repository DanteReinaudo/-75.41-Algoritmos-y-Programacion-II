#include <stdio.h>

int main()
{
    int numeroSecreto=9;
    int respuesta,limite=0;
    while(numeroSecreto != respuesta && limite<3){
        printf("Ingrese un numero: ");
        scanf("%d",&respuesta);
        limite++;
    }
    if (numeroSecreto == respuesta){
        printf("Has adivinado");
    }else{
        printf("Jaja perdiste");
    }
    return 0;
}
