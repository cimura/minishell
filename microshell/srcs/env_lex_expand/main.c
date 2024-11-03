#include "../env/env_lst.h"
#include "../expander/expander.h"
#include "../lexer/lexer.h"

#define RESET   "\033[0m"   // リセット
#define RED     "\033[31m"  // 赤
#define GREEN   "\033[32m"  // 緑
#define YELLOW  "\033[33m"  // 黄
#define BLUE    "\033[34m"  // 青

static void	print_commands(char **commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		printf("%s\n", commands[i++]);
	}
}

static void	Print(t_token *token)
{
	while (token != NULL)
	{
		print_commands(token->command_line);
		token = token->next;
		if (token != NULL)
			printf("\tnext...\n");
	}
}

int	pass_token_to_expand(t_env *env_lst, t_token *per_pipe)
{
	int	i;
	while (per_pipe != NULL)
	{
		i = 0;
		while (per_pipe->command_line[i] != NULL)
		{
			per_pipe->command_line[i] = expander(env_lst, per_pipe->command_line[i]);
			i++;
		}
		per_pipe = per_pipe->next;
	}
	return (0);
}

// void	test_main(t_env *env_lst)
// {
// 	t_token	*token;
// 	char	*input;

// 	input = "echo hello$USER >cat out| ls  <<INFILE";
// 	token = lexer(input);
// 	assert(strcmp())
// }

int	main(int argc, char **argv, char **envp)
{
	t_env	*head;
	t_env	*env_lst;
	t_token	*token;
	(void)argv;
	(void)argc;


	env_lst = create_env_lst(envp);
	head = env_lst;
	// test_main(env_lst);
	token = lexer("echo hello$USER >cat out| ls  <<INFILE");
	if (pass_token_to_expand(env_lst, token) == 1)
		return (1);
	printf(GREEN"\t--- Result---\n\n"RESET);
	Print(token);
	env_lstclear(&head, free_env_node);
}
