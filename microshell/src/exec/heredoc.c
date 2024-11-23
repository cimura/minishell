/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:04:16 by cimy              #+#    #+#             */
/*   Updated: 2024/11/20 15:27:16 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	g_global = 0;

void	sigint_handler_in_heredoc(int signum)
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

static int	tmpfile_to_readfrom(char *tmp_file, int fd_tmp,
										t_file_descripter fd)
{
	fd_tmp = open(tmp_file, O_RDONLY);
	if (fd_tmp == -1)
	{
		perror("open");
		return (1);
	}
	dup2(fd_tmp, fd.read_from);
	close(fd_tmp);
	return (0);
}

#define SIGINT_RECEIVED 2
#define BREAK 3

static int	append_readline_to_tmpfile(char *eof, t_env *env_lst,
								int fd_tmp, int end_status)
{
	char	*line;
	char	*expanded;

	signal(SIGINT, sigint_handler_in_heredoc);
	line = readline("> ");
	ft_signal();
	if (g_global == 1)
	{
		g_global = 0;
		free(line);
		return (SIGINT_RECEIVED);
	}
	if (line == NULL || ft_strncmp(line, eof, ft_strlen(eof) + 1) == 0)
		return (BREAK);
	expanded = expand_env_variable(env_lst, line, end_status);
	free(line);
	if (expanded == NULL)
		return (1);
	write(fd_tmp, expanded, ft_strlen(expanded));
	write(fd_tmp, "\n", 1);
	free(expanded);
	return (0);
}

int	here_doc(char *eof, t_env *env_lst,
	t_file_descripter fd, int end_status)
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
			return (close(fd_tmp), 0);
		else if (local_status == 1)
			return (close(fd_tmp), 1);
		else if (local_status == BREAK)
			break ;
	}
	close(fd_tmp);
	return (tmpfile_to_readfrom(tmp_file, fd_tmp, fd));
}