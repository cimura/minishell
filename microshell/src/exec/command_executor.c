/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 23:53:42 by cimy              #+#    #+#             */
/*   Updated: 2024/11/13 23:53:44 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	command(t_cmd_data *until_redirection, char **envp, t_file_descripter fd)
{
	pid_t	pid;

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
			perror("execve failed");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		wait(NULL);
	}
}

void	initialize_fd(t_file_descripter *fd)
{
	fd->pure_stdin = dup(STDIN_FILENO);
	fd->pure_stdout = dup(STDOUT_FILENO);
	fd->read_from = STDIN_FILENO;
	fd->write_to = STDOUT_FILENO;
}

// 標準出力や標準入力はdup2によって書き換わるため，構造体でその値を保存しておく
// -> 最後とそれ以外で分ければいい
int	execute_command_line(t_token *token, t_env *env_lst)
{
	t_cmd_data	*until_redirection;
	t_file_descripter	fd;
	char 	**env_array;
	int		pipe_fd[2];
	// int		in_fd;

	// int	pure_stdin = dup(STDIN_FILENO);

	initialize_fd(&fd);
	env_array = env_lst_to_array(env_lst);
	if (env_array == NULL)
		return (1);
	// in_fd = STDIN_FILENO;
	while (token != NULL)
	{
		// 最後のコマンド
		if (token->next == NULL)
		{
			fd.write_to = STDOUT_FILENO;
			until_redirection = redirect(token, env_lst, fd);
			if (until_redirection == NULL)
				return (free_commands(env_array), 1);
			if (is_builtin(until_redirection->cmd))
				builtin_command(until_redirection->cmd, env_lst, fd);
			else
				command(until_redirection, env_array, fd);
			close(fd.read_from);
		}
		// それ以外
		else
		{
			pipe(pipe_fd);
			fd.write_to = pipe_fd[1];
			until_redirection = redirect(token, env_lst, fd);
			if (until_redirection == NULL)
				return (free_commands(env_array), 1);
			if (is_builtin(until_redirection->cmd))
				builtin_command(until_redirection->cmd, env_lst, fd);
			else
				command(until_redirection, env_array, fd);
			close(pipe_fd[1]);
			if (fd.read_from != STDIN_FILENO)
				close(fd.read_from);
			fd.read_from = pipe_fd[0]; // 次のコマンドの入力に設定
		}
		free_cmd_data(until_redirection);
		token = token->next;
	}
	free_commands(env_array);

	close(fd.pure_stdin);
	close(fd.pure_stdout);
	return (0);
}

// void  last_command(t_token *token, char **envp)
// {
//  	pid_t	pid;
// 	t_fd t;

//   if (pipe(t.tmp_fd) == -1)
//     perror("pipe");
// 	pid = fork();
//   if (pid == -1)
//     perror("fork");

// 	if (pid == 0)
// 	{
//     t_cmd_data *cmd = redirect(token, envp);
//     // printf("cmd->path: %s\n", cmd->path);
//     // printf("cmd->cmd: %s\n", cmd->cmd[0]);

//     close(t.tmp_fd[0]);
//     dup2(STDOUT_FILENO, t.out_fd);
//     close(t.tmp_fd[1]);
// 		if (execve(cmd->path, cmd->cmd, envp) == -1)
//     {
//       // ft_putendl_fd(cmd->path, 2);
//       perror("execve failed");
//     }
//     exit(EXIT_FAILURE);
// 	}
// 	else
// 	{
//     close(t.tmp_fd[1]);
// 		dup2(t.tmp_fd[0], t.in_fd);
// 		close(t.tmp_fd[0]);
// 		// wait(NULL);
//     exit(EXIT_SUCCESS);
// 	} 
// }
