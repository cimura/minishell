#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void	grand_child(void)
{
	printf("grand_child\n");
}

void child(void)
{
	pid_t pid = fork();
	if (pid == 0)
		grand_child();
	else
	{
		wait(NULL);
		printf("child\n");
		exit (0);
	}
	exit(0);
}

int main() {
	pid_t pid = fork();
	if (pid == 0)
		child();
	else
	{
		wait(NULL);
		printf("Parent\n");
		return (0);
	}
}
