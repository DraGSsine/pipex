#include "get_next_line.h"

size_t rl_strlen(char *s1)
{
	int i;

	i = 0;
	if (s1 == NULL)
		return (0);
	while (s1[i])
	{
		i++;
	}
	return (i);
}

char *rl_substr(char *s, unsigned int start, size_t len)
{
	size_t s_len;
	char *ptr_str;
	size_t i;

	i = 0;
	if (!s)
		return (NULL);
	s_len = rl_strlen(s);
	if (start >= s_len || len == 0)
	{
		ptr_str = malloc(1);
		if (!ptr_str)
			return (NULL);
		ptr_str[0] = '\0';
		return (ptr_str);
	}
	if (start + len > s_len)
		len = s_len - start;
	ptr_str = malloc(len + 1);
	if (ptr_str == NULL)
		return (NULL);
	while (i < len)
		ptr_str[i++] = s[start++];
	ptr_str[len] = '\0';
	return (ptr_str);
}

int rl_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return (1);
		s++;
	}
	if (*s == (char)c)
		return (1);
	return (0);
}

char *rl_strjoin(char *s1, char *buff)
{
	char *ptr_str;
	size_t i;
	size_t x;

	i = -1;
	x = 0;
	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!buff)
		return (NULL);
	ptr_str = malloc(rl_strlen(s1) + rl_strlen(buff) + 1);
	if (!ptr_str)
		return (free(s1), NULL);
	while (++i < rl_strlen(s1))
		ptr_str[i] = s1[i];
	while (x < rl_strlen(buff))
		ptr_str[i++] = buff[x++];
	ptr_str[i] = '\0';
	return (free(s1), ptr_str);
}
