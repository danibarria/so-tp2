#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define TIEMPO 15

int contador = TIEMPO;

void sigalrm_handler(int);
void sigint_handler(int);

int main(void){
    signal(SIGALRM, sigalrm_handler);
    signal(SIGINT,sigint_handler);
    alarm(1);
    while(1);
    // return 0;
}

void sigint_handler(int sig){
    //resetea tiempo
    contador = TIEMPO;
    printf("SIGINT recibido.\n");
}
void sigalrm_handler(int sig)
{   
    //cuenta hacia atras y termina en 0
    if(contador--){
        printf("contador: %d\n", contador);
        alarm(1);
    }else{
        printf("Fin.\n");
        raise(SIGTERM);
        // contador = TIEMPO;
    }
}

