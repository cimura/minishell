/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:04:16 by cimy              #+#    #+#             */
/*   Updated: 2024/12/12 14:38:02 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "expander.h"
#include "signal_handler.h"

int	g_global = 0;

static int	tmpfile_to_readfrom(char *tmp_file, int fd_tmp)
{
	fd_tmp = open(tmp_file, O_RDONLY);
	if (fd_tmp == -1)
	{
		perror("open");
		return (1);
	}
	if (dup2(fd_tmp, STDIN_FILENO) == -1)
		perror("dup2");
	close(fd_tmp);
	return (0);
}

static char	*expand_dollar(t_env *env_lst, char *line, int end_status)
{
	int		i;
	char	*new;

	i = 0;
	new = ft_strdup("");
	if (new == NULL)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '$')
		{
			new = env_query(env_lst, new, &line[++i], end_status);
			i += dollar_variable_size(&line[i]);
		}
		else
		{
			new = non_expandble_str(new, &line[i], "$");
			i += count_until_char(&line[i], "$");
		}
		if (new == NULL)
			return (NULL);
	}
	return (new);
}

static void	on_sigint_received(char *line, int *end_status)
{
	g_global = 0;
	*end_status = 130;
	if (line)
		ft_signal();
	else
		signal(SIGINT, sigint_handler_non_nl);
	free(line);
}

static int	append_readline_to_tmpfile(char *eof, t_env *env_lst,
								int fd_tmp, int *end_status)
{
	char	*line;
	char	*expanded;

	signal(SIGINT, sigint_handler_in_heredoc);
	line = readline("> ");
	if (g_global == 130)
	{
		on_sigint_received(line, end_status);
		return (SIGINT_RECEIVED);
	}
	if (line == NULL || ft_strncmp(line, eof, ft_strlen(eof) + 1) == 0)
		return (free(line), BREAK);
	expanded = expand_dollar(env_lst, line, *end_status);
	free(line);
	if (expanded == NULL)
		return (1);
	write(fd_tmp, expanded, ft_strlen(expanded));
	write(fd_tmp, "\n", 1);
	free(expanded);
	return (0);
}

#define TMP_FILE "/tmp/.heredoc_tmp"

int	here_doc(char *eof, t_env *env_lst,
	t_file_descripter fd, int *end_status)
{
	int	pipe_stdout;
	int	fd_tmp;
	int	local_status;

	local_status = 0;
	if (dup2(fd.pure_stdin, STDIN_FILENO) == -1)
		perror("dup2");
	pipe_stdout = dup(STDOUT_FILENO);
	if (dup2(fd.pure_stdout, STDOUT_FILENO) == -1)
		perror("dup2");
	fd_tmp = open(TMP_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_tmp == -1)
		return (perror("open"), 1);
	while (local_status == 0)
	{
		local_status = append_readline_to_tmpfile(eof, env_lst,
				fd_tmp, end_status);
	}
	close(fd_tmp);
	if (dup2(pipe_stdout, STDOUT_FILENO) == -1)
		perror("dup2");
	close(pipe_stdout);
	if (local_status == BREAK)
		local_status = tmpfile_to_readfrom(TMP_FILE, fd_tmp);
	return (local_status);
}
