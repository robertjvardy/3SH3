#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* The threads will serve as the philosphers */
#define THREAD_NUM 5

void *thread_function(int phil_num);
void *pickup_forks(int phil_num);
void *return_forks(int phil_num);

int counter = 0;
pthread_mutex_t mutex;
pthread_cond_t cond_var;

pthread_mutex_init(&mutex, NULL);
pthread_cond_init(&cond_var, NULL);

/* int forks[5] = {1, 1, 1, 1, 1}; */
int forks = 1;

int main()
{
    pthread_t threadId[THREAD_NUM];
    int ret;
    for (int i = 0; i < THREAD_NUM; i++)
    {
        ret = pthread_create(&threadId[i], NULL, thread_function, i);
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

void *thread_function(int phil_num)
{
    printf("%d start!\n", phil_num);
    int randomNumber = rand() % 3;
    printf("Sleeping for %d seconds\n", randomNumber);
    sleep(randomNumber);

    if (forks)
    {
        forks -= 1;
        pickup_forks(phil_num);
        return_forks(phil_num);
    }

    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 10000; i++)
    {
        counter++;
    }
    pthread_mutex_unlock(&mutex);

    printf("%d complete!\n", phil_num);
}

void *pickup_forks(int phil_num)
{
    printf("%d got forks!\n", phil_num);
}

void *return_forks(int phil_num)
{
    printf("%d put forks back!\n", phil_num);
}