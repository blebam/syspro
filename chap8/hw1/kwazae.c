#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
static void exit_handler1(), exit_handler2();

int main(int argc, char *argv[]) {
	extern char **environ;
	int i;
	char **ptr;

	if(argc>=2) {
		if(strcmp(argv[1], "-e")==0) {

