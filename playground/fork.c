#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void child(void)
{
	sleep(2);
	printf("child exit\n");
	exit(0);
}

int main() {
	pid_t pid = fork();
	if (pid == 0)
		child();
	else
	{
		printf("Parent\n");
		return (0);
	}
}
