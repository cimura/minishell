#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]) {
	char *cmd1[] = {"cat","-n", "infile", "|", NULL};
	// char **cmd2 = {"ls", NULL};
	// char **cmd3 = {"ls", NULL};

	// execve("/bin/ls", cmd1, envp);
	if (execve("/bin/cat", cmd1, envp) == -1)
		printf("failed execve\n");
}
