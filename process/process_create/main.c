#include <unistd.h>
#include <stdio.h>

int main()
{
    pid_t child_pid = fork();
    if (child_pid == 0){
        /*Child process*/
        printf("I'm the child process of: %d\n", getppid());
        printf("My pid is: %d\n", getpid());
    }
    else {
        /*Parent process*/
        printf("I'm the child process of: %d\n", getppid());
        printf("My pid is: %d\n", getpid());
    }
    
    return 0;
}