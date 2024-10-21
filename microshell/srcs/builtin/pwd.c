#include "builtin.h"

void  pwd(void)
{
	char *cwd;

	//cwd = malloc(100);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd failed");
		return ;
	}
	printf("%s\n", cwd);
	free(cwd);
}
