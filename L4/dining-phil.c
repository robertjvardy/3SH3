#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* The threads will serve as the philosphers */
#define THREAD_NUM 5

void *thread_function(void *parameter, int phil_num);

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
        ret = pthread_create(&threadId[i], NULL, thread_function, threadName[i], i);
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

void *thread_function(void *parameter, int phil_num)
{
    const char *name = (char *)parameter;
    printf("%s %d start!\n", name, phil_num);
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 10000; i++)
    {
        counter++;
    }
    pthread_mutex_unlock(&mutex);

    int randomNumber = rand() % 3;
    printf("Sleeping for %d seconds\n", randomNumber);
    sleep(randomNumber);

    printf("%s complete!\n", name);
}