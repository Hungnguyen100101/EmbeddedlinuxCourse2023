#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAX_NAME_LEN        30
#define MAX_PHONENUM_LEN    11
#define MAX_HOMETOWN_LEN    50
#define MAX_YEAR_OF_BIRTH   15       

typedef struct {
    char    Name[MAX_NAME_LEN];
    char    Yearofbirth[MAX_YEAR_OF_BIRTH];
    char    Hometown[MAX_HOMETOWN_LEN];
}student_t;

student_t Student;

typedef enum {
    STUDENT_GET,
    STUDENT_WRITE,
    STUDENT_READ
}status_t;

status_t Status = STUDENT_GET;

pthread_t thread_id1, thread_id2, thread_id3;
pthread_mutex_t mutex_student;
pthread_cond_t  cond_student = PTHREAD_COND_INITIALIZER;

char filepath[] = "thongtinsinhvien.txt";
int volatile fd;

static void* thread_handler1(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex_student);
        while (Status != STUDENT_GET)
        {
            pthread_cond_wait( &cond_student, &mutex_student);
            sleep(3);
        }
        printf( "This is thread 1\n" );
        printf("Please input student name:");
        fgets( Student.Name, MAX_NAME_LEN, stdin );
        // printf("%s\n",Student.Name);
        printf("Please input student year of birth:");
        fgets( Student.Yearofbirth, MAX_YEAR_OF_BIRTH, stdin );
        // printf("%d\n",Student.Yearofbirth);
        printf("Please input student home town:");
        fgets( Student.Hometown, MAX_HOMETOWN_LEN, stdin );
        // printf("%s\n",Student.Hometown);

        Status = STUDENT_WRITE;
        pthread_cond_broadcast(&cond_student);
        pthread_mutex_unlock(&mutex_student);
    }
    printf("exit\n");
    pthread_exit( NULL );
}

static void* thread_handler2(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex_student);
        while ( Status != STUDENT_WRITE )
        {
            pthread_cond_wait( &cond_student, &mutex_student);
            sleep(3);
        }
        printf( "This is thread 2\n" );

        int fd = open ( filepath, O_CREAT | O_RDWR, S_IRWXU);
        if ( fd == -1) {
            perror("open file error\n");
        }
        else {
            printf ("file descriptor is: %d\n", fd);
            lseek( fd, 0, SEEK_END );
            ssize_t numbytes = write( fd, Student.Name, strlen(Student.Name) ); 
            printf ("Write %ld bytes to file\n",numbytes);
            numbytes += write( fd, Student.Yearofbirth, strlen(Student.Yearofbirth) );
            printf ("Write %ld bytes to file\n",numbytes);
            numbytes += write( fd, Student.Hometown, strlen(Student.Hometown) );  
            printf ("Write %ld bytes to file\n",numbytes);  
            lseek ( fd, numbytes, SEEK_CUR );
            if ( close(fd) == -1 ) {
                perror ("Close file error\n");
            }    
        }
        Status = STUDENT_READ;
        pthread_cond_broadcast(&cond_student);
        pthread_mutex_unlock(&mutex_student);
    }
    printf("exit\n");
    pthread_exit( NULL );
}

static void* thread_handler3(void *arg)
{   
    int read_buff_len = MAX_NAME_LEN +MAX_YEAR_OF_BIRTH + MAX_HOMETOWN_LEN;
    char read_buff [read_buff_len];
    while (1)
    {
        pthread_mutex_lock(&mutex_student);
        while ( Status != STUDENT_READ )
        {
            pthread_cond_wait( &cond_student, &mutex_student );
            sleep(3);
        }
        printf( "This is thread 3\n" );
        printf ("file descriptor is: %d\n", fd);
        // ssize_t readret = read( fd , read_buff, read_buff_len );
        // printf ("%ld\n", readret);
        // printf ("%s", read_buff);
        Status = STUDENT_GET;
        pthread_cond_broadcast(&cond_student);
        pthread_mutex_unlock(&mutex_student);
    }
    printf("exit\n");
    pthread_exit( NULL );
}


int main()
{
    int ret;

    pthread_mutex_init(&mutex_student, NULL);
    // pthread_cond_init(&cond_student, NULL);

    if (ret = pthread_create(&thread_id1, NULL, &thread_handler1, NULL)) {
        printf("pthread_create() error number: %d",ret);
        return -1;
    }
    
    // sleep(1);
    
    if (ret = pthread_create(&thread_id2, NULL, &thread_handler2, NULL)) {
        printf("pthread_create() error number: %d",ret);
        return -1;
    }
    // sleep(1);

    if (ret = pthread_create(&thread_id3, NULL, &thread_handler3, NULL)) {
        printf("pthread_create() error number: %d",ret);
        return -1;
    }

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    pthread_join(thread_id3, NULL);

    pthread_mutex_destroy(&mutex_student);
    pthread_cond_destroy(&cond_student);
    return 0;
}