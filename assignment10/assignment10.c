#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int pfds[2];
    pipe(pfds);
    int child_pid;
    child_pid = fork();
    if(child_pid==0)
    {       
        dup2(pfds[1], 1);   
        close(pfds[0]); 
        execlp("ls", "-l", NULL);

    }
    else 
    {
        dup2(pfds[0], 0);
        close(pfds[1]); 
        execlp("sort", "-n", NULL);
    }
    exit(0);
}