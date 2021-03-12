#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* The threads will serve as the philosphers */
#define THREAD_NUM 5

void *thread_function(void *parameter);

int counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main()
{
    pthread_t threadId[THREAD_NUM];
    char *threadName[THREAD_NUM] = {"Thread 1",
                                    "Thread 2",
                                    "Thread 3",
                                    "Thread 4",
                                    "Thread 5"};
    int ret;
    for (int i = 0; i < THREAD_NUM; i++)
    {
        ret = pthread_create(&threadId[i], NULL, thread_function, threadName[i]);
        if (ret != 0)
        {
            fprintf(stderr, "Create thread failed!\n");
            return -1;
        }
    }

    for (int i = 0; i < THREAD_NUM; i++)
    {
        pthread_join(threadId[i], NULL);
    }

    printf("Final counter = %d\n", counter);
    printf("Main complete\n");
    return 0;
}

void *thread_function(void *parameter)
{
    const char *name = (char *)parameter;
    printf("%s start!\n", name);
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 10000; i++)
    {
        counter++;
    }
    pthread_mutex_unlock(&mutex);

    int randomnumber = rand() % 10;
    printf("%d\n", randomnumber);

    printf("%s complete!\n", name);
}