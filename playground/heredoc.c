#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*line;

	line = readline("heredoc> ");
	if (line == NULL)
		return (1);
	printf("line = %s\n", line);
	free(line);
	line = NULL;
	return (0);
}
