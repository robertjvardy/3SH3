#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>

int prime;

void *thread_function_print_primes();
int is_prime(int num);

int main(int argc, char *argv[])
{

    printf("Prime Number Calculator\n");

    prime = atoi(argv[1]);
    printf("all primes up to: %d\n", prime);

    pthread_t thread_primes;

    pthread_create(&thread_primes, NULL, thread_function_print_primes, NULL);

    pthread_join(thread_primes, NULL);

    return 0;
}

void *thread_function_print_primes()
{

    pthread_t id = pthread_self();

    printf("The prime numbers are:\n");
    for (int i = 2; i <= prime; i++)
    {
        if (is_prime(i))
        {
            printf("%d, ", i);
        }
    }

    printf("\nThread #%lu finished\n", id);

    return 0;
}

int is_prime(int num)
{
    if (num % 2 == 0)
    {
        return 0;
    }
    else
    {
        int sr = sqrt(num) + 1;
        for (int i = 3; i <= sr; i++)
        {
            if (num % i == 0)
            {
                return 0;
            }
        }
    }

    return 1;
}
