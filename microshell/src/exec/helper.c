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

int	tmpfile_to_readfrom(char *tmp_file, int fd_tmp, t_file_descripter fd)
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

int	append_readline_to_tmpfile(char *eof, t_env *env_lst,
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

int	set_cmd_in_path(char *cmd, char **com_sep, char **path)
{
	char	*segment;
	char	*candidate;
	int		i;

	i = 0;
	while (com_sep[i])
	{
		segment = ft_strjoin(com_sep[i], "/");
		if (segment == NULL)
			return (1);
		candidate = ft_strjoin(segment, cmd);
		if (candidate == NULL)
			return (free(segment), 1);
		free(segment);
		if (access(candidate, X_OK) == 0)
		{
			*path = candidate;
			break ;
		}
		free(candidate);
		i++;
	}
	return (0);
}

// /bin/cat Makefile| /usr/bin/grep all
// TODO: /bin/cat Makefile| /usr/bin/grep all > out
int	set_path(char *cmd, char **path, t_env *env_lst)
{
	char	*env_path;
	char	**com_sep;

	*path = NULL;
	if (access(cmd, X_OK) == 0)
	{
		*path = ft_strdup(cmd);
		if (*path == NULL)
			return (1);
		return (0);
	}
	env_path = get_value_from_key(env_lst, "PATH");
	com_sep = ft_split(env_path, ':');
	if (com_sep == NULL)
		return (1);
	if (set_cmd_in_path(cmd, com_sep, path) == 1)
		return (free_ptr_array(com_sep), 1);
	free_ptr_array(com_sep);
	return (0);
}

char	**get_cmd_until_redirection(char **head_cmdline)
{
	int		i;
	int		size;
	char	**result;

	size = count_until_redirection(head_cmdline);
	result = malloc((size + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		result[i] = ft_strdup(head_cmdline[i]);
		if (result[i] == NULL)
			return (free_ptr_array(result), NULL);
		i++;
	}
	result[i] = NULL;
	return (result);
}

int	ft_open(char *path, int oflag, int to_dup)
{
	int	redirect_fd;

	redirect_fd = open(path, oflag, 0644);
	if (redirect_fd == -1)
		return (1);
	dup2(redirect_fd, to_dup);
	close(redirect_fd);
	return (0);
}

// /bin/cat Makefile > out1 > out2
t_cmd_data	*register_cmd_data(t_token *token, t_env *env_lst)
{
	t_cmd_data	*cmd_data;

	cmd_data = malloc(sizeof(t_cmd_data));
	if (cmd_data == NULL)
		return (NULL);
	if (set_path(token->command_line[0], &(cmd_data->path), env_lst) != 0)
		return (free(cmd_data), NULL);
	cmd_data->cmd = get_cmd_until_redirection(&token->command_line[0]);
	if (cmd_data->cmd == NULL)
		return (free(cmd_data->path), free(cmd_data), NULL);
	return (cmd_data);
}

int	handle_redirect(char **command_line, int i, t_file_descripter fd)
{
	if (ft_strncmp(command_line[i], ">", 2) == 0)
	{
		if (ft_open(command_line[i + 1],
				O_CREAT | O_WRONLY | O_TRUNC, fd.write_to) == -1)
			return (1);
	}
	else if (ft_strncmp(command_line[i], ">>", 3) == 0)
	{
		if (ft_open(command_line[i + 1],
				O_CREAT | O_WRONLY | O_APPEND, fd.write_to) == -1)
			return (1);
	}
	else if (ft_strncmp(command_line[i], "<", 2) == 0)
	{
		if (ft_open(command_line[i + 1],
				O_RDONLY, fd.read_from) == -1)
			return (1);
	}
	return (0);
}

int	redirect(t_token *token, t_env *env_lst,
			t_file_descripter fd, int end_status)
{
	int	i;

	i = 0;
	while (token->command_line[i] != NULL)
	{
		if (handle_redirect(token->command_line, i, fd) == 1)
			return (1);
		if (ft_strncmp(token->command_line[i], "<<", 3) == 0)
		{
			if (here_doc(token->command_line[i + 1],
					env_lst, fd, end_status) != 0)
				return (1);
		}
		i++;
	}
	return (0);
}
