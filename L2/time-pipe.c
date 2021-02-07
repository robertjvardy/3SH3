#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>


#define BUFFER_SIZE 50
#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[])
{
    char write_msg[BUFFER_SIZE] = "Hello";
    char read_msg[BUFFER_SIZE];
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1)
    {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    if (pid > 0)
    {
	wait(NULL);
        close(fd[WRITE_END]);
        read(fd[READ_END], read_msg, BUFFER_SIZE);
        close(fd[READ_END]);
	long start;
	long endtime;
	char *ptr;
	start = strtol(read_msg, &ptr, 10);

	struct timeval end;
	gettimeofday(&end, NULL);

        printf("Elapsed time: %lu\n", end.tv_usec - start);
    }
    else
    { /* child process */
        close(fd[READ_END]);
	struct timeval current;
	gettimeofday(&current, NULL);

	char str[50];
	sprintf(str, "%lu", current.tv_usec);

	system(argv[1]);

        write(fd[WRITE_END], str, strlen(str) + 1);
        close(fd[WRITE_END]);
    }
    return 0;
}
