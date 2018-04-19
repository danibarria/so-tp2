#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "utiles.h"

int main(){
    int fds[2];     //file descriptor    
    int resultado_ejecucion;
    int cantidad_tokens;
    int status;// comando es /bin/ls   // comando es completo ej: ls -l || exit(1)
    char ruta[MAX]= BIN;
    char ruta2[MAX] = BIN;
    char *primer_comando[MAX] ;
    char *segundo_comando[MAX] ;
    char entrada[MAX];
    char *tokens[MAX];
    /*todo comando: solo 1 argumento por simplicidad*/
    printf (">>>>> ");scanf("%[^\n]", &entrada);        
    cantidad_tokens = parsear_comando(entrada, tokens);        
    switch(cantidad_tokens){//acomoda los comandos en los arreglos
        case 1: //ls
            PARSE_PROG_0
            primer_comando[1]= NULL;
        break;
        case 2: //ls -l
            PARSE_PROG_0
            PARSE_ARGS_0
            primer_comando[2]= NULL;
        break;
        case 3: // ls && pwd // tokens[1] es pipe o && o ||
            PARSE_PROG_0           
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
    
    switch(cantidad_tokens){ //esto para hacer pipes, && y ||
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
        case 3://TODO: ej pwd && ls
        break;
        case 4:
        case 5://para 4 y 5 son lo mismo, ambos son ls -l || pwd = simbolo en token[2] o grep c && man ls
        if(ES_PIPE_2){     //compara el tercer token con |       
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
        if(ES_XOR_2){      //compara el tercer token con doble ||   // 
            if(fork() !=0){
                waitpid(-1,&status,0);
                if((WEXITSTATUS(status))){// fallo, se ejecuta //printf("es || %d \n", status);                    
                    execv(segundo_comando[0],segundo_comando );
                }
            }else{
                execv(primer_comando[0],primer_comando );
            }
        }
        if(ES_AND_2){      //compara el tercer token con && // printf("es &&");
            if(fork() !=0){    
                waitpid(-1,&status,0);
                if(!(WEXITSTATUS(status))){//no falla, se ejecuta
                    execv(segundo_comando[0],segundo_comando );
                }          
            }else{              
                execv(primer_comando[0],primer_comando );
            }       
        }
        break;
    };        
    return 0;
}


           