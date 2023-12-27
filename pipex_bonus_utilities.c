/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utilities.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchen <youchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:18:53 by youchen           #+#    #+#             */
/*   Updated: 2023/12/27 10:09:30 by youchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_env_paths(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strstr(env[i], "PATH"))
		{
			return (ft_split(env[i++] + 5, ':'));
		}
		i++;
	}
	return (NULL);
}

char	*validate_path(char *command, char **env)
{
	int		i;
	char	*cm;
	char	*full_path;
	char	**paths;

	paths = get_env_paths(env);
	i = 0;
	cm = ft_strjoin("/", command);
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], cm);
		if (access(full_path, X_OK) != -1)
			return (full_path);
		i++;
	}
	perror("comand not found");
	exit(EXIT_FAILURE);
}

void	handdle_middle_commands(char **argv, int fds2[], int fds[], char **env)
{
	int	i;
	int	pid;
	int	argc;

	argc = count_args(argv);
	i = 2;
	while (i < (argc - 3))
	{
		pipe(fds2);
		pid = fork();
		if (pid == 0)
			middle_commnad(argv[i + 1], fds, env, fds2);
		dup2(fds2[0], fds[0]);
		close(fds2[0]);
		close(fds2[1]);
		i++;
	}
}

void	handdle_here_doc(char *limiter)
{
	int		fd;
	char	*line;

	fd = open("tmp.txt", O_RDWR | O_APPEND | O_CREAT, 0666);
	if (fd == -1)
		exit(EXIT_FAILURE);
	line = read_line(0);
	while (line)
	{
		if (ft_strstr(line, limiter))
			break ;
		write(fd, line, ft_strlen(line));
		line = read_line(0);
	}
	close(fd);
}
