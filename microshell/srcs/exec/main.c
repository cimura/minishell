/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:22:59 by ttakino           #+#    #+#             */
/*   Updated: 2024/11/13 16:01:25 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// void  set_stdin(const char *tmp_file)
// {
//   int fd_tmp = open(tmp_file, O_RDONLY);

//   unlink(tmp_file);
//   dup2(fd_tmp, in_fd);
//   close(fd_tmp);
// }

void	here_doc(char *eof, t_env *env_lst, int in_fd)
{
	char		*line;
	int			fd_tmp;
	char	*tmp_file = "/tmp/.heredoc_tmp";
  char  *expanded;

	fd_tmp = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_tmp == -1)
		perror("tmpfile");

	while (1)
	{
	// ft_putendl_fd("in heredoc", STDERR_FILENO);
	ft_putstr_fd("heredoc> ", in_fd);
	// dup2(in_fd, STDIN_FILENO);
		line = readline("");
		// if (*lined
	// ft_putstr_fd(line, 2);
	// dup2(STDIN_FILENO, in_fd);
		expanded = expander(env_lst, line);
		if (!expanded || (ft_strncmp(expanded, eof, ft_strlen(eof) + 1) == 0))
				break ;
		write(fd_tmp, expanded, ft_strlen(expanded));
		write(fd_tmp, "\n", 1);
		if (*line == '\0')
			write(in_fd, "\n", 1);
		free(line);
		free(expanded);
	}
	free(line);
	free(expanded);
	close(fd_tmp);
	// set_stdin(tmp_file);
  int tmp = open(tmp_file, O_RDONLY);

  unlink(tmp_file);
//   int save = dup(in_fd);
  dup2(tmp, in_fd);
  close(tmp);
//   dup2(save, in_fd);
//   close(save);
}

int	pass_token_to_expand(t_env *env_lst, t_token *per_pipe)
{
	int		i;
	char	*expand;

	while (per_pipe != NULL)
	{
		i = 0;
		while (per_pipe->command_line[i] != NULL)
		{
			expand = expander(env_lst, per_pipe->command_line[i]);
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
			return (free_commands(com_sep), 1);
		candidate = ft_strjoin(segment, cmd);
		if (candidate == NULL)
			return (free_commands(com_sep), free(segment), segment = NULL, 1);
		free(segment);
		segment = NULL;
		if (access(candidate, X_OK) == 0)
		{
			*path = candidate;
			break ;
		}
		free(candidate);
		candidate = NULL;
		i++;
	}
	free_commands(com_sep);
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
			return (free_commands(result), NULL);
		i++;
	}
	result[i] = NULL;
	return (result);
}

// /bin/cat Makefile > out1 > out2
t_cmd_data  *redirect(t_token *token, t_env *env_lst, int in_fd, int out_fd)
{
	t_cmd_data	*set;
	int			fd;
	int			i;
	int			save = dup(STDIN_FILENO);

	set = malloc(sizeof(t_cmd_data));
	if (set == NULL)
		return (NULL);
	
	// $PATHからpathを得て代入
	// get_cmd_until_redirection関数はリダイレクトまでの配列を二次元配列にする
	 if (set_path(token->command_line[0], &(set->path), env_lst) != 0)
	 	return (free(set), set = NULL, NULL);
	set->cmd = get_cmd_until_redirection(&token->command_line[0]);
	if (set->cmd == NULL)
		return (free(set->path), set->path = NULL, free(set), set = NULL, NULL);

	i = 0;
	while (token->command_line[i] != NULL)
	{
		if (ft_strncmp(token->command_line[i], ">", 2) == 0)
		{
			fd = open(token->command_line[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			dup2(fd, out_fd);
			close(fd);
		}
		else if (ft_strncmp(token->command_line[i], ">>", 3) == 0)
		{
			fd = open(token->command_line[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
			dup2(fd, out_fd);
			close(fd);
		}
		else if (ft_strncmp(token->command_line[i], "<", 2) == 0)
		{
			fd = open(token->command_line[i + 1], O_RDONLY, 0644);
			dup2(fd, in_fd);
			close(fd);
		}
		else if (ft_strncmp(token->command_line[i], "<<", 3) == 0)
		{
			dup2(save, in_fd);
			// ft_putendl_fd(token->command_line[i + 1], 2);
			here_doc(token->command_line[i + 1], env_lst, in_fd);
		}
		i++;
	}
	return (set);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_lst;
	t_token	*token;

	if (argc < 2)
		return (printf("Must have 2 arguments\n"), 1);
	env_lst = create_env_lst(envp);
	if (env_lst == NULL)
		return (1);
	token = lexer(argv[1]);
	if (token == NULL)
		return (env_lstclear(&env_lst, free_env_node), 1);
	if (pass_token_to_expand(env_lst, token) != 0)
	{
		env_lstclear(&env_lst, free_env_node);
		token_lst_clear(&token, free_commands);
		return (1);
	}
	if (execute_command_line(token, env_lst) != 0)
	{
		env_lstclear(&env_lst, free_env_node);
		token_lst_clear(&token, free_commands);
		return (1);
	}
	env_lstclear(&env_lst, free_env_node);
	token_lst_clear(&token, free_commands);
	return (0);
}
