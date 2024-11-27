/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_command_executor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 23:53:42 by cimy              #+#    #+#             */
/*   Updated: 2024/11/27 12:21:25 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	setup_and_exec(t_cmd_data *until_redirection, char **envp,
												t_file_descripter fd)
{
	if (fd.now_in != STDIN_FILENO)
	{
		dup2(fd.now_in, STDIN_FILENO);
		close(fd.now_in);
	}
	// else
	// 	close(fd.now_in);
	if (fd.now_out != STDOUT_FILENO)
	{
		dup2(fd.now_out, STDOUT_FILENO);
		close(fd.now_out);
	}
	// else
	// 	close(fd.now_out);
	if (execve(until_redirection->path, until_redirection->cmd, envp) == -1)
	{
		ft_putstr_fd(until_redirection->cmd[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
}

void	execve_command(t_cmd_data *until_redirection, char **envp,
								t_file_descripter fd, int *end_status)
{
	pid_t	pid;

	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, sigquit_handler_child);
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		setup_and_exec(until_redirection, envp, fd);
		exit(127);
	}
	else if (pid > 0)
	{
		// close(fd.now_out);
		// if (fd.now_in != STDIN_FILENO)
		// 	close(fd.now_in);
		waitpid(pid, end_status, 0);
		ft_signal();
		if (WIFEXITED(*end_status))
			*end_status = WEXITSTATUS(*end_status);
		else if (WIFSIGNALED(*end_status))
			*end_status = 128 + WTERMSIG(*end_status);
	}
}

void	initialize_fd(t_file_descripter *fd)
{
	fd->pure_stdin = dup(STDIN_FILENO);
	fd->pure_stdout = dup(STDOUT_FILENO);
	fd->now_in = STDIN_FILENO;
	fd->now_out = STDOUT_FILENO;
}

bool	is_executable(char **cmd)
{
	if (cmd == NULL || cmd[0] == NULL)
		return (false);
	return (true);
}

int	run_command_with_redirect(t_token *token, t_env *env_lst,
						t_file_descripter *fd, int *end_status)
{
	t_cmd_data	*until_redirection;
	char		**env_array;

	env_array = env_lst_to_array(env_lst);
	if (env_array == NULL)
		return (-1);
	if (redirect(token, env_lst, *fd, *end_status) == 1)
		return (free_ptr_array(env_array), -1);
	until_redirection = register_cmd_data(token, env_lst);
	if (until_redirection == NULL)
		return (free_ptr_array(env_array), -1);
	if (is_builtin(until_redirection->cmd))
		builtin_command(until_redirection->cmd, env_lst, *fd, end_status);
	else if (is_executable(until_redirection->cmd))
		execve_command(until_redirection, env_array, *fd, end_status);
	free_cmd_data(until_redirection);
	free_ptr_array(env_array);
	return (0);
}

int	case_no_pipe_ahead(t_token *token, t_env *env_lst, t_file_descripter *fd,
	int *end_status)
{
	int	local_status;

	fd->now_out = dup(STDOUT_FILENO);
	local_status = run_command_with_redirect(token, env_lst, fd, end_status);
	close(fd->now_in);
	close(fd->now_out);
	return (local_status);
}

int	case_pipe_ahead(t_token *token, t_env *env_lst, t_file_descripter *fd,
	int *end_status)
{
	int	pipe_fd[2];
	int	local_status;

	if (pipe(pipe_fd) != 0)
	{
		perror("pipe");
		return (-1);
	}
	fd->now_out = dup(pipe_fd[1]);
	close(pipe_fd[1]);
	local_status = run_command_with_redirect(token, env_lst, fd, end_status);
	close(fd->now_out);
	if (fd->now_in != STDIN_FILENO)
		close(fd->now_in);
	fd->now_in = dup(pipe_fd[0]);
	close(pipe_fd[0]);
	return (local_status);
}

// 標準出力や標準入力はdup2によって書き換わるため，構造体でその値を保存しておく
// -> 最後とそれ以外で分ければいい
int	execute_command_line(t_token *token, t_env *env_lst, int *end_status)
{
	t_file_descripter	fd;

	initialize_fd(&fd);
	while (token != NULL)
	{
		if (token->next == NULL)
		{
			if (case_no_pipe_ahead(token, env_lst, &fd, end_status) == -1)
				return (-1);
		}
		else
		{
			if (case_pipe_ahead(token, env_lst, &fd, end_status) == -1)
				return (-1);
		}
		token = token->next;
	}
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
//	int		status;

// 	if (argc < 2)
// 		return (printf("Must have 2 arguments\n"), 1);
//	status = 0;
// 	env_lst = create_env_lst(envp);
// 	if (env_lst == NULL)
// 		return (1);
// 	token = lexer(argv[1]);
// 	if (token == NULL)
// 		return (env_lstclear(&env_lst), 1);
// 	if (pass_token_to_expand(env_lst, token, status) != 0)
// 	{
// 		env_lstclear(&env_lst);
// 		token_lstclear(&token);
// 		return (1);
// 	}
//	if (execute_command_line(token, env_lst, &status) == -1)
// 	{
// 		env_lstclear(&env_lst);
// 		token_lstclear(&token);
// 		return (1);
// 	}
// 	env_lstclear(&env_lst);
// 	token_lstclear(&token);
// 	return (status);
// }
