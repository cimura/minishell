/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:02:58 by cimy              #+#    #+#             */
/*   Updated: 2024/12/02 19:47:52 by ttakino          ###   ########.fr       */
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

static int	no_pipe_exit(t_env *env_lst, t_command_lst *per_pipe, int *status)
{
	if (per_pipe->command_line[0] != NULL && per_pipe->next == NULL
		&& ft_strncmp(per_pipe->command_line[0], "exit", 5) == 0)
	{
		if (ft_exit(&per_pipe->command_line[1], status) == CONTINUE)
		{
			command_lstclear(&per_pipe);
			return (CONTINUE);
		}
		else
			clear_exit(env_lst, per_pipe, *status);
	}
	return (0);
}

static int	preprocess_command(t_env *env_lst, t_command_lst **per_pipe,
	char *line, int *status)
{
	int	syntax_result;

	syntax_result = 0;
	if (check_syntax_before_parser(line, status) != 0)
	{
		free(line);
		return (CONTINUE);
	}
	*per_pipe = parser(line);
	free(line);
	if (*per_pipe == NULL)
		clear_exit(env_lst, *per_pipe, 1);
	if (syntax_result == CONTINUE)
		return (command_lstclear(per_pipe), CONTINUE);
	if (expander(env_lst, *per_pipe, *status) != 0)
		clear_exit(env_lst, *per_pipe, EXIT_FAILURE);
	syntax_result = check_syntax(*per_pipe);
	if (syntax_result != 0)
	{
		*status = syntax_result;
		command_lstclear(per_pipe);
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
	t_env			*env_lst;
	t_command_lst	*per_pipe;
	char			*line;
	int				status;

	(void)argv;
	(void)argc;
	ft_signal();
	status = 0;
	env_lst = create_env_lst(envp);
	while (1)
	{
		if (process_input_line(&line, status) == CONTINUE)
			continue ;
		if (preprocess_command(env_lst, &per_pipe, line, &status) == CONTINUE)
			continue ;
		if (no_pipe_exit(env_lst, per_pipe, &status) == CONTINUE)
			continue ;
		if (executor(per_pipe, env_lst, &status) == 1)
			clear_exit(env_lst, per_pipe, EXIT_FAILURE);
		command_lstclear(&per_pipe);
	}
	env_lstclear(&env_lst);
	return (status);
}
