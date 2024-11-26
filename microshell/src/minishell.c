/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:02:58 by cimy              #+#    #+#             */
/*   Updated: 2024/11/26 19:37:17 by ttakino          ###   ########.fr       */
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

#define CONTINUE 3

static	void	clear_exit(t_env *env_lst, t_token *token, int exit_status)
{
	env_lstclear(&env_lst);
	token_lstclear(&token);
	exit(exit_status);
}

static int	no_pipe_exit(t_env *env_lst, t_token *token, int *status)
{
	if (token->command_line[0] != NULL &&
		ft_strncmp(token->command_line[0], "exit", 5) == 0 && token->next == NULL)
	{
		if (ft_exit(&token->command_line[1], status) == 1)
		{
			token_lstclear(&token);
			return (CONTINUE);
		}
		else
			clear_exit(env_lst, token, *status);
	}
	return (0);
}

int	pass_token_to_expand(t_env *env_lst, t_token *per_pipe, int end_status)
{
	int		i;
	char	*expand;
	while (per_pipe != NULL)
	{
		i = 0;
		while (per_pipe->command_line[i] != NULL)
		{
			if (per_pipe->command_line[i + 1] != NULL
				&& ft_strncmp(per_pipe->command_line[i], "<<", 3) == 0)
			{
				i += 2;
				continue ;
			}
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

static int	preprocess_command(t_env *env_lst, t_token **token, char *line, int *status)
{
	int	syntax_result;

	syntax_result = 0;
	if (check_syntax_before_lexer(line) == 1)
	{
		*status = 2;
		free(line);
		return (CONTINUE);
	}
	char *expanded = expand_env_variable(env_lst, line, *status);
	*token = lexer(expanded, &syntax_result);
	if (*token == NULL)
		clear_exit(env_lst, *token, 1);
	if (syntax_result == CONTINUE)
		return (CONTINUE);
	if (pass_token_to_expand(env_lst, *token, *status) != 0)
		clear_exit(env_lst, *token, 1);
	syntax_result = check_syntax(*token, env_lst);
	if (syntax_result != 0)
	{
		*status = syntax_result;
		token_lstclear(token);
		return (CONTINUE);
	}
	return (0);
}

static int	process_input_line(char **line)
{
	*line = readline("minishell> ");
	if (*line == NULL)
	{
		printf("exit\n");
		exit(1);
	}
	if (ft_strlen(*line) == 0)
	{
		free(*line);
		return (CONTINUE);
	}
	else if (ft_strlen(*line) > 0)
		add_history(*line);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;
	t_env	*env_lst;
	t_token	*token;
	char	*line;
	int		status;
	
	ft_signal();
	status = 0;
	env_lst = create_env_lst(envp);
	while (1)
	{
		if (process_input_line(&line) == CONTINUE)
			continue ;
		if (preprocess_command(env_lst, &token, line, &status) == CONTINUE)
			continue ;
		if (no_pipe_exit(env_lst, token, &status) == CONTINUE)
			continue ;
		if (execute_command_line(token, env_lst, &status) == 1)
			clear_exit(env_lst, token, 1);
	}
	env_lstclear(&env_lst);
	return (status);
}
