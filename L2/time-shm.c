#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    	pid_t pid;

    	const int SIZE = 4096;
    	const char *name = "OS";
    	const char *message_0 = "Test";
    	int fd;
    	char *ptr;
    	fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    	ftruncate(fd, SIZE);

	pid = fork();

	if(pid < 0) {
		fprintf(stderr, "fork failed");
		return 1;
	}
	else if (pid == 0) {
		// child process
	    	ptr = (char *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

		struct timeval start;
		gettimeofday(&start, NULL);

		char str[60];
		sprintf(str, "%lu", start.tv_usec);
		sprintf(ptr, "%s", str);
		ptr += strlen(str);
		
		system(argv[1]);
		return 0;
	}
	else {
		// parent process
		wait(NULL);
		ptr = (char *)mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);

		long start;
		long endtime;
		char *ptr1;
		start = strtol(ptr, &ptr1, 10);

		struct timeval end;
		gettimeofday(&end, NULL);

		printf("Time elapsed: %lu\n", end.tv_usec - start);
		shm_unlink(name);
	}

	return 0;
}
