
#include<stdio.h>
#include<conio.h>
int main(){
    void ordsel(int * x, int n){
    int minimo=0,i,j;
    int swap;
    for(i=0 ; i<n-1 ; i++){
        minimo=i;
        for(j=i+1 ; j<n ; j++)
            if (x[minimo] > x[j])
            minimo=j;
        swap=x[minimo];
        x[minimo]=x[i];
        x[i]=swap;
    }
  }
}
