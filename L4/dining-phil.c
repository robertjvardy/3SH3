#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* The threads will serve as the philosphers */
#define THREAD_NUM 5

void *thread_function(int phil_num);
void *pickup_forks(int phil_num);
void *return_forks(int phil_num);

int counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

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

    printf("Main complete\n");
    return 0;
}

void *thread_function(int phil_num)
{
    int eat_count = 0;
    while (eat_count < 5)
    {
        int has_fork = 0;
        int randomNumber = rand() % 3;
        /* printf("Phil %d: Sleeping for %d seconds\n", phil_num, randomNumber); */
        sleep(randomNumber);

        pthread_mutex_lock(&mutex);
        if (!forks)
        {
            pthread_cond_wait(&cond, &mutex);
        }
        printf("here: %d", phil_num);
        eat_count++;
        forks -= 1;
        pickup_forks(phil_num);
        has_fork = 1;
        pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&mutex);
        forks += 1;
        return_forks(phil_num);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }

    printf("%d complete!\n", phil_num);
}

void *pickup_forks(int phil_num)
{
    printf("Phil %d got forks!\n", phil_num);
}

void *return_forks(int phil_num)
{
    printf("Phil %d put forks back!\n", phil_num);
}