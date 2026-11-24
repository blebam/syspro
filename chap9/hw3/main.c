#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#define MAXARG 100

int main(void) {
    char line[1024];
    char command[1024];
    char cmdline[2048];
    char *cmd;
    char *token;
    char *save_cmd;
    char *save_arg;
    char *args[MAXARG];
    char *inputFile;
    char *outputFile;
    int i;
    int j;
    int background;
    int fd;

    pid_t pid;

    while (1) {
        printf("[shell] ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        save_cmd = NULL;
        cmd = strtok_r(line, ";", &save_cmd);

        while (cmd != NULL) {
            inputFile = NULL;
            outputFile = NULL;
            background = 0;
            i = 0;
            j = 0;

            while (*cmd != '\0' && j < 2040) {
                if (*cmd == '<' || *cmd == '>' || *cmd == '&') {
                    cmdline[j++] = ' ';
                    cmdline[j++] = *cmd;
                    cmdline[j++] = ' ';
                }
                else {
                    cmdline[j++] = *cmd;
                }
                cmd++;
            }

            cmdline[j] = '\0';
            save_arg = NULL;
            token = strtok_r(cmdline, " \t\n", &save_arg);

            while (token != NULL && i < MAXARG - 1) {
                if (strcmp(token, "<") == 0) {
                    token = strtok_r(NULL, " \t\n", &save_arg);
                    inputFile = token;
                }
                else if (strcmp(token, ">") == 0) {
                    token = strtok_r(NULL, " \t\n", &save_arg);
                    outputFile = token;
                }
                else if (strcmp(token, "&") == 0) {
                    background = 1;
                }
                else {
                    args[i] = token;
                    i++;
                }
                token = strtok_r(NULL, " \t\n", &save_arg);
            }
            args[i] = NULL;

            if (args[0] != NULL) {
                if (strcmp(args[0], "exit") == 0)
                    return 0;

                pid = fork();

                if (pid == 0) {
                    if (inputFile != NULL) {
                        fd = open(inputFile, O_RDONLY);

                        if (fd < 0) {
                            perror(inputFile);
                            exit(1);
                        }
                        dup2(fd, 0);
                        close(fd);
                    }
                    if (outputFile != NULL) {
                        fd = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);

                        if (fd < 0) {
                            perror(outputFile);
                            exit(1);
                        }
                        dup2(fd, 1);
                        close(fd);
                    }
                    execvp(args[0], args);

                    perror(args[0]);
                    exit(1);
                }
                else if (pid > 0) {
                    if (background == 0) {
                        waitpid(pid, NULL, 0);
                    }
                }
                else {
                    perror("fork");
                }
            }
            cmd = strtok_r(NULL, ";", &save_cmd);
        }
    }
    return 0;
}
