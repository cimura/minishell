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

        if (command == NULL)
        {
            printf("exit\n");
            break;
        }
        judge_command(command, envp);
        if (strlen(line) > 0)
            add_history(line);
        free(line); // Free memory allocated by readline
    }
    return 0;
}

void  judge_command(char **command, char **envp)
{
  if (strcmp(command[0], "cat") == 0)
    cat(command, envp);
  else if (strcmp(command[0], "cd") == 0)
    cd(command, envp);
  else if (strcmp(command[0], "echo") == 0)
    echo(command, envp);
  else if (strcmp(command[0], "env") == 0)
    env(command, envp);
  else if (strcmp(command[0], "ls") == 0)
    ls(command, envp);
  else if (strcmp(command[0], "pwd") == 0)
    pwd(command, envp);
  else
    printf("input is '%s'\n", command[0]);
}