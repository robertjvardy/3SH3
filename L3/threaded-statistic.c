#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int size;
float ave;
int min;
int max;

void *get_ave(int nums[]);
void *get_max(int nums[]);
void *get_min(int nums[]);

int main(int argc, char *argv[])
{

    printf("Statistics Analyzer\n");
    printf("There are %d numbers\n", (argc - 1));
    int nums[argc];

    for (int i = 1; i < argc; i++)
    {
        //printf("%s ", argv[i]);
        nums[i - 1] = atoi(argv[i]);
    }
    size = (argc - 1);
    //printf("\n");
    //printf("%d\n", nums[1] + nums[2]);

    pthread_t ave_id, max_id, min_id;

    pthread_create(&ave_id, NULL, get_ave, nums);
    pthread_create(&max_id, NULL, get_max, nums);
    pthread_create(&min_id, NULL, get_min, nums);

    pthread_join(ave_id, NULL);
    pthread_join(max_id, NULL);
    pthread_join(min_id, NULL);

    printf("Average is: %.2f\n", ave);
    printf("Maximum is: %d\n", max);
    printf("Minimum is: %d\n", min);
    printf("END\n");

    return 0;
}

void *get_ave(int nums[])
{
    pthread_t id = pthread_self();
    //printf("\n");

    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += nums[i];
    }
    ave = (float)sum / (float)size;

    printf("Thread #%lu finished\n", id);
    return 0;
}

void *get_min(int nums[])
{
    pthread_t id = pthread_self();
    //int num_list[size] = (int *)parameter;

    //printf("Num: %d\n", nums[1]);

    min = nums[0];
    for (int i = 1; i < size; i++)
    {
        //printf("%d, ", nums[i]);
        if (min > nums[i])
        {
            min = nums[i];
        }
    }
    //printf("\n");
    printf("Thread #%lu finished\n", id);
    return 0;
}

// this function might overflow cuz niggers commit a lot of crime
void *get_max(int nums[])
{
    pthread_t id = pthread_self();
    //int num_list[size] = (int *)parameter;

    //printf("Num: %d\n", nums[1]);

    max = nums[0];
    for (int i = 1; i < size; i++)
    {
        //printf("%d, ", nums[i]);
        if (max < nums[i])
        {
            max = nums[i];
        }
    }
    //printf("\n");
    printf("Thread #%lu finished\n", id);
    return 0;
}