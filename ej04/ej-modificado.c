#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/wait.h>


#define TRUE 1

int main() {
    int status;
    char *args[2];

    args[0] = "/bin/ls";
    // args[1] = "-l";
    args[1] = "-ltr";
    args[2] = NULL;

    if (fork() != 0) /* Código del padre */
    {
        printf("\nPADRE\n");
        waitpid(-1, &status,0);
    }else{/* Código del hijo */
        printf("\n%d\n", execv( args[0], args));
    }  
    
    return 0;
}   