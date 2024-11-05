#include "exec.h"

// /bin/cat Makefile > out1 > out2
int count_until_redirection(char **cmdline)
{
  int count = 0;
  while (cmdline[count] != NULL)
  {
    if (ft_strncmp(cmdline[count], ">", 1) == 0
      || ft_strncmp(cmdline[count], ">>", 2) == 0
      || ft_strncmp(cmdline[count], "<", 1) == 0
      || ft_strncmp(cmdline[count], "<<", 2) == 0)
        return (count);
    count++;
  }
  return (count);
}

void	print_commands(char **commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		printf("%s\n", commands[i++]);
	}
}

// static void	Print(t_token *token)
// {
// 	while (token != NULL)
// 	{
// 		print_commands(token->command_line);
// 		token = token->next;
// 		if (token != NULL)
// 			printf("\tnext...\n");
// 	}
// }


// void	test_main(t_env *env_lst)
// {
// 	t_token	*token;
// 	char	*input;

// 	input = "echo hello$USER >cat out| ls  <<INFILE";
// 	token = lexer(input);
// 	assert(strcmp())
// }

// bool  is_builtin(t_token *token)
// {
//   return (ft_strncmp(token->command_line[0], "cd", 3) ||
//           ft_strncmp(token->command_line[0], "echo", 5) ||
//           ft_strncmp(token->command_line[0], "env", 4) ||
//           ft_strncmp(token->command_line[0], "exit", 5));
// }

// void	builtin_command(t_token *token)
// {
// 	if (ft_strncmp(token->command_line[0], "cd", 3))
// 		cd(&token->command_line[1]);
// 	else if (ft_strncmp(token->command_line[0], "echo", 5))
// 		echo(&token->command_line[1]);
// 	else if (ft_strncmp(token->command_line[0], "env", 4))
// 		env(&token->command_line[1]);
// 	else if (ft_strncmp(token->command_line[0], "exit", 5))
// 		exit(&token->command_line[1]);
// 	else if (ft_strncmp(token->command_line[0], "export", 7))
// 		export(&token->command_line[1]);
// 	else if (ft_strncmp(token->command_line[0], "pwd", 4))
// 		pwd(&token->command_line[1]);
// 	else if (ft_strncmp(token->command_line[0], "unset", 6))
// 		unset(&token->command_line[1]);
// }

