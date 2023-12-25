#include "pipex.h"

int main()
{
	char *awk[2];
	awk[0] = "ls";
	awk[1] = NULL;
	execve("/bin/ls",awk,NULL);
	printf("Hellfffsdfsdfdsfdsfsdfsdfsfsdfsdfdgsdthhygo");
}
