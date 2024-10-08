#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

volatile sig_atomic_t e_flag = 0;

void	sig_c(int sig)
{
	e_flag = 1;
	printf("I get a SIGINT\n");
}

int main() {
	signal(SIGINT, sig_c);
	while (!e_flag) {}
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}
