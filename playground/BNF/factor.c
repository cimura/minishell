#include "bnf.h"

int	factor(const char *pc, const char **endp)
{
	*endp = pc;

	while (**endp != '\0')
	{
		if (**endp == '(')
		{
			// (は飛ばす
			*endp += 1;

			// ()内の値
			int	inner_value = expr(pc, endp);
			
			while (1)
			{
				if (')' == **endp)
					break ;
				*endp += 1;
			}

			pc = *endp + 1;
			return (inner_value + expr(pc, endp));
		}
		else
			return (digit(pc, endp));
	}
	return (-1);
}
