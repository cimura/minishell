/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 23:53:42 by cimy              #+#    #+#             */
/*   Updated: 2024/11/29 14:37:45 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"
#include "signal_handler.h"

int	execute_single_command(t_token *token, t_env *env_lst,
	t_file_descripter *fd, int *end_status)
{
	t_cmd_data	*until_redirection;
	char		**env_array;
	int			local_status;

	env_array = env_lst_to_array(env_lst);
	if (env_array == NULL)
		return (1);
	local_status = redirect(token, env_lst, *fd, end_status);
	if (local_status == 1 || local_status == -1)
		return (free_ptr_array(env_array), local_status);
	until_redirection = register_cmd_data(token, env_lst);
	if (until_redirection == NULL)
		return (free_ptr_array(env_array), 1);
	if (is_builtin(until_redirection->cmd))
		execute_builtin_command(until_redirection->cmd,
			env_lst, *fd, end_status);
	else if (is_executable(until_redirection->cmd))
		execute_external_command(until_redirection,
			*fd, end_status, env_array);
	free_cmd_data(until_redirection);
	free_ptr_array(env_array);
	return (0);
}

static int	execute_two_commands(t_token *token, t_env *env_lst,
	t_file_descripter *fd, int *end_status)
{
	if (first_command(token, env_lst, fd, end_status) == 1)
		return (1);
	token = token->next;
	if (last_command(token, env_lst, fd, end_status) == 1)
		return (1);
	return (0);
}

static int	execute_multi_commands(t_token *token, t_env *env_lst,
	t_file_descripter *fd, int *end_status)
{
	if (first_command(token, env_lst, fd, end_status) == 1)
		return (1);
	token = token->next;
	while (token->next != NULL)
	{
		if (middle_command(token, env_lst, fd, end_status) == 1)
			return (1);
		token = token->next;
	}
	if (last_command(token, env_lst, fd, end_status))
		return (1);
	return (0);
}

int	handle_command_branch(t_token *token, t_env *env_lst,
	t_file_descripter *fd, int *end_status)
{
	int		count;
	int		local_status;
	t_token	*head;

	count = token_lstsize(token);
	head = token;
	if (count == 1)
		local_status = execute_single_command(token, env_lst, fd, end_status);
	else if (count == 2)
		local_status = execute_two_commands(token, env_lst, fd, end_status);
	else
		local_status = execute_multi_commands(token, env_lst, fd, end_status);
	if (local_status == 1)
		return (1);
	if (count != 1)
		wait_all_commands(head, end_status);
	ft_signal();
	return (0);
}

int	executor(t_token *token, t_env *env_lst, int *end_status)
{
	t_file_descripter	fd;

	initialize_fd(&fd);
	if (handle_command_branch(token, env_lst, &fd, end_status) == 1)
		return (1);
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
