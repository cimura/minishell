/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:02:58 by cimy              #+#    #+#             */
/*   Updated: 2024/11/17 18:44:33 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env_lst.h"
#include "exec.h"
#include "expander.h"
#include "lexer.h"
#include "signal_handler.h"
#include "libft.h"

int	g_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_lst;
	t_token	*token;
	char	*line;
	int		status = 0;

	int pure_STDIN = dup(STDIN_FILENO);

	(void)argv;

	ft_signal();
	if (argc > 2)
		return (printf("No need arguments\n"), 1);
	env_lst = create_env_lst(envp);
	if (env_lst == NULL)
		return (1);

	while (1)
	{
		dup2(pure_STDIN, STDIN_FILENO);
		line = readline("minishell> ");
	if (line == NULL)
	{
	  printf("exit\n");
	  break ;
	}
	if (ft_strlen(line) == 0)
	{
	  free(line);
	  continue;
	}
		token = lexer(line);
		if (token == NULL)
			return (env_lstclear(&env_lst, free_env_node), 1);
		if (pass_token_to_expand(env_lst, token, status) != 0)
		{
			env_lstclear(&env_lst, free_env_node);
			token_lst_clear(&token, free_commands);
			return (1);
		}
		if (ft_strncmp(token->command_line[0], "exit", 5 ) == 0 && token->next == NULL)
		{
			if (ft_exit(&token->command_line[1], &status) == 1)
			{
				token_lst_clear(&token, free_commands);
				continue ;
			}
			else
			{
				token_lst_clear(&token, free_commands);
				break ;
			}
		}
		if (execute_command_line(token, env_lst, &status) == -1)
		{
			// system error
			env_lstclear(&env_lst, free_env_node);
			token_lst_clear(&token, free_commands);
			return (1);
		}
		token_lst_clear(&token, free_commands);
	if (ft_strlen(line) > 0)
			add_history(line);
	}
	env_lstclear(&env_lst, free_env_node);
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
