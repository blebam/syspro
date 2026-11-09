#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[]) {
	char **ptr;
	extern char **environ;
	char *val;

	if(argc<2) {
		return 0;
	}

	switch(argv[1][1]) {
		case 'e':
			if(argc==2) {
				for(ptr=environ; *ptr!=NULL; ptr++) {
					printf("%s\n", *ptr);
				}
			}
			else {
				val=getenv(argv[2]);
				if(val!=NULL) {
					printf("%s = %s\n", argv[2], val);
				}
			}
			break;
	
		case 'u':
			printf("My Realistic User ID : %d(%s)\n", getuid(), getpwuid(getuid())->pw_name);
			printf("My Valid User ID : %d(%s)\n", geteuid(), getpwuid(geteuid())->pw_name);
			break;

		case 'g':
			printf("My Realistic Group ID : %d(%s) \n", getgid(), getgrgid(getgid())->gr_name);
			printf("My Valid Group ID : %d(%s) \n", getegid(), getgrgid(getegid())->gr_name);
			break;

		case 'i' :
			printf("my process number : [%d]\n", getpid());
			break;

		case 'p' :
			printf("my parent's process number : [%d]\n", getppid());
			break;
	}
	return 0;
}
