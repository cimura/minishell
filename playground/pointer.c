#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	f(char **line)
{
	char *result = malloc(6);
	result = memcpy(result, "hello\0", 6);
	*line = result;
	// printf("result: %s\n", line);
}

int	main() {
	char **ptr = malloc(sizeof(char *) * 3);
	ptr[0] = "echo";
	ptr[1] = "PATH";
	ptr[2] = NULL;
	
	f(&ptr[1]);
	while (*ptr)
	{
		printf("%s\n", *ptr);
		ptr++;
	}
}
