#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAXARG 100

int main(void) {
    char line[1024];
    char *args[MAXARG];
    char *token;
    char *saveptr;
    int i;
    int background;
    int status;

    pid_t pid;
    pid_t child;

    while (1) {
        printf("Pls input cmd : ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        i = 0;
        background = 0;
        token = strtok_r(line, " \t\n", &saveptr);

        while (token != NULL && i < MAXARG - 1) {
            args[i] = token;
            i++;

            token = strtok_r(NULL, " \t\n", &saveptr);
        }
        args[i] = NULL;

        if (args[0] == NULL)
            continue;

        if (strcmp(args[0], "exit") == 0)
            break;

        if (i > 1 && strcmp(args[i - 1], "&") == 0) {
            background = 1;
            args[i - 1] = NULL;
        }
        printf("[%d] Parent process start\n", getpid());

        pid = fork();

        if (pid == 0) {
            printf("[%d] Child process start\n", getpid());
            execvp(args[0], args);
            perror("execvp");
            exit(1);
        }
        else if (pid > 0) {
            if (background == 0) {
                child = wait(&status);

                printf("[%d] Child process end %d\n",
                       getpid(), child);
            }
            printf("SUCCESS\n");
        }
        else {
            perror("fork");
        }
        printf("\n");
    }
    return 0;
}
