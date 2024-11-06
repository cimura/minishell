#include "exec.h"

void	command(t_cmd_data *until_redirection, char **envp, bool last)
{
	pid_t	pid;
	int	fd[2];

  if (pipe(fd) == -1)
    perror("pipe");
	pid = fork();
  if (pid == -1)
    perror("fork");

	if (pid == 0)
	{
		close(fd[0]);
		if (last)
			dup2(1, STDOUT_FILENO);
		else
			dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (execve(until_redirection->path, until_redirection->cmd, envp) == -1)
			perror("execve failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		// wait(NULL);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

// 標準出力や標準入力はdup2によって書き換わるため，構造体でその値を保存しておく
// -> 最後とそれ以外で分ければいい
void	execute_command_line(t_token *token, t_env *env_lst)
{
	t_cmd_data	*until_redirection;
	bool	last;

	// fd.out_fd = STDOUT_FILENO;
	last = false;
	while (token != NULL)
	{
		if (token->next == NULL)
			last = true;
		until_redirection = redirect(token, env_lst_to_array(env_lst));

		if (is_builtin(until_redirection->cmd))
			builtin_command(until_redirection->cmd, env_lst, last);
		else
			command(until_redirection, env_lst_to_array(env_lst), last);
		token = token->next;
	}
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