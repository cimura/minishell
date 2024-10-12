#include "micro.h"

// cat Makefile > outなどのリダイレクトに対応させる
// line --->    <command> <redirect> <file>

void	redirect(char *line, char **envp)
{
	// split

	char **command_line = ft_split(line, '>');
	char **paths = setup_paths(envp);

	char *command = ft_strtrim(command_line[0], " \t\n");
	char *file = ft_strtrim(command_line[1], " \t\n");

	// printf("file -> %s\n", file);

	pid_t	pid = fork();
	if (pid == 0)
	{
		int fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);

		// 空白でsplitして渡してあげる
		char **space_split = ft_split(command, ' ');
		// printf("command => %s\n", command);
		char *executable_path = get_exec_path(paths, space_split, envp);
		// printf("executable path => %s\n", executable_path);
		execve(executable_path, space_split, envp);
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
		// exit(EXIT_SUCCESS);
	}
}