#include "micro.h"

void	error_exit(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	specific_error(char *command)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	by_path(char *command)
{
	if (command[0] == '/')
	{
		if (access(command, X_OK) != 0)
			error_exit(command);
		else if (access(command, F_OK) != 0)
		{
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			exit(127);
		}
	}
}
