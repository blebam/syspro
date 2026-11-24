#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int i;
    int fd;
    char buf;
    off_t size;
    off_t end;
    off_t start;

    if (argc != 2) {
        printf("How to use: %s file\n", argv[0]);
        exit(1);
    }
    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }
    size = lseek(fd, 0L, SEEK_END);

    if (size == -1) {
        perror("lseek");
        close(fd);
        exit(3);
    }
    end = size;

    while (end > 0) {
        start = end - 1;
        while (start > 0) {
            lseek(fd, start - 1, SEEK_SET);
            read(fd, &buf, 1);
            if (buf == '\n')
                break;
            start--;
        }
        lseek(fd, start, SEEK_SET);

        for (i = start; i < end; i++) {
            read(fd, &buf, 1);

            if (buf != '\n')
                write(1, &buf, 1);
        }
        write(1, "\n", 1);
        end = start;
    }
    close(fd);
    return 0;
}
