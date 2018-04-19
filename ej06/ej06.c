#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "utiles.h"

#define MAX 20
#define BIN "/bin/"
#define PIPE "|"
#define XOR "||"
#define AND "&&" 

int main(){
    int resultado_ejecucion;
    int cantidad_tokens;
    int status, cant_args=0;

    char comando[MAX]= BIN;
    char entrada[MAX];
    char *tokens[MAX];

    printf (">>>>> ");scanf("%[^\n]", &entrada);    
    cantidad_tokens = parsear_comando(entrada, tokens);
    /*todo comando: solo 1 argumento por simplicidad*/
        
    strcat(comando, tokens[0]);//a la cadena /bin/ le agrega un programa al final
    if(cantidad_tokens>2){
        if(!(strcmp(tokens[2], PIPE))){     //compara el tercer token con |
            printf("es pipe");
        }
        if(!(strcmp(tokens[2], XOR))){      //compara el tercer token con doble ||
            printf("es ||");
        }
        if(!(strcmp(tokens[2], AND))){      //compara el tercer token con &&
            printf("es &&");
        }
            // else{printf("no es pipe");}
    }else{
        if(fork() != 0){
            waitpid(-1, &status,0);
        }else{
            resultado_ejecucion = execl(comando,comando,NULL );
            if(resultado_ejecucion){
                printf("no es un comando valido");
            }
        }
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
es comando invalido  0
comando comun 1
con pipe 2 
con && 3 
o con || 4
*/
