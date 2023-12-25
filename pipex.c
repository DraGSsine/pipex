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
	perror("Error opening file");
	exit(EXIT_FAILURE);
}

void excution(char *path, char **commands, char **env)
{
	if (execve(path, commands, env) == -1)
		exit(127);
}

char *format_awk(char *awk)
{
	int left = 0;
	int right = ft_strlen(awk);

	while (awk[left] != '\'')
		left++;
	while (awk[right] != '\'')
		right--;
	right = right - left;
	return (ft_substr(awk, ++left, --right));
}

void second_command(char **argv, int fds[], char **env)
{
	int fd;
	char **second_commands;
	char *path;

	fd = open(argv[4], O_RDWR | O_CREAT, 0666);
	dup2(fd, 1);
	close(fd);
	dup2(fds[0], 0);
	close(fds[1]);
	close(fds[0]);
	second_commands = ft_split(argv[3], ' ');
	path = validate_path(second_commands[0], env);
	if (!second_commands || !path)
		exit(17);
	excution(path, second_commands, env);
}

void first_command(char **argv, int fds[], char **env)
{
	int fd;
	char **first_commands;
	char *path;

	fd = open(argv[1], O_RDWR | O_CREAT, 0666);
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
int main(int argc, char **argv, char **env)
{
	int pid;
	int fds[2];

	if (argc != 5)
		exit(127);
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
	return (0);
}
