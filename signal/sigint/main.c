#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void sigint_handler(int signum) {
    printf("This is SIGINT handler\n");
}

int main () 
{
    if (signal(SIGINT, sigint_handler) == SIG_ERR)  {
        perror("Can not register action for SIGINT");
        exit(1);
    }
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    if ( sigprocmask(SIG_BLOCK, &mask, NULL) == 0 ) {
        if (sigismember(&mask, SIGINT) == 1)    {
            printf("SIGINT block\n");
        }
    }
    sleep(10);
     if ( sigprocmask(SIG_UNBLOCK, &mask, NULL) == 0 ) {
        if (sigismember(&mask, SIGINT) == 1)    {
            printf("SIGINT unblock\n");
        }
    }
    while (1)
    {
        sleep (2);
    }
}