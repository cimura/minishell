#include "micro.h"

bool	is_builtin(char **command)
{
	(void)command;
	return (false);
}

void	do_builtin(char **command)
{
	(void)command;
}

void	execute_command(char **command, char **envp)
{
	pid_t	pid;
	char **paths = setup_paths(envp);

	if (is_builtin(command))
		do_builtin(command);

	pid = fork();

	// <command>の実行
	if (pid == 0)
	{
		char *executable_path = get_exec_path(paths, command, envp);
		execve(executable_path, &command[0], envp);
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}

void  do_command(char **command, char **envp)
{
	// if (check_error(command))
	// 	print_error(command);
	// else
	// {
		execute_command(command, envp);
	// }
}