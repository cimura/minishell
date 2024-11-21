#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

void	free_ptr_array(char **ptr)
{
	int	i;

	if (ptr == NULL)
		return ;
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

int	count_char_array_words(char **ptr)
{
	int	c;

	c = 0;
	while (ptr[c] != NULL)
	{
		c++;
	}
	return (c);
}

void	d_print_char_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		fprintf(stderr, "%s\n", array[i]);
		i++;
	}
}
