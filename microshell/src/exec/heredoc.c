/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:04:16 by cimy              #+#    #+#             */
/*   Updated: 2024/12/02 15:18:34 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "expander.h"
#include "signal_handler.h"

#define SIGINT_RECEIVED 2
#define BREAK 3

int	g_global = 0;

static void	sigint_handler_in_heredoc(int signum)
{
	int	pipefd[2];

	(void)signum;
	g_global = 1;
	if (pipe(pipefd) < 0)
		perror("pipe: ");
	dup2(pipefd[0], STDIN_FILENO);
	write(pipefd[1], "", 1);
	close(pipefd[0]);
	close(pipefd[1]);
}

static int	tmpfile_to_readfrom(char *tmp_file, int fd_tmp)
{
	fd_tmp = open(tmp_file, O_RDONLY);
	if (fd_tmp == -1)
	{
		perror("open");
		return (1);
	}
	dup2(fd_tmp, STDIN_FILENO);
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
			i += count_key_size(&line[i]);
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

static int	append_readline_to_tmpfile(char *eof, t_env *env_lst,
								int fd_tmp, int *end_status)
{
	char	*line;
	char	*expanded;

	signal(SIGINT, sigint_handler_in_heredoc);
	line = readline("> ");
	ft_signal();
	if (g_global == 1)
	{
		g_global = 0;
		*end_status = 130;
		free(line);
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

int	here_doc(char *eof, t_env *env_lst,
	t_file_descripter fd, int *end_status)
{
	int		fd_tmp;
	char	*tmp_file;
	int		local_status;

	dup2(fd.pure_stdin, STDIN_FILENO);
	tmp_file = "/tmp/.heredoc_tmp";
	fd_tmp = open(tmp_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_tmp == -1)
		return (perror("open"), 1);
	while (1)
	{
		local_status = append_readline_to_tmpfile(eof, env_lst,
				fd_tmp, end_status);
		if (local_status == SIGINT_RECEIVED)
			return (close(fd_tmp), -1);
		else if (local_status == 1)
			return (close(fd_tmp), 1);
		else if (local_status == BREAK)
			break ;
	}
	close(fd_tmp);
	return (tmpfile_to_readfrom(tmp_file, fd_tmp));
}
