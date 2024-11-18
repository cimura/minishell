/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:04:16 by cimy              #+#    #+#             */
/*   Updated: 2024/11/17 17:44:53 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	g_global = 0;

void	sigint_handler_in_heredoc(int signum)
{
	int	pipefd[2];

	(void)signum;
	g_global = 1;
	//printf("heredoc_handler\n");
	if (pipe(pipefd) < 0)
		perror("pipe: ");
	dup2(pipefd[0], STDIN_FILENO);
	write(pipefd[1], "", 1);
	close(pipefd[0]);
	close(pipefd[1]);
}

int	here_doc(char *eof, t_env *env_lst, t_file_descripter fd, int end_status)
{
	char	*line;
	int		fd_tmp;
	char	*tmp_file = "/tmp/.heredoc_tmp";
	char	*expanded;

	fd_tmp = open(tmp_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_tmp == -1)
	{
		perror("open");
		return (1);
	}
	if (fd_tmp == -1)
		perror("tmpfile");
	while (1)
	{
		signal(SIGINT, sigint_handler_in_heredoc);
		line = readline("> ");
		ft_signal();
		if (g_global == 1)
		{
			g_global = 0;
			close(fd_tmp);
			free(line);
			return (0);
		}
		if (line == NULL)
			break ;
		expanded = expand_env_variable(env_lst, line, end_status);
		free(line);
		if (!expanded || (ft_strncmp(expanded, eof, ft_strlen(eof) + 1) == 0))
		{
			free(expanded);
			break ;
		}
		write(fd_tmp, expanded, ft_strlen(expanded));
		write(fd_tmp, "\n", 1);
		free(expanded);
	}
	close(fd_tmp);
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
			if (expand== NULL)
				return (1);
			free(per_pipe->command_line[i]);
			per_pipe->command_line[i] = expand;
			i++;
		}
		per_pipe = per_pipe->next;
	}
	return (0);
}

// /bin/cat Makefile| /usr/bin/grep all
// TODO: /bin/cat Makefile| /usr/bin/grep all > out
int	set_path(char *cmd, char **path, t_env *env_lst)
{
	char	*env_path;
	char	**com_sep;
	char	*segment;
	char	*candidate;
	int		i;

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
	i = 0;
	while (com_sep[i])
	{
		segment = ft_strjoin(com_sep[i], "/");
		if (segment == NULL)
			return (free_ptr_array(com_sep), 1);
		candidate = ft_strjoin(segment, cmd);
		if (candidate == NULL)
			return (free_ptr_array(com_sep), free(segment), 1);
		free(segment);
		if (access(candidate, X_OK) == 0)
		{
			*path = candidate;
			break ;
		}
		free(candidate);
		i++;
	}
	free_ptr_array(com_sep);
	return (0);
}

char  **get_cmd_until_redirection(char **head_cmdline)
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
	{
		free(cmd_data->path);
		free(cmd_data);
		return (NULL);
	}
	return (cmd_data);
}

int  on_redirection(t_token *token, t_env *env_lst, t_file_descripter fd, int end_status)
{
	int	redirect_fd;
	int	i;

	i = 0;
	while (token->command_line[i] != NULL)
	{
		if (ft_strncmp(token->command_line[i], ">", 2) == 0)
		{
			 redirect_fd = open(token->command_line[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (redirect_fd == -1)
			{
				perror("open");
				return (1);
			}
			 dup2(redirect_fd, fd.write_to);
			 close(redirect_fd);
			//if (ft_open(token->command_line[i + 1], O_CREAT | O_WRONLY | O_TRUNC, fd.write_to) == -1)
			//	return (1);
		}
		else if (ft_strncmp(token->command_line[i], ">>", 3) == 0)
		{
			redirect_fd = open(token->command_line[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (redirect_fd == -1)
			{
				perror("open");
				return (1);
			}
			dup2(redirect_fd, fd.write_to);
			close(redirect_fd);
		}
		else if (ft_strncmp(token->command_line[i], "<", 2) == 0)
		{
			redirect_fd = open(token->command_line[i + 1], O_RDONLY, 0644);
			if (redirect_fd == -1)
			{
				perror("open");
				return (1);
			}
			dup2(redirect_fd, fd.read_from);
			close(redirect_fd);
		}
		else if (ft_strncmp(token->command_line[i], "<<", 3) == 0)
		{
			dup2(fd.pure_stdin, STDIN_FILENO);
			if (here_doc(token->command_line[i + 1], env_lst, fd, end_status) != 0)
				return (1);
		}
		i++;
	}
	return (0);
}
