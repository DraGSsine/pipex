#include "pipex.h"

// char *format_awk(char *awk)
// {
// 	int left = 0;
// 	int right = ft_strlen(awk);

// 	while (awk[left] != '\'')
// 		left++;
// 	while (awk[right] != '\'')
// 		right--;
// 	right = right - left;
// 	return (ft_substr(awk, ++left, --right));
// }

int main()
{
	//"input grep Hello | awk '{count++} END {print count}' hgjhjg "
	char *awk[3];
	awk[0] = "awk";
	awk[1] = "{count++} END {print count}";
	awk[2] = NULL;
	int fd = open("file1.txt",O_RDONLY);
	if(fd == -1)
		perror("invalid fd");
	dup2(fd,0);
	close(fd);
	execve("/usr/bin/awk",awk,NULL);
}
