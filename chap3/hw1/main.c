#include <stdio.h>
#include <string.h>
#include "copy.h"
#define MAXLINE 100

char line[MAXLINE];
char lineArray[100][MAXLINE];

int main() {
	int count=0;
	int i,j;
	char temp[MAXLINE];

	while(fgets(line,MAXLINE,stdin)!=NULL) {
		line[strlen(line)-1]='\0';
		copy(line,lineArray[count]);
		count++;
	}

	for(i=0; i<count; i++) {
		for(j=i+1; j<count; j++) {
			if(strlen(lineArray[i])<strlen(lineArray[j])) {
				copy(lineArray[i],temp);
				copy(lineArray[j],lineArray[i]);
				copy(temp,lineArray[j]);
			}
		}
	}
	for(i=0; i<count; i++) {
		printf("%s\n", lineArray[i]);
	}
	return 0;
}
