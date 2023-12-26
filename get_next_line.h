#ifndef get_next_line_H
#define get_next_line_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

char *rl_strjoin(char *s1, char *buff);
char *rl_substr(char *s, unsigned int start, size_t len);
size_t rl_strlen(char *s1);
char *get_next_line(int fd);
int rl_strchr(char *s, int c);
#endif
