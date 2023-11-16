#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
void main()
{
    const char* filepath = "test.txt";
    const char* databuff = "hello ubuntu\n";
    int fd;
    ssize_t numofbyte_written;
    struct stat stbuff;
    int getstatflag;
    
    fd = open(filepath,O_CREAT|O_RDWR);
    if (fd == -1)
    {
        perror("Error");
        exit(1);
    }
    numofbyte_written = write(fd,databuff,strlen(databuff));
    if (numofbyte_written == -1)
    {
        perror("write");
        close(fd);
        exit(1);
    }
    getstatflag= stat(filepath,&stbuff);
    if ( getstatflag == -1)
    {
        perror("stat error");
        close(fd);
        exit(1);
    }  
    if (S_ISREG(stbuff.st_mode))
    {
        printf("Regular file\n");
    }
    else if (S_ISDIR(stbuff.st_mode))
    {
        printf("Directory file\n");
    }
    else if (S_ISCHR(stbuff.st_mode))
    {
        printf("Character device file\n");
    }
    else if (S_ISBLK(stbuff.st_mode))
    {
        printf("Block device file\n");
    }
    else if (S_ISFIFO(stbuff.st_mode))
    {
        printf("FIFO file\n");
    }
    else if (S_ISSOCK(stbuff.st_mode))
    {
        printf("Socket file\n");
    }
    else if (S_ISLNK(stbuff.st_mode))
    {
        printf("Link file\n");
    }
    else 
    {
        printf("not a file\n");
    }
    printf("Time of last modification: %ld\nSize: %ld\n ",stbuff.st_mtime,stbuff.st_size);
    close(fd);
}