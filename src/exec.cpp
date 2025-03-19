#include "../inc/shell.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h> 
#include <string.h>

void exec_cmd(char ***cmd) {
    if (cmd == NULL) return;


    pid_t pid;
    int fds[2];
    int fd_in = 0;
    int i = 0;

    while (cmd[i] != NULL) {
        if (cmd[i + 1] != NULL) {
            if (pipe(fds) == -1) {
                perror("pipe failed");
                return; 
            }
        }

        pid = fork();
        if (pid < 0) {
            perror("fork failed");
            return;
        } else if (pid == 0) {
            if (i > 0) {
                if (dup2(fd_in, STDIN_FILENO) == -1) {
                    perror("dup2 failed");
                    exit(1); 
                }
                close(fd_in);
            }

            if (cmd[i + 1] != NULL) {
                if (dup2(fds[1], STDOUT_FILENO) == -1) {
                    perror("dup2 failed");
                    exit(1);
                }
                close(fds[1]);
                close(fds[0]);
            }

            execvp(cmd[i][0], cmd[i]);
            perror("execvp failed");
            exit(1); 
        } else {
            if (i > 0) {
                close(fd_in);
            }

            if (cmd[i + 1] != NULL) {
                close(fds[1]);
                fd_in = fds[0];
            }
            int status;

            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid error");
            }
            else if (WIFEXITED(status)) {
                printf("Ret code: %d\n", WEXITSTATUS(status));
            }
            i++;
        }
    }

    if (fd_in != 0) {
        close(fd_in);
    }
}