#include "util.h"
#include <stdlib.h>
#include <stdio.h>

void	ft_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	free_ptr_array(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
}

// Debug
void	print_char_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
}
