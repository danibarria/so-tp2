#include <stdio.h>
#include <signal.h>

typedef void (*funcPtr)();

int salir=0;    /* Falso */

void controlador( int *lista_Registros )
{
    static int contador = 0;
    contador++;
    printf( "SIGINT capturado. veces : %d\n",contador );
}

int main()
{
    signal( SIGINT, (funcPtr)controlador );
    while(1);
   return 0;
}