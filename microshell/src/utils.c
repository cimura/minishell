#include "utils.h"

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

char	*ft_strndup(const char *str, size_t n)
{
	char	*result;
	size_t	str_len;
	size_t	i;

	i = 0;
	str_len = ft_strlen((char *)str);
	if (n < str_len)
		result = malloc(sizeof(char) * (n + 1));
	else
		result = malloc(sizeof(char) * (str_len + 1));
	if (result == NULL)
		return (NULL);
	while (str[i] != '\0' && n > i)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
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

int	white_space(char check_chr)
{
	if (check_chr == ' ' || check_chr == '\t' || check_chr == '\n' || \
		check_chr == '\v' || check_chr == '\f' || check_chr == '\r')
		return (1);
	else
		return (0);
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
