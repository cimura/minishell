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
        judge_command(command, envp);
        free_command(command);
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
  else if ((strcmp(command[0], "cd") == 0) && command[1])
    cd(command[1]);
  else if (strcmp(command[0], "echo") == 0)
    echo(command, envp);
  else if (strcmp(command[0], "env") == 0)
    env(command, envp);
  else if (strcmp(command[0], "ls") == 0)
    ls(command, envp);
  else if (strcmp(command[0], "pwd") == 0)
    pwd();
  else
    printf("input is '%s'\n", command[0]);
}

