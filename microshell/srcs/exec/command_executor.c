#include "exec.h"

void	command(t_cmd_data *until_redirection, char **envp, int in_fd, int out_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		if (in_fd != STDIN_FILENO)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		if (out_fd != STDOUT_FILENO)
		{
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
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

// 標準出力や標準入力はdup2によって書き換わるため，構造体でその値を保存しておく
// -> 最後とそれ以外で分ければいい
int	execute_command_line(t_token *token, t_env *env_lst)
{
	t_cmd_data	*until_redirection;
	char 	**env_array;
	int		fd[2];
	int		in_fd;

	env_array = env_lst_to_array(env_lst);
	if (env_array == NULL)
		return (1);
	in_fd = STDIN_FILENO;
	while (token != NULL)
	{
		// 最後のコマンド
		if (token->next == NULL)
		{
			until_redirection = redirect(token, env_lst);
			if (until_redirection == NULL)
				return (free_commands(env_array), 1);
			if (is_builtin(until_redirection->cmd))
				builtin_command(until_redirection->cmd, env_lst, in_fd, STDOUT_FILENO);
			else
				command(until_redirection, env_array, in_fd, STDOUT_FILENO);
			close(in_fd);
		}
		// それ以外
		else
		{
			pipe(fd);
			until_redirection = redirect(token, env_lst);
			if (until_redirection == NULL)
				return (free_commands(env_array), 1);
			if (is_builtin(until_redirection->cmd))
				builtin_command(until_redirection->cmd, env_lst, in_fd, fd[1]);
			else
				command(until_redirection, env_array, in_fd, fd[1]);
			close(fd[1]);
			if (in_fd != STDIN_FILENO)
				close(in_fd);
			in_fd = fd[0]; // 次のコマンドの入力に設定
		}
		free_cmd_data(until_redirection);
		token = token->next;
	}
	free_commands(env_array);
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
