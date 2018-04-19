#include <stdio.h>
#include <string.h>


#define MAX 20
#define BIN "/bin/"
#define PIPE "|"
#define XOR "||"
#define AND "&&" 

#define PARSE_PROG_0  primer_comando[0] = strcat(ruta, tokens[0]);//a la cadena /bin/ le agrega el nombre de un ruta al final // primer_comando[1] = NULL;
#define PARSE_ARGS_0  primer_comando[1]= tokens[1];  
#define PARSE_PROG_1  segundo_comando[0] = strcat(ruta2,tokens[3]);
#define PARSE_ARGS_1  segundo_comando[1] = tokens[4];
#define PARSE_PROG_2  segundo_comando[0] = strcat(ruta2,tokens[2]);

#define ES_AND_1  !(strcmp(tokens[1], AND))
#define ES_PIPE_1 !(strcmp(tokens[1], PIPE))
#define ES_XOR_1  !(strcmp(tokens[1], XOR))

#define ES_AND_2  !(strcmp(tokens[2], AND))
#define ES_PIPE_2 !(strcmp(tokens[2], PIPE))
#define ES_XOR_2  !(strcmp(tokens[2], XOR))

void mostrar_prompt(char* cadena);
int parsear_comando(char* cadena, char* arg[]);

/* Muestra un prompt por pantalla
 * Retorna la cadena que haya ingresado el usuario hasta presionar ENTER
 */
void mostrar_prompt(char* cadena) {
	printf ("> ");
	scanf("%[^\n]", &cadena);
}


/* Recibe una cadena y la divide en subcadenas
 * tomando como separador el espacio
 * Retorna las subcadenas como un arreglo de cadenas llamado arg
 */
int parsear_comando(char* cadena, char* arg[]) {    
   char *ptrToken;
   char *comando;
   int cont=0;
   
//    printf("La cadena es: %s \n", cadena);
          
   ptrToken = strtok(cadena, " "); //obtengo el primer token
   comando = ptrToken;

   while (ptrToken != NULL) {
		arg[cont] = ptrToken;
    //  printf("Arg[%d]: %s \n",cont, arg[cont]);
		cont++;
		ptrToken = strtok(NULL, " "); //obtengo el siguiente token		
   }
   //modificado parsear comando devuelve cantidad de tokens
   return cont;
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
*/
// tokens[0] = primer ruta
// tokens[1] = argumentos primer ruta
// tokens[2] = || , | , &&
// tokens[3] = segundo ruta
// tokens[4] = argumentos segundo ruta