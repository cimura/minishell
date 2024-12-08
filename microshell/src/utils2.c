/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:46:20 by ttakino           #+#    #+#             */
/*   Updated: 2024/12/08 16:00:01 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	dollar_variable_size(char *line_ptr)
{
	int	size;

	size = 0;
	if (line_ptr[0] == '?')
		return (1);
	if (!(line_ptr[0] >= 'A' && line_ptr[0] <= 'Z') && line_ptr[0] != '_'
		&& !(line_ptr[0] >= 'a' && line_ptr[0] <= 'z'))
		return (size);
	while (line_ptr[size] != '\0' && line_ptr[size] != '=')
	{
		if (!(line_ptr[size] >= 'A' && line_ptr[size] <= 'Z')
			&& line_ptr[size] != '_'
			&& !(line_ptr[size] >= 'a' && line_ptr[size] <= 'z')
			&& !(line_ptr[size] >= '0' && line_ptr[size] <= '9'))
			return (size);
		size++;
	}
	return (size);
}

void	free_cmd_data(t_cmd_data *data)
{
	free(data->path);
	data->path = NULL;
	free_ptr_array(data->cmd);
	free(data);
	data = NULL;
}

bool	is_redirection(char *arg)
{
	if (ft_strncmp(arg, ">", 2) == 0
		|| ft_strncmp(arg, ">>", 3) == 0
		|| ft_strncmp(arg, "<", 2) == 0
		|| ft_strncmp(arg, "<<", 3) == 0)
		return (true);
	else
		return (false);
}

void	clear_exit(t_env *env_lst, t_command_lst *per_pipe, int exit_status)
{
	env_lstclear(&env_lst);
	command_lstclear(&per_pipe);
	exit(exit_status);
}

void	print_error_msg(char *cmd_name, bool arg_decorate,
	char *arg_name, char *err_msg)
{
	int		pure_stdout;
	char	*cmd_separator;
	char	*arg_separator;

	cmd_separator = ": ";
	arg_separator = ": ";
	if (cmd_name[0] == '\0')
		cmd_separator = "";
	if (arg_name[0] == '\0')
		arg_separator = "";
	pure_stdout = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (arg_decorate)
		printf("minishell: %s%s`%s'%s%s\n",
			cmd_name, cmd_separator, arg_name, arg_separator, err_msg);
	else
		printf("minishell: %s%s%s%s%s\n",
			cmd_name, cmd_separator, arg_name, arg_separator, err_msg);
	dup2(pure_stdout, STDOUT_FILENO);
	close(pure_stdout);
}
