#include "pipex.h"

int main()
{
	char *args[] = {"awk","BEGIN { printf "Hello, World"}",NULL};

	execve("/usr/bin/awk",args,NULL);
}

// "awk '{ printf "Hello, World"}'"
