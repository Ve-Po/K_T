#include "./inc/shell.hpp" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int BUFFER = 4096;

int main() {
  while (1) {
    const int size = BUFFER;
    char string[size];
    printf("Enter command: ");
    if (fgets(string, size, stdin) == NULL) {
      return -1;
    }
    int a = 0;
    char **cmd = parse_line(string, &a);
    char ***cms = parse_command(cmd, &a);
    exec_cmd(cms);
    free_t(cmd);
    free_tt(cms);
  }
  return 0;
}