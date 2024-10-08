 #include  <unistd.h>

int main(int ac, char **av, char **envp) {
 execve("/bin/bash", av, envp);
}
