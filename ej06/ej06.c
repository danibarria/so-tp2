#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "utiles.h"

#define MAX 20
#define BIN "/bin/"

int parsear_comando(char* cadena, char* arg[]);

int main(){
    int resultado_ejecucion;
    int cantidad_tokens;
    int status, cant_args=0;

    char comando[MAX]= BIN;
    char entrada[MAX];
    char *tokens[MAX];

    while(1){//por siempre hacer
        printf (">>>>> ");scanf("%[^\n]", &entrada);
        
        cantidad_tokens = parsear_comando(entrada, tokens);
        
        if(fork() != 0){
            waitpid(-1, &status,0);
                    // scanf("%s",&entrada);
        }else{
            /*aca ejecutar*/
            strcat(comando, tokens[0]);
            resultado_ejecucion = execl(comando,comando,NULL );
                    // scanf("%s",&entrada);
            if(resultado_ejecucion){
                printf("no es un comando valido");
            }
        }
        scanf("%d",&status);
    }
    return 0;
}

/***
 * 06. Desarrolle su propia terminal (un shell) que implemente las siguientes funcionalidades:
a. Ejecutar procesos con sus argumentos.
b. Permitir conectar la salida estándar de un proceso con la entrada estándar de otro
(ej: ps | grep “bash”).
c. Ejecutar condicionalmente un proceso dependiendo de la finalización de otro
(ej: grep “cadena” archivo && ls).
Nota: ​ Para resolver el ejercicio debe investigar las llamadas al sistema fork, exec, dup, pipe,
entre otras.


ver si es un 
es comando invalido
comando comun
con pipe
con && 
o con ||




*/

int esComando(){
    /***
     * si es comando devuelve 0, sino otro numero
     * 
     * */
}