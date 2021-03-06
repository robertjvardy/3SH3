#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    /* fork a child process */
    pid = fork();

    if (pid < 0)
    { /* error occurred */
        fprintf(stderr, "Fork Failed");
        return 1;
    }

    else if (pid == 0)
    { /* child process */
        execlp("/bin/ls", "ls", NULL);
	return 0;
    }
    else
    { /* parent process */
        /* parent will wait for the child to complete */
	sleep(10);
        wait(NULL);
        printf("Child Complete\n");
    }
    return 0;
}
