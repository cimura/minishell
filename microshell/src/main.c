/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:02:58 by cimy              #+#    #+#             */
/*   Updated: 2024/12/02 13:42:01 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env_lst.h"
#include "exec.h"
#include "expander.h"
#include "parser.h"
#include "signal_handler.h"
#include "utils.h"
#include "syntax.h"
#include "libft.h"

#define CONTINUE 3

static int	no_pipe_exit(t_env *env_lst, t_token *token, int *status)
{
	if (token->command_line[0] != NULL && token->next == NULL
		&& ft_strncmp(token->command_line[0], "exit", 5) == 0)
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

static int	preprocess_command(t_env *env_lst, t_token **token,
	char *line, int *status)
{
	int	syntax_result;

	syntax_result = 0;
	if (check_syntax_before_parser(line) != 0)
	{
		*status = 2;
		free(line);
		return (CONTINUE);
	}
	*token = parser(line);
	free(line);
	if (*token == NULL)
		clear_exit(env_lst, *token, 1);
	if (syntax_result == CONTINUE)
		return (token_lstclear(token), CONTINUE);
	if (pass_token_to_expand(env_lst, *token, *status) != 0)
		clear_exit(env_lst, *token, EXIT_FAILURE);
	syntax_result = check_syntax(*token);
	if (syntax_result != 0)
	{
		*status = syntax_result;
		token_lstclear(token);
		return (CONTINUE);
	}
	return (0);
}

static int	process_input_line(char **line, int status)
{
	*line = readline("minishell> ");
	if (*line == NULL)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(status);
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
	t_env	*env_lst;
	t_token	*token;
	char	*line;
	int		status;

	(void)argv;
	(void)argc;
	ft_signal();
	status = 0;
	env_lst = create_env_lst(envp);
	while (1)
	{
		if (process_input_line(&line, status) == CONTINUE)
			continue ;
		if (preprocess_command(env_lst, &token, line, &status) == CONTINUE)
			continue ;
		if (no_pipe_exit(env_lst, token, &status) == CONTINUE)
			continue ;
		if (executor(token, env_lst, &status) == 1)
			clear_exit(env_lst, token, EXIT_FAILURE);
		token_lstclear(&token);
	}
	env_lstclear(&env_lst);
	return (status);
}
