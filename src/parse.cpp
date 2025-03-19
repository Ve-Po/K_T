#include "../inc/shell.hpp"  
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **parse_line(char *string, int *num) {
   if (string == NULL || num == NULL) {
        return NULL;
    }
  size_t len = strlen(string);
  if (len > 0 && string[len - 1] == '\n') {
    string[len - 1] = '\0';
  }
  char *str_copy = strdup(string);
  if (str_copy == NULL) {
        perror("strdup (parse_line)");
        return NULL;
    }

  *num = 0;
  char *p = strtok(str_copy, "|");
  while (p != NULL) {
    (*num)++;
    p = strtok(NULL, "|");
  }
  free(str_copy);
  char **mass = (char **)calloc(*num + 1, sizeof(char *));
   if (mass == NULL) {
        perror("calloc (parse_line)");
        return NULL;
    }
  int i = 0;
  p = strtok(string, "|");
  while (p != NULL && i < *num) {
    while (*p == ' ' || *p == '\t') p++;
    char *end = p + strlen(p) - 1;
    while (end > p && (*end == ' ' || *end == '\t')) end--;
    *(end + 1) = '\0';

    mass[i] = strdup(p);
      if (mass[i] == NULL) {
            free_t(mass);
            perror("strdup (parse_line)");
            return NULL;
        }

    i++;
    p = strtok(NULL, "|");
  }
  mass[i] = NULL;

  return mass;
}

char ***parse_command(char **buf, int *num) {
  if (buf == NULL || num == NULL || *num <= 0) {
  
        return NULL;
  }

  char ***command = (char ***)calloc(*num + 1, sizeof(char **));
    if (command == NULL) {
        perror("calloc (parse_command)");
        return NULL;
    }
  for (int i = 0; i < *num; i++) {
    if (buf[i] == NULL) {
      free_tt(command);
      return NULL;
    }
    char *copy1 = strdup(buf[i]);
  if (copy1 == NULL) {
    free_tt(command);
    perror("strdup (parse_command)");
    return NULL;
  }

    int word_count = 0;
    char *p = strtok(copy1, " \t\n");
    while (p != NULL) {
      word_count++;
      p = strtok(NULL, " \t\n");
    }
    free(copy1);
    command[i] = (char **)calloc(word_count + 1, sizeof(char *));
    if (command[i] == NULL) {
            free_tt(command);
            perror("calloc (parse_command)");
            return NULL;
     }
    char *copy2 = strdup(buf[i]);
    if (copy2 == NULL) {
            free_tt(command);
            perror("strdup (parse_command)");
            return NULL;
        }
    int j = 0;
    p = strtok(copy2, " \t\n");
    while (p != NULL && j < word_count) {
      command[i][j] = strdup(p);
      if (command[i][j] == NULL) {
        free(copy2);
        free_tt(command);
        perror("strdup (parse_command)");
        return NULL;
       }
      j++;
      p = strtok(NULL, " \t\n");
    }
    command[i][j] = NULL;
    free(copy2);
  }
  command[*num] = NULL;

  return command;
}

void free_t(char **str) {
  if (str == NULL) {
    return;
  }
  int i;
  for (i = 0; str[i] != NULL; i++) {
    free(str[i]);
  }
  free(str);
}

void free_tt(char ***str) {
  if (str == NULL) {
    return;
  }

  for (int i = 0; str[i] != NULL; i++) {
    for (int j = 0; str[i][j] != NULL; j++) {
      free(str[i][j]);
    }
    free(str[i]);
  }

  free(str);
}