#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	FILE *fp;
	int c, i;
	int line=1;
	int number=0;

	if(argc<2)
		fp=stdin;
	else { i=1;
		if(strcmp(argv[1], "-n")==0) {
			number=1;
			i=2;
		}
		line=1;

		for(; i<argc; i++) {        //error part, gpt hint
			if((fp=fopen(argv[i], "r"))==NULL) {
				fprintf(stderr, "Error Open File\n");
				continue;
			}
			c=getc(fp);

			if(number && c!=EOF)
				printf("%4d ",line);

			while(c!=EOF) {
				putc(c,stdout);

				if(c=='\n') {
					line++;
					c=getc(fp);

					if(number && c!=EOF) {
						printf("%4d ",line);
					}
				}
				else c=getc(fp);
			}
			fclose(fp);
		}
		return 0;
	}
	c=getc(fp);
	while(c!=EOF) {
		putc(c,stdout);
		c=getc(fp);
	}
	return 0;
}


