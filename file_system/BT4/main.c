#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

void main()
{
    char filepath[50];
    int fd ;
    struct  stat statbuff;
    char *writebuff= "moi ghi them\n";
    
    if (!fgets(filepath, sizeof(filepath), stdin)) {
        fputs("Input error :(\n\n", stderr);
        return ;
    }
    filepath[strcspn(filepath, "\n")] = '\0';
    fd = open(filepath,O_CREAT|O_RDWR|O_APPEND,S_IRWXU);
    if (fd == -1)
    {
        perror("Open\n");
        exit(1);
    }
   off_t lseeksuccess= lseek(fd,0,SEEK_SET);
   if (lseeksuccess == -1)
   {
        perror("seek\n");
        close(fd);
        exit(1);
   } 
   ssize_t writesuccess=write(fd,writebuff,strlen(writebuff));
   if (writesuccess == -1)
   {
        perror("write\n");
        close(fd);
        exit(1);
   }
   printf("done\n");
   close(fd);
}