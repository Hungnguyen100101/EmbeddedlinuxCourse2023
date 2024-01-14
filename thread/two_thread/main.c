#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN        30
#define MAX_PHONENUM_LEN    11
#define MAX_HOMETOWN_LEN    50

typedef struct {
    char    Name[MAX_NAME_LEN];
    int     Yearofbirth;
    char    Phonenumber[MAX_PHONENUM_LEN];
    char    Hometown[MAX_HOMETOWN_LEN];
}human;

pthread_t thread_id1, thread_id2;

static void* thread_handler(void *arg)
{
    human * Human = (human*) arg;
    pthread_t current_thread_id = pthread_self();
    if (pthread_equal(thread_id1, current_thread_id)) {
        printf("This is thread_id1\n");
    }
    
    else if (pthread_equal(thread_id2, current_thread_id)) {
        printf("This is thread_id2\n");
        printf("Name: %s\n", Human->Name);
        printf("Year of birth: %d\n", Human->Yearofbirth);
        printf("Phone number: %s\n", Human->Phonenumber);
        printf("Home town: %s\n", Human->Hometown);
    }
}

int main()
{
    int ret;
    human Human;

    strcpy(Human.Name, "Hung");
    Human.Yearofbirth = 2001;
    strcpy(Human.Phonenumber, "0332345678"); 
    strcpy(Human.Hometown, "Ha noi"); 

    if (ret = pthread_create(&thread_id1, NULL, &thread_handler, NULL)) {
        printf("pthread_create() error number: %d",ret);
        return -1;
    }

    sleep(2);

    if (ret = pthread_create(&thread_id2, NULL, &thread_handler, &Human)) {
        printf("pthread_create() error number: %d",ret);
        return -1;
    }

    sleep(5);
    return 0;
}