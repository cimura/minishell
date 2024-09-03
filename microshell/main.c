#include "micro.h"

int main(int argc, char **argv, char **envp)
{
  (void)argv;
  (void)argc;
  char *line = NULL;

    while (1)
    {
        line = readline("minishell> ");
        char **command = ft_split(line, ' ');

        if (line == NULL)
        {
            printf("exit\n");
            break;
        }
        if (strlen(line) > 0)
            add_history(line);

        if (strcmp(command[0], "ls") == 0)
        {
          ls(command, envp);
        }
        else
            printf("input is '%s'\n", line);
        free(line); // Free memory allocated by readline
    }

    return 0;
}
