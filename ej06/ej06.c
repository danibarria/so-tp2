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

#define PARSE_PROG_0  primer_comando[0] = strcat(ruta, tokens[0]);//a la cadena /bin/ le agrega el nombre de un ruta al final // primer_comando[1] = NULL;
#define PARSE_ARGS_0  primer_comando[1]= tokens[1];  
#define PARSE_PROG_1  segundo_comando[1] = tokens[3];
#define PARSE_ARGS_1  segundo_comando[2] = tokens[4];
#define PARSE_PROG_2  segundo_comando[0] = strcat(ruta2,tokens[2]);


int main(){
    int resultado_ejecucion;
    int cantidad_tokens;
    int status;
    // comando es /bin/ls   // comando es completo ej: ls -l || exit(1)
    char ruta[MAX]= BIN;
    char ruta2[MAX] = BIN;
    char *primer_comando[MAX] ;
    char *segundo_comando[MAX] ;
    char entrada[MAX];
    char *tokens[MAX];
    /*todo comando: solo 1 argumento por simplicidad*/
    printf (">>>>> ");scanf("%[^\n]", &entrada);        
    cantidad_tokens = parsear_comando(entrada, tokens);        
    switch(cantidad_tokens){
        case 1: //ls
            PARSE_PROG_0
            primer_comando[1]= NULL;
        break;
        case 2: //ls -l
            PARSE_PROG_0
            PARSE_ARGS_0
            primer_comando[2]= NULL;
        break;
        case 3: // ls && pwd
            PARSE_PROG_0
            // tokens[1] es pipe
            PARSE_PROG_2
            primer_comando[1] = NULL;
            segundo_comando[1] = NULL;
        break;
        case 4: // ls -r | pwd
            PARSE_PROG_0
            PARSE_PROG_1
            PARSE_ARGS_0
            PARSE_ARGS_1
            primer_comando[2] = NULL;
            segundo_comando[1] = NULL;
        break;
        case 5: // grep asd | ls -r
            PARSE_PROG_0
            PARSE_PROG_1
            PARSE_ARGS_0
            PARSE_ARGS_1
            primer_comando[2] = NULL;
            segundo_comando[2] = NULL;
        break;
        default:
            printf("invalido\n");
        break;
    };
    
    switch(cantidad_tokens){
        //esto para hacer pipes, && y ||
        case 1:
        case 2:
            if(fork() != 0){
                waitpid(-1, &status,0);
            }else{
                resultado_ejecucion = execv(primer_comando[0], primer_comando );
                if(resultado_ejecucion){
                    printf("no es un comando valido\n");
                }
            }
        break;
        case 3:
        break;
        case 4:
        case 5://para 4 y 5 son lo mismo, ambos son ls -l || pwd = simbolo en token[2] o grep c && man ls
        break;
    }
    if(cantidad_tokens>2){
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
        
        if(!(strcmp(tokens[2], XOR))){      //compara el tercer token con doble ||   // 
            printf("es ||");
            // pipe(fds);
            if(fork() !=0){
                close(1);               //cierra stdout
                dup(fds[1]);            //duplica stdout
                waitpid(-1,&status,0);
                if(!(WEXITSTATUS(status))){
                    resultado_ejecucion = execv(segundo_comando[0],segundo_comando );
                }                   
            }else{
                close(0);               //cierra stdin
                dup(fds[0]);            //duplica stdin
                // resultado_ejecucion == 
                execv(primer_comando[0],primer_comando );
            }
        }

        if(!(strcmp(tokens[2], AND))){      //compara el tercer token con && // printf("es &&");
        }
            // else{printf("no es pipe");}
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
            // tokens[0] = primer ruta
            // tokens[1] = argumentos primer ruta
            // tokens[2] = || , | , &&
            // tokens[3] = segundo ruta
            // tokens[4] = argumentos segundo ruta
           