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
	perror("comand not found");
	exit(EXIT_FAILURE);
}

void excution(char *path, char **commands, char **env)
{
	if (execve(path, commands, env) == -1)
		exit(EXIT_FAILURE);
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

void second_command(int argc, char **argv, int fds[], char **env)
{
	int fd;
	char **second_commands;
	char *path;

	fd = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (fd == -1)
		printf("error opning file 2");
	dup2(fd, 1);
	close(fd);
	dup2(fds[0], 0);
	close(fds[1]);
	close(fds[0]);
	second_commands = ft_split(argv[argc - 2], ' ');
	path = validate_path(second_commands[0], env);
	if (!second_commands || !path)
		exit(EXIT_FAILURE);
	excution(path, second_commands, env);
}

void first_command(char **argv, int fds[], char **env)
{
	int fd;
	char **first_commands;
	char *path;

	fd = open(argv[1], O_RDWR | O_CREAT, 0666);
	if (fd == -1)
		printf("error opning file 1");
	dup2(fd, 0);
	close(fd);
	dup2(fds[1], 1);
	close(fds[1]);
	close(fds[0]);
	first_commands = ft_split(argv[2], ' ');
	path = validate_path(first_commands[0], env);
	if (!first_commands || !path)
		exit(EXIT_FAILURE);
	excution(path, first_commands, env);
}
void middle_commnad(char *argv, int fds[], char **env, int fds2[])
{
	char **first_commands;
	char *path;

	dup2(fds[0], 0);
	close(fds[0]);
	close(fds[1]);

	dup2(fds2[1], 1);
	close(fds2[0]);
	close(fds2[1]);

	first_commands = ft_split(argv, ' ');
	path = validate_path(first_commands[0], env);
	if (!first_commands || !path)
		exit(EXIT_FAILURE);
	excution(path, first_commands, env);
}
void handdle_middle_commands(char **argv , int argc ,int fds2[] ,int fds[], char **env)
{
	int i;
	int pid;

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
int main(int argc, char **argv, char **env)
{
	int pid;
	int fds[2];
	int fds2[2];
	int i;

	i = 2;
	if (argc < 5)
		exit(EXIT_FAILURE);
	pipe(fds);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
		first_command(argv, fds, env);

	handdle_middle_commands(argv,argc,fds2,fds,env);

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
		second_command(argc, argv, fds, env);
	return 0;
}
