#include "exec.h"

int	execute_command_line(t_token *token)
{
	while (token != NULL)
	{
		// もしbuiltinコマンドの場合はforkは必要ない
		if (is_builtin(token->command_line))
			builtin_command(token);
		else
			command(token);
		token = token->next;
	}
}

int	main() {
	char	*command_line = "cat Makefile| grep all > outfile|";
	t_token	*token;

	token = ft_lexer(command_line);
	// while (token != NULL)
	// {
	// 	ft_print_commands(token->command_line);
	// 	printf("\n");
	// 	token = token->next;
	// }
}