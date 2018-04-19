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
    int status;
    // comando es /bin/ls   // comando es completo ej: ls -l || exit(1)
    char primer_programa[MAX]= BIN;
    char segundo_programa[MAX] = BIN;
    char *primer_comando[MAX] ;
    char *segundo_comando[MAX] ;
    char entrada[MAX];
    char *tokens[MAX];
    /*todo comando: solo 1 argumento por simplicidad*/
    printf (">>>>> ");scanf("%[^\n]", &entrada);        
    cantidad_tokens = parsear_comando(entrada, tokens);        
    primer_comando[0] = strcat(primer_programa, tokens[0]);//a la cadena /bin/ le agrega el nombre de un programa al final // primer_comando[1] = NULL;
    if(cantidad_tokens>1){    
        // strcat(primer_comando,tokens[1]);
        primer_comando[1]= tokens[1];
        primer_comando[2]= NULL;
    }        
    if(cantidad_tokens>2){
        segundo_comando[0] = strcat(segundo_programa, tokens[3]); //une la cadena /bin/ y le agrega el nombre de un programa
        if(cantidad_tokens>3){
            segundo_comando[1] = tokens[4];
            segundo_comando[2] = NULL;
        }
        int fds[2];     //file descriptor
        if(!(strcmp(tokens[2], PIPE))){     //compara el tercer token con |  
           
            pipe(fds);
            if(fork() !=0){
                close(1);               //cierra stdout
                dup(fds[1]);            //duplica stdout
                resultado_ejecucion = execv(primer_comando[0],primer_comando );
            }else{
                close(0);               //cierra stdin
                dup(fds[0]);            //duplica stdin
                resultado_ejecucion = execv(segundo_comando[0],segundo_comando );
            }
        }
        
        if(!(strcmp(tokens[2], XOR))){      //compara el tercer token con doble ||   // printf("es ||");
        }

        if(!(strcmp(tokens[2], AND))){      //compara el tercer token con && // printf("es &&");
        }
            // else{printf("no es pipe");}
    }else{ // 1 solo comando sin argumetnos
        if(fork() != 0){
            waitpid(-1, &status,0);
        }else{
            resultado_ejecucion = execv(primer_comando[0], primer_comando );
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

 // strcat(segundo_comando, tokens[3]);
            // tokens[0] = primer programa
            // tokens[1] = argumentos primer programa
            // tokens[2] = || , | , &&
            // tokens[3] = segundo programa
            // tokens[4] = argumentos segundo programa
           