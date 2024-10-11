#include "bnf.h"

int	variable(const char *pc, const char **endp)
{
	char *name;

	*endp = pc;

	while (1)
	{
		if (isdigit(*pc))
		{
			printf("Error. must be number");
			exit(0);
		}
		if (('_' == **endp) || isalnum(**endp))
		{
			name = push_back(name, **endp);
			*endp += 1;
		}
		else if (isspace(**endp))
			*endp += 1;
		else
			break ;
	}

	if (name == NULL)
		return (0);
	else
	{
		// 変数にキーが設定されていない
		return (-1);
	}
}
