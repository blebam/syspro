#include <stdio.h>
#include <stdlib.h>
static void exit_handler1(),exit_handler2();
 
int main() {
	if (atexit(exit_handler1) != 0)	
		perror("exit_handler1 NOT allowed");
    if(atexit(exit_handler2) != 0) 	
	    perror("exit_handler2 NOT allowed");
	printf("main END\n");
   
	exit(0);
}

static void exit_handler1(void) {
    printf("first exit processor\n");
}

static void exit_handler2(void) {
   printf("second exit processor\n");
}

