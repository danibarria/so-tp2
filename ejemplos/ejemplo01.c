#include <stdio.h>
#include <signal.h>

int mi_manejador(int);


int main(){
    signal(SIGINT, (__sighandler_t)mi_manejador);
    
    while(1);
}

int mi_manejador(int nro){
    printf("Hola, recibi sigint");
    return 0;
}