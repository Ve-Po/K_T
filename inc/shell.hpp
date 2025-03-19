#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>
char **parse_line(char *string, int *num);
char ***parse_command(char **buf, int *num);
void exec_cmd(char ***cmd);
void free_tt(char ***str);
void free_t(char **str);

#endif