#include "pipex.h"

size_t ft_strlen(const char *str)
{
	int i;
	i = 0;
	while (str[i])
		i++;
	return i;
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
