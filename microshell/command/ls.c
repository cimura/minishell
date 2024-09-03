#include "micro.h"

void  ls(char **command, char **envp)
{
  pid_t pid = fork();
            if (pid == 0)
            {
                execve("/bin/ls", command, envp);
                perror("execve failed");
                exit(EXIT_FAILURE);
            }
            else if (pid > 0)
            {
                // Parent process
                int status;
                waitpid(pid, &status, 0);
            }
            else
            {
                perror("fork failed");
            }
}

void  echo(char **command, char **envp)
{
  pid_t pid = fork();
            if (pid == 0)
            {
                execve("/bin/echo", command, envp);
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