#include "micro.h"

void  env(char **command, char **envp)
{
  pid_t pid = fork();
            if (pid == 0)
            {
                execve("/usr/bin/env", command, envp);
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