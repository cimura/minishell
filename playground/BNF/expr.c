#include "bnf.h"

int	expr(const char *pc, const char **endp)
{
	// exprのleftはtermしか受け付けない（readme参照）
	int	left = term(pc, endp);

	while (1)
	{
		if ('+' == **endp)
		{
			// '+'の分一個右にずらす
			int right = expr(*endp + 1, endp);
			return (left + right);
		}
		else if ('-' == **endp)
		{
			int right = expr(*endp + 1, endp);
			return (left - right);
		}
		else if (isspace(**endp))
			*endp += 1;
		else
			break ;
	}
	return (left);
}
