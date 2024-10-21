#include "exec.h"

int	main() {
	char	*command_line = "cat Makefile| grep all";
	t_token	*token;

	token = ft_lexer(command_line);
	
}