#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MENSAJE_SALIR "para salir ejecutar EXIT"
#define MENSAJE_USUARIO "ingrese nombre de usuario"
#define MENSAJE_CONTRASENA "ingrese contrasena"
#define MAX 50
#define TIEMPO 15



void sigalrm_handler(int);
void formulario();

int contador;
int flag, status;

int main(){
    char nombre[MAX];
    char passwd[MAX];
    
    while(1){
        flag = 0;
        contador = TIEMPO;
        printf("%s:",  MENSAJE_SALIR);

        signal(SIGALRM,sigalrm_handler);    
        printf("%s:",  MENSAJE_USUARIO);
        scanf("%s",nombre);
        printf("%s:",  MENSAJE_CONTRASENA);   
        alarm(1);//alarma encendira    
        flag = scanf("%s", passwd);

        if(flag){
            alarm(0);// printf("logueado!\n");
            if( fork() != 0 ){
                waitpid(-1, &status,0);
            }else{
                printf("creado: %d\n", execv("/bin/bash", NULL));
            }       
        }
    }
    return 0;
}


void sigalrm_handler(int sig)
{
    if(contador--){
        printf("\ntiempo %d \n", contador);
        alarm(1);        
    }else{
        printf("TIMEOUT\n");
        alarm(0);
        raise(SIGTERM);
    }
}
/**
 * Escriba un programa que muestre una pantalla de inicio de sesión con el mensaje ​ ”login: “​ , y
se quede esperando un string por parte del usuario. Cuando el usuario ingresa una cadena,
el programa debe almacenar la línea ingresada en una variable en memoria y luego mostrar
el mensaje ​ “password: “​ , para quedarse nuevamente esperando que el usuario tipee algo y
presione <ENTER>.
Una vez que el programa escribe “password: “​ , solo esperará por 15 segundos. Si al cabo de
este tiempo el usuario no ingresó ningún password, el programa debe imprimir ​ “Timeout” y
finalizar su ejecución. Para el control de tiempos debe utilizar la señal ​ SIGALRM​ . Si el usuario
ingresa un password y presiona <ENTER> antes de los 15 segundos, debe cancelarse la
alarma pendiente y mediante un ​ fork y un ​ exec ejecutar (en el hijo) ​ /bin/bash​ . Por su parte
el padre quedará esperando que termine la ejecución del hijo y cuando esto ocurra volverá
a la pantalla de inicio de sesión, a pedir un nombre de usuario.
NOTA: ​ Por simplicidad no se hace nada con el username y password ingresados.
*/