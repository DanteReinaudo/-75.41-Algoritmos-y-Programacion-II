#include<stdio.h>
#include <string.h>
int main(){
    char vector[]="viva peron";
    unsigned int  longitud;
    longitud = strlen(vector);
    printf("La longitud es %d", longitud);
    unsigned int my_strlen(char *p){
        unsigned int count = 0;
        while(*p!='\0'){
        count++;
        p++;
        }
        return count;
        }
    return 0;
    }
