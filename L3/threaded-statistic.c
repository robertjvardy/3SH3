#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int size;
float average;
int minimum;
int maximum;

void *thread_function_calculate_average(int nums[]);
void *thread_function_calculate_maximum(int nums[]);
void *thread_function_calculate_minimum(int nums[]);

int main(int argc, char *argv[])
{

    int nums[argc];

    for (int i = 1; i < argc; i++)
    {
        nums[i - 1] = atoi(argv[i]);
    }
    size = (argc - 1);

    pthread_t thread_calculate_average,
        thread_calculate_maximum,
        thread_calculate_minimum;

    int ret1 = pthread_create(&thread_calculate_average, NULL,
                              thread_function_calculate_average, nums);

    int ret2 = pthread_create(&thread_calculate_maximum, NULL,
                              thread_function_calculate_maximum, nums);

    int ret3 = pthread_create(&thread_calculate_minimum, NULL,
                              thread_function_calculate_minimum, nums);

    pthread_join(thread_calculate_average, NULL);
    pthread_join(thread_calculate_maximum, NULL);
    pthread_join(thread_calculate_minimum, NULL);

    printf("Average is: %.2f\n", average);
    printf("Maximum is: %d\n", maximum);
    printf("Minimum is: %d\n", minimum);
    return 0;
}

void *thread_function_calculate_average(int nums[])
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += nums[i];
    }
    average = (float)sum / (float)size;

    return 0;
}

void *thread_function_calculate_minimum(int nums[])
{
    minimum = nums[0];
    for (int i = 1; i < size; i++)
    {
        if (minimum > nums[i])
        {
            minimum = nums[i];
        }
    }
    return 0;
}

void *thread_function_calculate_maximum(int nums[])
{
    maximum = nums[0];
    for (int i = 1; i < size; i++)
    {
        if (maximum < nums[i])
        {
            maximum = nums[i];
        }
    }
    return 0;
}
