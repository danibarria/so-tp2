#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "utiles.h"

#define MAX 15

int parsear_comando(char* cadena, char* arg[]);

int main(){
    int status, cant_args=0;
    char args[MAX];
    char *tokens[MAX];

    // while(1){//por siempre hacer
        printf ("> ");
	    scanf("%[^\n]", &args);
        
        /*aca parsear*/
        // parsear_comando(char* cadena, char* arg[])
        parsear_comando(args, tokens);
        /**/
        // printf("%d",cant_args);
        // if(fork() != 0){
            // waitpid(-1, &status,0);
        // }else{
            /*aca ejecutar*/
            // execv("/bin/bash", NULL);
        // }
    // }

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


ver si es un comando


*/
