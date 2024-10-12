#include "bnf.h"

char	*push_back(char *num_array, int to_add)
{
	char *ret;
	int	i = 0;
	while (num_array[i] != '\0')
		i++;
	ret = malloc(i + 1);
	i = 0;
	while (num_array[i] != '\0')
	{
		ret[i] = num_array[i];
		i++;
	}
	ret[i] = to_add;
	return (ret);
}

int	digit(const char *pc, const char **endp)
{
	char *number;

	*endp = pc;

	while (1)
	{
		if (isdigit(**endp))
		{
			number = push_back(number, **endp);
			*endp += 1;
		}
		else if ('_' == **endp || isalnum(**endp))
			return (variable(pc, endp));
		else
			break ;
	}

	if (number == NULL)
		return (0);
	else
		return (atoi(number));
}
