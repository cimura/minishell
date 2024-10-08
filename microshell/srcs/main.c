#include "micro.h"

void free_command(char **command)
{
    for (int i = 0; command[i] != NULL; i++)
    {
        free(command[i]);
    }
    free(command);  // 最後に配列自体を解放
}

int main(int argc, char **argv, char **envp)
{
  (void)argv;
  (void)argc;
  char *line = NULL;

    while (1)
    {
        line = readline("minishell> ");

        if (!line)
        {
          printf("exit\n");
          break;
        }
        if (strlen(line) == 0)
        {
          free(line);
          continue;
        }
        char **command = ft_split(line, ' ');

        if (command == NULL)
        {
          free(line);
            printf("exit\n");
            break;
        }
        do_command(command, envp);
        free_command(command);
        if (strlen(line) > 0)
            add_history(line);
        free(line); // Free memory allocated by readline
    }
    return 0;
}

bool	is_builtin(char **command)
{

}

void	do_builtin(char **command)
{

}

void	execute_command(char **command, char **envp)
{
	pid_t	pid;

	pid = fork();
	
	// child process
	if (pid == 0)
	{
		execve();
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
}

void  do_command(char **command, char **envp)
{
	if (is_builtin(command))
		do_builtin(command);
	else
	{
		execute_command(command, envp);
	}
}

