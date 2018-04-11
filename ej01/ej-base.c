#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int cant = 0;
typedef void (*ptr)();
void manejador(int);

int main(void){
    signal(2,(ptr)manejador); //(ptr)
    while(1);
}

void manejador(int num){
    printf("Recibi senial");
    cant++;
    if(cant==3){
        printf("finalizo mi ejecucion");
        exit(1);
    }
}