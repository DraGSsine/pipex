/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchen <youchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:27:50 by youchen           #+#    #+#             */
/*   Updated: 2023/12/27 22:37:53 by youchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	second_command(int argc, char **argv, int fds[], char **env)
{
	int		fd;
	char	**second_commands;
	char	*path;

	fd = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0666);
	second_commands = ft_split(argv[argc - 2], ' ');
	path = validate_path(second_commands[0], env);
	if (!second_commands || !path || fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd, 1);
	close(fd);
	dup2(fds[0], 0);
	close(fds[1]);
	close(fds[0]);
	if (execve(path, second_commands, env) == -1)
		exit(EXIT_FAILURE);
}

void	first_command(char **argv, int fds[], char **env)
{
	int		fd;
	char	**first_commands;
	char	*path;

	fd = open(argv[1], O_RDONLY);
	if (ft_strstr(argv[1], "here_doc"))
	{
		fd = open("/tmp/tmp.txt", O_RDWR | O_CREAT, 0666);
		first_commands = ft_split(argv[3], ' ');
	}
	else
		first_commands = ft_split(argv[2], ' ');
	if (!first_commands || fd == -1)
		exit(EXIT_FAILURE);
	path = validate_path(first_commands[0], env);
	dup2(fd, 0);
	close(fd);
	dup2(fds[1], 1);
	close(fds[0]);
	close(fds[1]);
	if (execve(path, first_commands, env) == -1)
		exit(EXIT_FAILURE);
}

void	middle_commnad(char *argv, int fds[], char **env, int fds2[])
{
	char	**first_commands;
	char	*path;

	dup2(fds[0], 0);
	close(fds[0]);
	close(fds[1]);
	dup2(fds2[1], 1);
	close(fds2[0]);
	close(fds2[1]);
	first_commands = ft_split(argv, ' ');
	if (!first_commands)
		exit(EXIT_FAILURE);
	path = validate_path(first_commands[0], env);
	if (execve(path, first_commands, env) == -1)
		exit(EXIT_FAILURE);
}

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	return (pid);
}

int	main(int argc, char **argv, char **env)
{
	int	fds[2];
	int	fds2[2];
	int	i;

	if (access("/tmp/tmp.txt", F_OK) == 0)
		unlink("/tmp/tmp.txt");
	i = 2;
	if (argc < 5)
		exit(EXIT_FAILURE);
	pipe(fds);
	if (ft_strstr(argv[1], "here_doc"))
		handdle_here_doc(argv[2]);
	if (ft_fork() == 0)
		first_command(argv, fds, env);
	handdle_middle_commands(argv, fds2, fds, env);
	if (ft_fork() == 0)
		second_command(argc, argv, fds, env);
	close(fds[0]);
	close(fds[1]);
	close(fds2[0]);
	close(fds2[1]);
	while (wait(NULL) != -1)
		;
	return (0);
}
