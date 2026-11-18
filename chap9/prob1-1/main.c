#include <stdio.h>
#include <unistd.h>
/* fork1.c */
int main() {
	int pid;
	printf("[%d] Process Start\n", getpid());
	pid=fork();
	printf("[%d] Process: Return value %d\n", getpid(), pid);
}
