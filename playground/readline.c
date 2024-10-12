#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char **argv, char **envp)
{
    char *line = NULL;

    while (1)
    {
        line = readline("minishell> ");
        if (line == NULL)
        {
            printf("exit\n");
            break;
        }

        if (strlen(line) > 0)
        {
            add_history(line);
        }

        if (strcmp(line, "ls") == 0)
        {
            pid_t pid = fork();
            if (pid == 0)
            {
                // Child process
                char *command[] = {"/bin/ls", NULL};
                execve("/bin/ls", command, envp);
                // If execve fails, exit with an error code
                perror("execve failed");
                exit(EXIT_FAILURE);
            }
            else if (pid > 0)
            {
                // Parent process
                int status;
                waitpid(pid, &status, 0); // Wait for the child to complete
            }
            else
            {
                perror("fork failed");
            }
        }
        else
        {
            printf("input is '%s'\n", line);
        }

        free(line); // Free memory allocated by readline
    }

    return 0;
}
