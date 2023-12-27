/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchen <youchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:29:53 by youchen           #+#    #+#             */
/*   Updated: 2023/12/27 12:31:52 by youchen          ###   ########.fr       */
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
	perror("Error command not found");
	exit(EXIT_FAILURE);
}

void	second_command(char **argv, int fds[], char **env)
{
	int		fd;
	char	**second_commands;
	char	*path;

	fd = open(argv[4], O_RDWR | O_CREAT, 0666);
	second_commands = ft_split(argv[3], ' ');
	path = validate_path(second_commands[0], env);
	if (!second_commands || !path || fd == -1)
		exit(17);
	dup2(fd, 1);
	close(fd);
	dup2(fds[0], 0);
	close(fds[1]);
	close(fds[0]);
	if (execve(path, second_commands, env) == -1)
		exit(127);
}

void	first_command(char **argv, int fds[], char **env)
{
	int		fd;
	char	**first_commands;
	char	*path;

	fd = open(argv[1], O_RDWR);
	first_commands = ft_split(argv[2], ' ');
	path = validate_path(first_commands[0], env);
	if (!first_commands || !path || fd == -1)
		exit(127);
	dup2(fd, 0);
	close(fd);
	dup2(fds[1], 1);
	close(fds[1]);
	close(fds[0]);
	if (execve(path, first_commands, env) == -1)
		exit(127);
}

int	main(int argc, char **argv, char **env)
{
	int	pid;
	int	fds[2];

	if (argc != 5)
		exit(EXIT_FAILURE);
	pipe(fds);
	pid = fork();
	if (pid < 0)
		exit(127);
	if (pid == 0)
		first_command(argv, fds, env);
	pid = fork();
	if (pid < 0)
		exit(127);
	if (pid == 0)
		second_command(argv, fds, env);
	close(fds[0]);
	close(fds[1]);
	while (wait(NULL) != -1)
		;
	return (0);
}
