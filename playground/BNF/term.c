#include "bnf.h"

int	term(const char *pc, const char **endp)
{
	int	left = factor(pc, endp);
	while (1)
	{
		if ('*' == **endp)
		{
			int right = term(*endp + 1, endp);
			return (left * right);
		}
		else if ('/' == **endp)
		{
			int right = term(*endp + 1, endp);
			return (left / right);
		}
		else if ('%' == **endp)
		{
			int right = term(*endp + 1, endp);
			return (left % right);
		}
		else if (isspace(**endp))
			*endp += 1;
		else
			break ;
	}
	return (left);
}
