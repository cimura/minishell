#include "micro.h"

void free_command(char **command)
{
    for (int i = 0; command[i] != NULL; i++)
    {
        free(command[i]);
    }
    free(command);  // 最後に配列自体を解放
}

bool  include_redirect(char *line)
{
	char **lists = ft_split(line, ' ');
	
	int i = 0;
	while (lists[i] != NULL)
	{
		if (strcmp(lists[i], "<") == 0)
			return (true);
		i++;
	}
	return (false);
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
        	// <command> <redirect> <command>の実行
        if (include_redirect(line))
	        redirect(line, envp);
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
