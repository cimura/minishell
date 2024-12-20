/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:02:58 by cimy              #+#    #+#             */
/*   Updated: 2024/12/12 16:27:48 by sshimura         ###   ########.fr       */
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

extern int	g_global;

static int	no_pipe_exit(t_mobile *mobile,
	t_env *env_lst, t_command_lst *per_pipe)
{
	if (per_pipe->command_line[0] != NULL && per_pipe->next == NULL
		&& ft_strncmp(per_pipe->command_line[0], "exit", 5) == 0)
	{
		if (ft_exit(&per_pipe->command_line[1],
				&mobile->status, NOPIPE) == CONTINUE)
		{
			command_lstclear(&per_pipe);
			return (CONTINUE);
		}
		else
			clear_exit(mobile->cwd, env_lst, per_pipe, mobile->status);
	}
	return (0);
}

static int	preprocess_command(t_env *env_lst, t_command_lst **per_pipe,
	char *line, t_mobile *mobile)
{
	int	syntax_result;

	syntax_result = 0;
	if (check_syntax_before_parser(line, &mobile->status) != 0)
	{
		free(line);
		return (CONTINUE);
	}
	*per_pipe = parser(line);
	free(line);
	if (*per_pipe == NULL)
		clear_exit(mobile->cwd, env_lst, *per_pipe, 1);
	syntax_result = check_syntax(*per_pipe, env_lst);
	if (syntax_result != 0)
	{
		mobile->status = syntax_result;
		command_lstclear(per_pipe);
		return (CONTINUE);
	}
	if (expander(env_lst, *per_pipe, mobile->status) != 0)
		clear_exit(mobile->cwd, env_lst, *per_pipe, EXIT_FAILURE);
	return (0);
}

static int	process_input_line(t_env *env_lst, char **line, t_mobile *mobile)
{
	if (mobile->status == 0)
		*line = readline("mini"GREEN"('u')"RESET" $ ");
	else
		*line = readline("mini"RED"(`n`)"RESET" $ ");
	if (*line == NULL)
	{
		free(mobile->cwd);
		env_lstclear(&env_lst);
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(mobile->status);
	}
	if (g_global != 0)
	{
		mobile->status = g_global;
		g_global = 0;
	}
	ft_signal();
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
	t_mobile		mobile;
	char			*line;

	(void)argv;
	(void)argc;
	ft_signal();
	env_lst = create_env_lst(envp);
	init_mobile(env_lst, &mobile);
	while (1)
	{
		if (process_input_line(env_lst, &line, &mobile) == CONTINUE)
			continue ;
		if (preprocess_command(env_lst, &per_pipe, line,
				&mobile) == CONTINUE)
			continue ;
		if (no_pipe_exit(&mobile, env_lst, per_pipe) == CONTINUE)
			continue ;
		if (executor(per_pipe, env_lst, &mobile) == 1)
			clear_exit(mobile.cwd, env_lst, per_pipe, EXIT_FAILURE);
		command_lstclear(&per_pipe);
	}
	env_lstclear(&env_lst);
	return (mobile.status);
}
