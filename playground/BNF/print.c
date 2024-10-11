#include "bnf.h"

void	print(int expected_value, int calculated_value)
{
	printf("Result: %s\n"
		"	-- ExpectedValue: %d, CalculatedValue: %d\n",
		(calculated_value == expected_value) ? "True" : "False",
		expected_value, calculated_value);
}
