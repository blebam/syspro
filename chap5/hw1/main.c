#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd;
    int totalLine = 0;
    int line = 0;
    int pos = 0;
    int i;
    int start, end;
    char buf;
    char option[100];
    char savedText[10][100];

    if (argc != 2) {
        printf("How to use: %s file\n", argv[0]);
        return 1;
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        printf("File Open Error\n");
        return 1;
    }

    while (read(fd, &buf, 1) > 0) {
        if (buf == '\n') {
            savedText[line][pos] = '\0';
            line++;
            pos = 0;

            if (line >= 10)
                break;
        }
        else {
            if (pos < 99) {
                savedText[line][pos] = buf;
                pos++;
            }
		}
    }
	if (pos > 0) {
        savedText[line][pos] = '\0';
        line++;
    }

    totalLine = line;
    close(fd);

    printf("File read success\n");
    printf("Total Line : %d\n", totalLine);
    printf("You can choose 1 ~ %d Line\n", totalLine);
    printf("Pls 'Enter' the line to select : ");
    scanf("%99s", option);

    if (option[0] == '*' && option[1] == '\0') {
        for (i = 0; i < totalLine; i++) {
            printf("%s\n", savedText[i]);
        }
    }
    else {
		i = 0;
		while (option[i] != '\0') {
            start = 0;
            end = 0;

            while (option[i] >= '0' && option[i] <= '9') {
                start = start * 10 + option[i] - '0';
                i++;
            }

            if (option[i] == '-') {
                i++;

                while (option[i] >= '0' && option[i] <= '9') {
                    end = end * 10 + option[i] - '0';
                    i++;
                }

                if (start >= 1 && end <= totalLine && start <= end) {
                    for (line = start; line <= end; line++) {
                        printf("%s\n", savedText[line - 1]);
                    }
                }
            }
            else {
                if (start >= 1 && start <= totalLine) {
                    printf("%s\n", savedText[start - 1]);
                }
            }
            if (option[i] == ',')
                i++;
            else
                break;
        }
    }
    return 0;
}
