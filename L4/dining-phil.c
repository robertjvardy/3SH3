#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* The threads will serve as the philosphers */
#define THREAD_NUM 5

void *thread_function(int phil_num);
void *pickup_forks(int phil_num);
void *return_forks(int phil_num);
int *are_forks_available(int phil_num);

int counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

/* 
    The state of the forks will be represented by the following array
    1 represents a present fork and 0 means its being used
 */
int forks[5] = {1, 1, 1, 1, 1};

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
        int randomNumber = (rand() % 3) + 1;
        sleep(randomNumber);

        pickup_forks(phil_num);
        eat_count++;
        /* sleeping for one second to simulate eating time */
        sleep(1);
        return_forks(phil_num);
    }

    printf("%d complete!\n", phil_num);
}

void *pickup_forks(int phil_num)
{

    int left = phil_num;
    int right;
    if (phil_num == 4)
    {
        right = 0;
    }
    else
    {
        right = phil_num + 1;
    }

    pthread_mutex_lock(&mutex);
    while (!(forks[left] && forks[right]))
    {
        pthread_cond_wait(&cond, &mutex);
    }

    forks[left] = 0;
    forks[right] = 0;

    printf("Phil %d got forks! ", phil_num);

    printf("forks: ");
    for (int i = 0; i < THREAD_NUM; i++)
    {
        printf("%d ", forks[i]);
    }
    printf("\n");
    pthread_mutex_unlock(&mutex);
}

void *return_forks(int phil_num)
{
    int left = phil_num;
    int right;
    if (phil_num == 4)
    {
        right = 0;
    }
    else
    {
        right = phil_num + 1;
    }

    pthread_mutex_lock(&mutex);
    forks[left] = 1;
    forks[right] = 1;

    printf("Phil %d put forks back! ", phil_num);

    printf("forks: ");
    for (int i = 0; i < THREAD_NUM; i++)
    {
        printf("%d ", forks[i]);
    }
    printf("\n");

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
}