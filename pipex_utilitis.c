#include "pipex.h"

size_t ft_strlen(const char *str)
{
	int i;
	i = 0;
	while (str[i])
		i++;
	return i;
}
static size_t	count_words(const char *str, char sp)
{
	size_t	nb_strings;

	nb_strings = 0;
	while (*str)
	{
		if (*str != sp)
		{
			while (*str != '\0' && *str != sp)
				str++;
			nb_strings++;
		}
		if (*str)
			str++;
	}
	return (nb_strings);
}

static const char	*charcopy_until_char(char **dest, const char *src, char c)
{
	const char	*start;
	size_t		len;
	char		*d;
	const char	*s;

	len = 0;
	while (*src == c)
		src++;
	start = src;
	while (*src && *src != c)
		src++;
	len = src - start;
	*dest = malloc(len + 1);
	if (!*dest)
		return (NULL);
	d = *dest;
	s = start;
	while (s < src)
	{
		*d++ = *s++;
	}
	*d = '\0';
	return (src);
}
int	ft_strstr(char *str, char *to_find)
{
	int i;
	int j;

	i = 0;
	if(!str || !to_find)
		return (0);
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (to_find[j + 1] == '\0')
			{
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

char	**ft_split(const char *s, char c)
{
	char	**strs;
	size_t	nb_strings;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	nb_strings = count_words(s, c);
	strs = malloc((nb_strings + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	strs[nb_strings] = NULL;
	while (i < nb_strings)
	{
		s = charcopy_until_char(strs + i, s, c);
		if (!s)
		{
			while (i > 0)
				free(strs[--i]);
			free(strs);
			return (NULL);
		}
		i++;
	}
	return (strs);
}
int	ft_strcmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n < 1)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
	{
		i++;
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr_str;
	size_t	i;
	size_t	x;

	i = 0;
	x = 0;
	if (!s1 || !s2)
		return (NULL);
	ptr_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr_str)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		ptr_str[i] = s1[i];
		i++;
	}
	while (x < ft_strlen(s2))
	{
		ptr_str[i] = s2[x];
		x++;
		i++;
	}
	ptr_str[i] = '\0';
	return (ptr_str);
}
