#include <stdio.h>
#include "bookquery.c"

int main(int argc, char *argv[]) {
	struct Book name;
	FILE *fp;

	if(argc!=2) {
		fprintf(stderr, "How to use: %s FileName\n", argv[0]);
		return 1;
	}
	fp=fopen(argv[1], "r");
	printf("%-2s %-6s %-6s %-4s %-11s %-6s\n", "id", "booknm", "author", "year", "numofborrow", "borrow");
	while(fscanf(fp,"%d %s %s %d %d %s",&name.id,&name.booknm,&name.author,&name.year,&name.numofborrow,&name.borrow)==6)
		printf("%3ld %7s %7s %-5ls %-12ls %-7ls\n",&name.id,&name.booknm,&name.author,&name.year,&name.numofborrow,&name.borrow);
	fclose(fp);
	return 0;
}
