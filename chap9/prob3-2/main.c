#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/* execute2 */
int main() {
	printf("Parent proces start\n");
	if(fork()==0) {
		execl("/bin/echo","echo","hello",NULL);
		fprintf(stderr,"First fail");
		exit(1);
	}

	if(fork()==0) {
		execl("/bin/date","date",NULL);
		fprintf(stderr,"Second fail");
		exit(2);
	}

	if(fork()==0) {
		execl("/bin/ls","ls","-1",NULL);
		fprintf(stderr,"Third fail");
		exit(3);
	}
	printf("Parent process end\n");
}
