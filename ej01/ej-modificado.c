#include <stdio.h>
#include <signal.h>
// #include <unistd.h>
// #include <stdlib.h>

typedef void (*funcPtr)();

void manejador(int *c){
    printf("Recibi senial\n");
}

int main(){
    signal(SIGINT,(funcPtr)manejador); //(ptr)
    while(1);
    return 0;
}

