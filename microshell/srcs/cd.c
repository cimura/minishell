#include "micro.h"

void  cd(char *path)
{
	//int ret = chdir(path);
	//printf("return value is %d\n", ret);
	// success -> 0, fail -> -1;
	
	if (chdir(path) != 0)
		perror("chdir failed");
	// free(path);
}
