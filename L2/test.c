#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[] ) {
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
	// printf("%s\n", argv[1]);
        // execlp("/bin/ls", "ls", NULL);
	// execvp(argv[0], argv);
	system(argv[1]);
	//printf("%d\n", argc);
	return 0;
    }
    else
    { /* parent process */
        /* parent will wait for the child to complete */
        wait(NULL);
	// printf("%s\n", argv[1]);
        printf("Parent Complete\n");
    }
    return 0;
}
