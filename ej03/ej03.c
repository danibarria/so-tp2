#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define TIEMPO 30
#define FIN 19

int contador = TIEMPO;


void sigalrm_handler(int);

int main(void){
    signal(SIGALRM, sigalrm_handler);
    alarm(1);
    while(1);
    return 0;
}

void sigalrm_handler(int sig)
{   
    //cuenta hacia atras y termina
    if(contador--){
        printf("contador: %d\n", contador);
        alarm(1);
    }
    if(contador==FIN+1){
        signal(SIGALRM,SIG_IGN);//forma 1
    }   
    if(contador==FIN){
        alarm(0);               //forma2
    }
    // RTA : el resultado obtenido es el mismo
}