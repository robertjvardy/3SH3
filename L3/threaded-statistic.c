#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/* define the global variables as instructed */
float ave;
int min;
int max_val;
int size;

void *get_ave(int values[]);
void *get_max(int values[]);
void *get_min(int values[]);

int main(int argc, char *argv[])
{

    printf("There are %d numbers\n", (argc - 1));
    int values[argc];

    /* read the values from the args passed and add them to the values array */
    for (int i = 0; i < argc; i++)
    {
        values[i] = atoi(argv[i + 1]);
    }
    /* define the size */
    size = (argc - 1);

    pthread_t ave_id, max_id, min_id;

    pthread_create(&ave_id, NULL, get_ave, values);
    pthread_create(&max_id, NULL, get_max, values);
    pthread_create(&min_id, NULL, get_min, values);

    pthread_join(ave_id, NULL);
    pthread_join(max_id, NULL);
    pthread_join(min_id, NULL);

    printf("Average is: %.2f\n", ave);
    printf("Maximum is: %d\n", max_val);
    printf("Minimum is: %d\n", min);
    printf("END\n");

    return 0;
}

void *get_ave(int values[])
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += values[i];
    }
    ave = (float)sum / (float)size;
    return 0;
}

void *get_min(int values[])
{
    min = values[0];
    for (int i = 1; i < size; i++)
    {
        if (values[i] < min)
        {
            min = values[i];
        }
    }
    return 0;
}

void *get_max(int values[])
{
    max_val = values[0];
    for (int i = 1; i < size; i++)
    {
        /*if (values[i] > max_val)
        {
            max_val = values[i];
        }*/
        max_val = max(max_val, values[i]);
    }
    return 0;
}