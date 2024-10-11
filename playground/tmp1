#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void	child(char **envp)
{
	char *argv[] = {"ls", NULL};
	execve("/bin/ls", argv, envp);
	printf("execve failed\n");
}

int main(int argc, char **argv, char **envp) {
	(void)argc;
	(void)argv;
	pid_t pid;

	pid = fork();
	if (pid == 0)
		child(envp);
	else
		wait(NULL);
	return (0);
}
