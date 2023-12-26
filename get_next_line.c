#include "get_next_line.h"
char	*get_lerl_string(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n')
		i++;
	return (rl_substr(str, ++i, rl_strlen(str)));
}

char	*get_the_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n')
		i++;
	return (rl_substr(str, 0, ++i));
}
#include <stdio.h>
char	*read_and_process_buffer(int fd, char *lerl)
{
	char	*buffer;
	int		r;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	r = read(fd, buffer, BUFFER_SIZE);
	while (r > 0)
	{
		buffer[r] = '\0';
		lerl = rl_strjoin(lerl, buffer);
		if (!lerl)
			return (free(buffer), NULL);
		if (rl_strchr(buffer, '\n'))
			break ;
		r = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (r == -1)
	{
		free(lerl);
		lerl = NULL;
		return (NULL);
	}
	return (lerl);
}

char	*get_next_line(int fd)
{
	static char	*lerl;
	char		*line;
	char		*ret;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	lerl = read_and_process_buffer(fd, lerl);
	if (!lerl)
		return (NULL);
	if (rl_strchr(lerl, '\n'))
	{
		line = get_the_line(lerl);
		ret = get_lerl_string(lerl);
		return (free(lerl), lerl = NULL, lerl = ret, line);
	}
	if (*lerl)
	{
		line = rl_strjoin(line, lerl);
		return (free(lerl), lerl = NULL, line);
		return (lerl);
	}
	return (free(lerl), lerl = NULL, NULL);
}
