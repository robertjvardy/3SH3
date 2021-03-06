#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

float ave_val;
int max_val;
int min_val;
int size;

void *get_ave(int values[]);
void *get_max(int values[]);
void *get_min(int values[]);

int main(int argc, char *argv[])
{

    int values[argc];

    /* add all values from the arguments passed to values array */
    for (int i = 1; i < argc; i++)
    {
        values[i - 1] = atoi(argv[i]);
    }
    size = (argc - 1);

    if (size == 0)
    {
        printf("No numbers passed\n");
        return 0;
    }

    pthread_t average_thread, max_thread, min_thread;

    pthread_create(&average_thread, NULL, get_ave, values);
    pthread_create(&max_thread, NULL, get_max, values);
    pthread_create(&min_thread, NULL, get_min, values);

    pthread_join(average_thread, NULL);
    pthread_join(max_thread, NULL);
    pthread_join(min_thread, NULL);

    printf("Average is: %.2f\n", ave_val);
    printf("Maximum is: %d\n", max_val);
    printf("Minimum is: %d\n", min_val);
    return 0;
}

/* function to find the ave val */
void *get_ave(int values[])
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += values[i];
    }
    ave_val = (float)sum / (float)size;

    return 0;
}

/* function to find the max val */
void *get_max(int values[])
{
    max_val = values[0];
    for (int i = 1; i < size; i++)
    {
        /* set max_val */
        if (max_val < values[i])
        {
            max_val = values[i];
        }
    }
    return 0;
}

/* function to find the min val */
void *get_min(int values[])
{
    min_val = values[0];
    for (int i = 1; i < size; i++)
    {
        /* set min_val */
        if (values[i] < min_val)
        {
            min_val = values[i];
        }
    }
    return 0;
}
