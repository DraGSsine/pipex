#include "pipex.h"

char **get_env_paths(char **env)
{
	int i;

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
char *validate_path(char *command, char **env)
{
	int i;
	char *cm;
	char *full_path;
	char **paths;

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
	exit(127);
}
void leaks()
{
	system("leaks a.out");
}
void redirect_fds(char *file1)
{
	int fd;
	fd = open(file1, O_RDONLY);
	dup2(fd, 0);
	close(fd);
}
void excution(char *path, char **first_commands, char **env)
{
	if (execve(path, first_commands, env) == -1)
		exit(127);
}
void handdle_second_command()
{
}
int main(int argc, char **argv, char **env)
{
	char **first_commands = NULL;
	char **seconds_commands = NULL;
	char *path;
	int pid;
	int fds[2];
	int fd;

	if (argc != 5)
		exit(127);
	pipe(fds);
	pid = fork();
	if (pid < 0)
		exit(127);
	if (pid == 0)
	{
		fd = open(argv[1], O_RDONLY);
		dup2(fd, 0);
		close(fd);
		dup2(fds[1], 1);
		close(fds[1]);
		close(fds[0]);
		first_commands = ft_split(argv[2], ' ');
		path = validate_path(first_commands[0], env);
		if (!first_commands || !path)
			exit(127);
		excution(path, first_commands, env);
	}
	pid = fork();
	if (pid < 0)
		exit(127);
	if (pid == 0)
	{
		fd = open(argv[4], O_RDWR | O_CREAT , 0666);
		dup2(fd, 1);
		close(fd);
		dup2(fds[0], 0);
		close(fds[1]);
		close(fds[0]);
		seconds_commands = ft_split(argv[3], ' ');
		path = validate_path(seconds_commands[0], env);
		if (!seconds_commands || !path)
			exit(127);
		excution(path, seconds_commands, env);
	}
	return (0);
}
