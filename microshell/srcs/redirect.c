#include "micro.h"

// cat Makefile > outなどのリダイレクトに対応させる
// line --->    <command> <redirect> <file>

void	redirect(char *line, char **envp)
{
	// split

	char **command_line = ft_split(line, '>');
	char **paths = setup_paths(envp);

	char *command = command_line[0];
	char *file = command_line[1];


	pid_t	pid = fork();
	if (pid == 0)
	{
		int fd = open(file, O_CREAT);
		dup2(fd, STDOUT_FILENO);
		close(fd);

		// 空白でsplitして渡してあげる
		//char **;
		char *executable_path = get_exec_path(paths, &command, envp);
		execve(executable_path, &command, envp);
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}