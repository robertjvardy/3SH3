#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>

int value;

void *primes_thread();
int is_prime(int num);

int main(int argc, char *argv[])
{

    value = atoi(argv[1]);
    pthread_t primes_id;

    pthread_create(&primes_id, NULL, primes_thread, NULL);
    pthread_join(primes_id, NULL);

    return 0;
}

int is_prime(int num)
{
    int max = sqrt(num) + 1;
    if (num % 2 == 0)
    {
        return 0;
    }
    else
    {
        for (int i = 3; i <= max; i = i + 1)
        {
            if (num % i == 0)
            {
                return 0;
            }
        }
    }

    return 1;
}

void *primes_thread()
{
    printf("Prime numbers less than %d:\n", value);
    if (value == 1)
    {
        return 0;
    }
    else
    {
        for (int i = 2; i <= value; i++)
        {
            if (is_prime(i))
            {
                printf("%d, ", i);
            }
        }
    }
    return 0;
}
