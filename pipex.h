#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

char    **ft_split(const char *s, char c);
char    *ft_strjoin(char const *s1, char const *s2);
size_t  ft_strlen(const char *str);
int     ft_strstr(char *str, char *to_find);
char	*ft_substr(char *s, size_t start, size_t len);
