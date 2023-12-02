#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

void signal_handler(int signum)
{
    printf("Signal handler\n");
    wait(NULL);
}
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
        signal(SIGCHLD,signal_handler);

        printf("I'm the child process of: %d\n", getppid());
        printf("My pid is: %d\n", getpid());
        sleep(5);
    }

    return 0;
}