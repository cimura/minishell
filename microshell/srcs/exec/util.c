#include "exec.h"

// /bin/cat Makefile > out1 > out2
int count_until_redirection(char **cmdline)
{
	int count = 0;
	while (cmdline[count] != NULL)
	{
	if (ft_strncmp(cmdline[count], ">", 2) == 0
		|| ft_strncmp(cmdline[count], ">>", 3) == 0
		|| ft_strncmp(cmdline[count], "<", 2) == 0
		|| ft_strncmp(cmdline[count], "<<", 3) == 0)
		return (count);
	count++;
	}
	return (count);
}

void	print_commands(char **commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		printf("%s\n", commands[i++]);
	}
}

void	free_cmd_data(t_cmd_data *data)
{
	free(data->path);
	data->path = NULL;
	free_commands(data->cmd);
	free(data);
	data = NULL;
}

// static void	Print(t_token *token)
// {
// 	while (token != NULL)
// 	{
// 		print_commands(cmd);
// 		token = token->next;
// 		if (token != NULL)
// 			printf("\tnext...\n");
// 	}
// }


// void	test_main(t_env *env_lst)
// {
// 	t_token	*token;
// 	char	*input;

// 	input = "echo hello$USER >cat out| ls  <<INFILE";
// 	token = lexer(input);
// 	assert(strcmp())
// }

bool  is_builtin(char **cmd)
{
	return (ft_strncmp(cmd[0], "cd", 3) == 0 ||
			ft_strncmp(cmd[0], "echo", 5) == 0 ||
			ft_strncmp(cmd[0], "env", 4) == 0 ||
			ft_strncmp(cmd[0], "exit", 5) == 0 ||
			ft_strncmp(cmd[0], "export", 6) == 0 ||
			ft_strncmp(cmd[0], "pwd", 4) == 0 ||
			ft_strncmp(cmd[0], "unset", 6) == 0);
}

void	builtin_command(char **cmd, t_env *env_lst, int in_fd, int out_fd)
{
	 int	out = dup(STDOUT_FILENO);
	(void)in_fd;
	// if (pipe(fd) == -1)
  //   	perror("pipe");
	// dup2(fd[0], STDIN_FILENO);
//	if (in_fd != stdin_fileno)
//		dup2(in_fd, stdin_fileno);
	if (out_fd != STDOUT_FILENO)
		dup2(out_fd, STDOUT_FILENO);
	// close(fd[0]);
	// close(fd[1]);
  // else
  // {
  //   dup2(stash_fd, STDOUT_FILENO);
  //   close(stash_fd);
  // }
	// exitの引数は何にすべきか
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		cd(&cmd[1]);
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		echo(&cmd[1]);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		env(env_lst);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		exit(1);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		export(&cmd[1], env_lst);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		pwd();
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		unset(&cmd[1], env_lst);
	dup2(out, STDOUT_FILENO);
	close(STDOUT_FILENO);
	close(out);
}

