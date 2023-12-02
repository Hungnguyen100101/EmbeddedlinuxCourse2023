#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main()
{
    pid_t child_pid = fork();
    int status;

    if (child_pid == 0) {
        /*Child process*/
        printf("I'm the child process of: %d\n", getppid());
        printf("My pid is: %d\n", getpid());
        
        printf("Exit after 1 second\n");
        sleep(1);
    }
    else {
        /*Parent process*/
        printf("I'm the child process of: %d\n", getppid());
        printf("My pid is: %d\n", getpid());

        waitpid(child_pid,&status,WUNTRACED);

        if (WIFEXITED(status)) {
            printf("The child process is terminated normally\n");
        }    
    }

    return 0;
}