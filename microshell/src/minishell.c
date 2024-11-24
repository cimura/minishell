/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:02:58 by cimy              #+#    #+#             */
/*   Updated: 2024/11/24 15:14:23 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env_lst.h"
#include "exec.h"
#include "expander.h"
#include "lexer.h"
#include "signal_handler.h"
#include "utils.h"
#include "syntax.h"
#include "libft.h"

int	pass_token_to_expand(t_env *env_lst, t_token *per_pipe, int end_status)
{
	int		i;
	char	*expand;
	while (per_pipe != NULL)
	{
		i = 0;
		while (per_pipe->command_line[i] != NULL)
		{
			expand = expander(env_lst, per_pipe->command_line[i], end_status);
			if (expand == NULL)
				return (1);
			free(per_pipe->command_line[i]);
			per_pipe->command_line[i] = expand;
			i++;
		}
		per_pipe = per_pipe->next;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_lst;
	t_token	*token;
	char	*line;
	int		syntax_result;
	int		status = 0;

	//int pure_STDIN = dup(STDIN_FILENO);

	(void)argv;

	ft_signal();
	if (argc > 2)
		return (printf("No need arguments\n"), 1);
	env_lst = create_env_lst(envp);
	if (env_lst == NULL)
		return (1);

	while (1)
	{
	//	dup2(pure_STDIN, STDIN_FILENO);
		line = readline("minishell> ");
		if (line == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue ;
		}
		else if (ft_strlen(line) > 0)
			add_history(line);

		if (check_syntax_before_lexer(line) == 1)
		{
		  status = 2;
		  free(line);
		  continue ;
		}
		token = lexer(line);
		if (token == NULL)
			return (env_lstclear(&env_lst), 1);
		if (pass_token_to_expand(env_lst, token, status) != 0)
		{
			env_lstclear(&env_lst);
			token_lstclear(&token);
			return (1);
		}
		syntax_result = check_syntax(token, env_lst);
		if (syntax_result != 0)
		{
			status = syntax_result;
			token_lstclear(&token);
			continue ;
		}
		if (stash_token_empty_ptrs(token) == 1)
		{
			env_lstclear(&env_lst);
			token_lstclear(&token);
			return (1);
		}


		// debug
		//d_print_token_lst(token);

		if (token->command_line[0] != NULL &&
			ft_strncmp(token->command_line[0], "exit", 5 ) == 0 && token->next == NULL)
		{
			if (ft_exit(&token->command_line[1], &status) == 1)
			{
				token_lstclear(&token);
				continue ;
			}
			else
			{
				token_lstclear(&token);
				break ;
			}
		}
		if (execute_command_line(token, env_lst, &status) == 1)
		{
			// system error
			env_lstclear(&env_lst);
			token_lstclear(&token);
			return (1);
		}
		token_lstclear(&token);
		}
	env_lstclear(&env_lst);
	return (status);
}


// int main(int argc, char **argv, char **envp)
// {
// 	(void)argv;
// 	(void)argc;
// 	char *line = NULL;

// 		while (1)
// 		{
// 				line = readline("minishell> ");

// 				if (!line)
// 				{
// 					printf("exit\n");
// 					break;
// 				}
// 				if (strlen(line) == 0)
// 				{
// 					free(line);
// 					continue;
// 				}
// 					// <command> <redirect> <command>の実行
// 				if (include_redirect(line))
// 					redirect(line, envp);
// 				else
// 				{
// 					char **command = ft_split(line, ' ');

// 					if (command == NULL)
// 					{
// 						free(line);
// 							printf("exit\n");
// 							break;
// 					}
// 					do_command(command, envp);
// 					free_command(command);
// 				}
// 				if (strlen(line) > 0)
// 						add_history(line);
// 				free(line); // Free memory allocated by readline
// 		}
// 		return 0;
// }
