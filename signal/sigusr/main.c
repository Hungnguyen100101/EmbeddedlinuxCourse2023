#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
void sigusr_handler(int signum) {
    if (signum == SIGUSR1)  {
        printf("This is signal USR1 handler\n");
        // exit(0);
    }
    if (signum == SIGUSR2)  {
        printf("This is signal USR2 handler\n");
        // exit(0);
    }
}
void sigint_handler(int signum) {
    printf("This is signal INT handler\n");
}
int main()
{
   
    if (signal(SIGINT, sigint_handler) == SIG_ERR)  {
        perror("Can not register action for SIGINT\n");
        exit(1);
    }
    if (signal(SIGUSR1, sigusr_handler ) == SIG_ERR)    {
        perror("Can not register action for SIGUSR1\n");
        exit(1);
    }
    if (signal(SIGUSR2, sigusr_handler ) == SIG_ERR)    {
        perror("Can not register action for SIGUSR2\n");
        exit(1);
    }
    printf("Process ID: %d\n", getpid());
    // printf("Waitting for signal");
    sleep(1);
    while (1) {
        // printf(". ");
        sleep(2);
    }

}