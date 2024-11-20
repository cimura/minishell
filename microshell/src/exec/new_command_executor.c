/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_command_executor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 23:53:42 by cimy              #+#    #+#             */
/*   Updated: 2024/11/20 20:01:44 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

void	setup_and_exec(t_cmd_data *until_redirection, char **envp,
												t_file_descripter fd)
{
	(void)fd;
	if (execve(until_redirection->path, until_redirection->cmd, envp) == -1)
	{
		ft_putstr_fd(until_redirection->cmd[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
}

int	first_command(t_token *token, t_env *env_lst, t_file_descripter *fd,
	int *end_status)
{
	int		pipe_fd[2];
	pid_t	pid;

	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, sigquit_handler_child);
	if (pipe(pipe_fd) == -1)
		perror("pipe");
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		if (run_command_with_redirect(token, env_lst, fd, end_status) == -1)
			return (-1);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		ft_signal();
		if (WIFEXITED(*end_status))
			*end_status = WEXITSTATUS(*end_status);
		else if (WIFSIGNALED(*end_status))
			*end_status = 128 + WTERMSIG(*end_status);
	}
	return (0);
}

int	middle_command(t_token *token, t_env *env_lst, t_file_descripter *fd,
	int *end_status)
{
	int		pipe_fd[2];
	pid_t	pid;

	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, sigquit_handler_child);
	if (pipe(pipe_fd) == -1)
		perror("pipe");
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		if (run_command_with_redirect(token, env_lst, fd, end_status) == -1)
			return (-1);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		ft_signal();
		if (WIFEXITED(*end_status))
			*end_status = WEXITSTATUS(*end_status);
		else if (WIFSIGNALED(*end_status))
			*end_status = 128 + WTERMSIG(*end_status);
	}
	return (0);
}

int	last_command(t_token *token, t_env *env_lst, t_file_descripter *fd,
	int *end_status)
{
	int		status;
	pid_t	pid;

	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, sigquit_handler_child);
	status = 0;
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		if (run_command_with_redirect(token, env_lst, fd, end_status) == -1)
			return (-1);
		exit(EXIT_FAILURE);
	}
	else
	{
		while (waitpid(pid, end_status, 0) > 0)
		{}
		ft_signal();
		if (WIFEXITED(*end_status))
			*end_status = WEXITSTATUS(*end_status);
		else if (WIFSIGNALED(*end_status))
			*end_status = 128 + WTERMSIG(*end_status);
	}
	return (status);
}

void	execve_command(t_cmd_data *until_redirection, char **envp,
								t_file_descripter fd, int *end_status)
{
	(void)end_status;
		setup_and_exec(until_redirection, envp, fd);
		exit(127);
}

void	initialize_fd(t_file_descripter *fd)
{
	fd->pure_stdin = dup(STDIN_FILENO);
	fd->pure_stdout = dup(STDOUT_FILENO);
	fd->read_from = STDIN_FILENO;
	fd->write_to = STDOUT_FILENO;
}


int	one_command(t_token *token, t_env *env_lst, t_file_descripter *fd,
	int *end_status)
{
	pid_t	pid;

	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, sigquit_handler_child);

	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		if (run_command_with_redirect(token, env_lst, fd, end_status) == -1)
			return (-1);
	}
	else
	{
		ft_signal();
		waitpid(pid, end_status, 0);
		if (WIFEXITED(*end_status))
			*end_status = WEXITSTATUS(*end_status);
		else if (WIFSIGNALED(*end_status))
			*end_status = 128 + WTERMSIG(*end_status);
	}
	return (0);
}

int	count_lstsize(t_token *token)
{
	int	c;

	c = 0;
	while (token != NULL)
	{
		c++;
		token = token->next;
	}
	return (c);
}

int	branch(t_token *token, t_env *env_lst, t_file_descripter *fd,
	int *end_status)
{
	int	count;
	count = count_lstsize(token);
	if (count == 1)
		one_command(token, env_lst, fd, end_status);
	else if (count == 2)
	{
		if (first_command(token, env_lst, fd, end_status) == -1)
			return (-1);
		token = token->next;
		if (last_command(token, env_lst, fd, end_status) == -1)
				return (-1);
	}
	else
	{
		if (first_command(token, env_lst, fd, end_status) == -1)
			return (-1);
		token = token->next;
		while (token->next != NULL)
		{
			if (middle_command(token, env_lst, fd, end_status) == -1)
				return (-1);
			token = token->next;
		}
		if (last_command(token, env_lst, fd, end_status))
				return (-1);
	}
	return (0);
}

// 標準出力や標準入力はdup2によって書き換わるため，構造体でその値を保存しておく
// -> 最後とそれ以外で分ければいい
int	execute_command_line(t_token *token, t_env *env_lst, int *end_status)
{
	t_file_descripter	fd;

	initialize_fd(&fd);
	if (branch(token, env_lst, &fd, end_status) == -1)
		return (-1);
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
// 		return (env_lstclear(&env_lst, free_env_node), 1);
// 	if (pass_token_to_expand(env_lst, token, status) != 0)
// 	{
// 		env_lstclear(&env_lst, free_env_node);
// 		token_lst_clear(&token, free_commands);
// 		return (1);
// 	}
//	if (execute_command_line(token, env_lst, &status) == -1)
// 	{
// 		env_lstclear(&env_lst, free_env_node);
// 		token_lst_clear(&token, free_commands);
// 		return (1);
// 	}
// 	env_lstclear(&env_lst, free_env_node);
// 	token_lst_clear(&token, free_commands);
// 	return (status);
// }
