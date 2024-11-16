/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 23:53:42 by cimy              #+#    #+#             */
/*   Updated: 2024/11/15 19:33:45 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern int g_status;

void	command(t_cmd_data *until_redirection, char **envp, t_file_descripter fd)
{
	pid_t	pid;

	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, sigquit_handler_child);
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		if (fd.read_from != STDIN_FILENO)
		{
			dup2(fd.read_from, STDIN_FILENO);
			close(fd.read_from);
		}
		if (fd.write_to != STDOUT_FILENO)
		{
			dup2(fd.write_to, STDOUT_FILENO);
			close(fd.write_to);
		}
		if (execve(until_redirection->path, until_redirection->cmd, envp) == -1)
		{
			ft_putstr_fd(until_redirection->cmd[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
		}
		exit(127);
	}
	else if (pid > 0)
	{
		waitpid(pid, &g_status, 0);
		ft_signal();
		if (WIFEXITED(g_status))
			g_status = WEXITSTATUS(g_status);
		else if (WIFSIGNALED(g_status))
			g_status = 128 + WTERMSIG(g_status);
	}
}

void	initialize_fd(t_file_descripter *fd)
{
	fd->pure_stdin = dup(STDIN_FILENO);
	fd->pure_stdout = dup(STDOUT_FILENO);
	fd->read_from = STDIN_FILENO;
	fd->write_to = STDOUT_FILENO;
}

int	case_no_pipe_ahead(t_token *token, t_env *env_lst, char **env_array, t_file_descripter *fd)
{
	t_cmd_data	*until_redirection;

	fd->write_to = STDOUT_FILENO;
	until_redirection = register_cmd_data(token, env_lst);
	if (until_redirection == NULL)
		return (1);
	if (on_redirection(token, env_lst, *fd) == 1)
		return (1);
	if (is_builtin(until_redirection->cmd))
		builtin_command(until_redirection->cmd, env_lst, *fd);
	else
		command(until_redirection, env_array, *fd);
	close(fd->read_from);
	close(fd->write_to);
	free_cmd_data(until_redirection);
	return (0);
}

int	case_pipe_ahead(t_token *token, t_env *env_lst, char **env_array, t_file_descripter *fd)
{
	int			pipe_fd[2];
	t_cmd_data	*until_redirection;

	if (pipe(pipe_fd) != 0)
	{
		perror("pipe");
		return (1);
	}
	fd->write_to = pipe_fd[1];
	until_redirection = register_cmd_data(token, env_lst);
	if (until_redirection == NULL)
		return (1);
	if (on_redirection(token, env_lst, *fd) == 1)
		return (1);
	if (is_builtin(until_redirection->cmd))
		builtin_command(until_redirection->cmd, env_lst, *fd);
	else
		command(until_redirection, env_array, *fd);
	close(pipe_fd[1]);
	if (fd->read_from != STDIN_FILENO)
		close(fd->read_from);
	free_cmd_data(until_redirection);;
	fd->read_from = pipe_fd[0];
	return (0);
}

// 標準出力や標準入力はdup2によって書き換わるため，構造体でその値を保存しておく
// -> 最後とそれ以外で分ければいい
int	execute_command_line(t_token *token, t_env *env_lst)
{
	t_file_descripter	fd;
	char 	**env_array;

	initialize_fd(&fd);
	env_array = env_lst_to_array(env_lst);
	if (env_array == NULL)
		return (1);
	while (token != NULL)
	{
		if (token->next == NULL)
		{
			if (case_no_pipe_ahead(token, env_lst, env_array, &fd) == 1)
				return (free_ptr_array(env_array), 1);
		}
		else
		{
			if (case_pipe_ahead(token, env_lst, env_array, &fd) == 1)
				return (free_ptr_array(env_array), 1);
		}
		token = token->next;
	}
	free_ptr_array(env_array);
	dup2(fd.pure_stdin, STDIN_FILENO);
	dup2(fd.pure_stdout, STDOUT_FILENO);
	close(fd.pure_stdin);
	close(fd.pure_stdout);
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env	*env_lst;
// 	t_token	*token;
//
// 	if (argc < 2)
// 		return (printf("Must have 2 arguments\n"), 1);
// 	env_lst = create_env_lst(envp);
// 	if (env_lst == NULL)
// 		return (1);
// 	token = lexer(argv[1]);
// 	if (token == NULL)
// 		return (env_lstclear(&env_lst, free_env_node), 1);
// 	if (pass_token_to_expand(env_lst, token) != 0)
// 	{
// 		env_lstclear(&env_lst, free_env_node);
// 		token_lst_clear(&token, free_ptr_array);
// 		return (1);
// 	}
// 	if (execute_command_line(token, env_lst) != 0)
// 	{
// 		env_lstclear(&env_lst, free_env_node);
// 		token_lst_clear(&token, free_ptr_array);
// 		return (1);
// 	}
// 	env_lstclear(&env_lst, free_env_node);
// 	token_lst_clear(&token, free_ptr_array);
// 	return (0);
// }
