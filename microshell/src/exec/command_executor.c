/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 23:53:42 by cimy              #+#    #+#             */
/*   Updated: 2024/12/02 20:49:16 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"
#include "signal_handler.h"

static int	execute_single_command(t_command_lst *per_pipe, t_env *env_lst,
	t_file_descripter *fd, int *end_status)
{
	t_cmd_data	*until_redirection;
	char		**env_array;
	int			local_status;

	env_array = env_lst_to_array(env_lst);
	if (env_array == NULL)
		return (close_purefd(*fd), 1);
	local_status = redirect(per_pipe, env_lst, *fd, end_status);
	if (local_status == 1 || local_status == -1)
		return (free_ptr_array(env_array), local_status);
	until_redirection = register_cmd_data(per_pipe, env_lst);
	if (until_redirection == NULL)
		return (free_ptr_array(env_array), close_purefd(*fd), 1);
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

static int	execute_two_commands(t_command_lst *per_pipe, t_env *env_lst,
	t_file_descripter *fd, int *end_status)
{
	if (first_command(per_pipe, env_lst, fd, end_status) == 1)
		return (1);
	per_pipe = per_pipe->next;
	if (last_command(per_pipe, env_lst, fd, end_status) == 1)
		return (1);
	return (0);
}

static int	execute_multi_commands(t_command_lst *per_pipe, t_env *env_lst,
	t_file_descripter *fd, int *end_status)
{
	if (first_command(per_pipe, env_lst, fd, end_status) == 1)
		return (1);
	per_pipe = per_pipe->next;
	while (per_pipe->next != NULL)
	{
		if (middle_command(per_pipe, env_lst, fd, end_status) == 1)
			return (1);
		per_pipe = per_pipe->next;
	}
	if (last_command(per_pipe, env_lst, fd, end_status))
		return (1);
	return (0);
}

static int	handle_command_branch(t_command_lst *per_pipe, t_env *env_lst,
	t_file_descripter *fd, int *end_status)
{
	int				count;
	int				local_status;
	t_command_lst	*head;

	count = command_lstsize(per_pipe);
	head = per_pipe;
	if (count == 1)
		local_status
			= execute_single_command(per_pipe, env_lst, fd, end_status);
	else if (count == 2)
		local_status
			= execute_two_commands(per_pipe, env_lst, fd, end_status);
	else
		local_status
			= execute_multi_commands(per_pipe, env_lst, fd, end_status);
	if (local_status == 1)
		return (1);
	if (count != 1)
		wait_all_commands(head, end_status);
	ft_signal();
	return (0);
}

int	executor(t_command_lst *per_pipe, t_env *env_lst, int *end_status)
{
	t_file_descripter	fd;
	int					local_status;

	initialize_fd(&fd);
	local_status = handle_command_branch(per_pipe, env_lst, &fd, end_status);
	dup2(fd.pure_stdin, STDIN_FILENO);
	dup2(fd.pure_stdout, STDOUT_FILENO);
	close_purefd(fd);
	return (local_status);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env	*env_lst;
// 	t_command_lst	*per_pipe;
//	int		status;

// 	if (argc < 2)
// 		return (printf("Must have 2 arguments\n"), 1);
//	status = 0;
// 	env_lst = create_env_lst(envp);
// 	if (env_lst == NULL)
// 		return (1);
// 	per_pipe = parser(argv[1]);
// 	if (per_pipe == NULL)
// 		return (env_lstclear(&env_lst), 1);
// 	if (expander(env_lst, per_pipe, status) != 0)
// 	{
// 		env_lstclear(&env_lst);
// 		command_lstclear(&per_pipe);
// 		return (1);
// 	}
//	if (execute_command_line(per_pipe, env_lst, &status) == -1)
// 	{
// 		env_lstclear(&env_lst);
// 		command_lstclear(&per_pipe);
// 		return (1);
// 	}
// 	env_lstclear(&env_lst);
// 	command_lstclear(&per_pipe);
// 	return (status);
// }
