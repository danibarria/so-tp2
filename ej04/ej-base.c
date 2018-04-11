#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

#define TRUE 1

int main() {
    int status;
    if (fork() != 0) /* Código del padre */
    {
        printf("\nPADRE\n");
        waitpid(-1, &status,0);
    }else{
        execl("/usr/bin/firefox", "",NULL);
    }/* Código del hijo */  
    
    return 0;
}