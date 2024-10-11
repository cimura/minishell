#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char	*push_back(char *num_array, int to_add);
int	expr(const char *pc, const char **endp);
int	term(const char *pc, const char **endp);
int	factor(const char *pc, const char **endp);
int	digit(const char *pc, const char **endp);
int	variable(const char *pc, const char **endp);
void	print(int expected_value, int calculated_value);
