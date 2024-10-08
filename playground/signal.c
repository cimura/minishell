#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void	nothing(int sig)
{
	printf("\033[2Dnothing\n");
	//exit(0);
}

int main() {
	struct sigaction sa_nothing;
	memset(&sa_nothing, 0, sizeof(sa_nothing));
	//sa_nothing.sa_sigation = nothing;
	//sa_nothing.sa_flags = sa_SIGINFO;
	sa_nothing.sa_handler = nothing;	
	sa_nothing.sa_flags = 0;
	sigaction(SIGINT, &sa_nothing, NULL);
	while (1)
		pause();
}
