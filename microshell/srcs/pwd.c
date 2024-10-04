#include "micro.h"

void  pwd(void)
{
	char *cwd;

	cwd = malloc(100);
	cwd = getcwd(NULL, 10);
	printf("%s\n", cwd);
}
