/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_cmd_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:04:16 by cimy              #+#    #+#             */
/*   Updated: 2024/12/03 18:33:28 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "env_lst.h"
#include "utils.h"

static int	set_cmd_in_path(char *cmd, char **com_sep, char **path)
{
	char	*segment;
	char	*candidate;
	int		i;

	if (ft_strchr(cmd, '/') != NULL)
		return (0);
	i = 0;
	while (com_sep[i])
	{
		segment = ft_strjoin(com_sep[i], "/");
		if (segment == NULL)
			return (1);
		candidate = ft_strjoin(segment, cmd);
		if (candidate == NULL)
			return (free(segment), 1);
		free(segment);
		if (access(candidate, F_OK) == 0)
		{
			*path = candidate;
			break ;
		}
		free(candidate);
		i++;
	}
	return (0);
}

#define PATH_NOT_FOUND 127

static int	register_path(char *cmd, char **path, t_env *env_lst)
{
	char	*env_path;
	char	**com_sep;

	*path = NULL;
	env_path = get_value_from_key(env_lst, "PATH");
	if (env_path[0] == '\0')
	{
		print_error_msg(cmd, NULL, "No such file or directory");
		return (PATH_NOT_FOUND);
	}
	com_sep = ft_split(env_path, ':');
	if (com_sep == NULL)
		return (1);
	if (set_cmd_in_path(cmd, com_sep, path) == 1)
		return (free_ptr_array(com_sep), 1);
	free_ptr_array(com_sep);
	if (*path == NULL && ft_strchr(cmd, '/') != NULL && access(cmd, X_OK) == 0)
	{
		*path = ft_strdup(cmd);
		if (*path == NULL)
			return (1);
	}
	return (0);
}

static char	**filter_cmd_args(char **head_cmdline)
{
	int		i;
	int		ri;
	int		size;
	char	**result;

	size = count_char_array_words(head_cmdline);
	result = malloc((size + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	i = 0;
	ri = 0;
	while (i < size)
	{
		if (is_redirection(head_cmdline[i]))
		{
			i += 2;
			continue ;
		}
		result[ri] = ft_strdup(head_cmdline[i++]);
		if (result[ri] == NULL)
			return (free_ptr_array(result), NULL);
		ri++;
	}
	result[ri] = NULL;
	return (result);
}

t_cmd_data	*register_cmd_data(t_command_lst *per_pipe,
	t_env *env_lst, int *status)
{
	t_cmd_data	*cmd_data;

	*status = 0;
	cmd_data = malloc(sizeof(t_cmd_data));
	if (cmd_data == NULL)
		return (*status = 1, NULL);
	cmd_data->path = NULL;
	if (!is_builtin(per_pipe->command_line))
	{
		*status = register_path(per_pipe->command_line[0],
				&(cmd_data->path), env_lst);
		if (*status == 1)
			return (free(cmd_data), NULL);
		else if (*status == PATH_NOT_FOUND)
			return (free(cmd_data), NULL);
	}
	cmd_data->cmd = filter_cmd_args(&per_pipe->command_line[0]);
	if (cmd_data->cmd == NULL)
		return (*status = 1, free(cmd_data->path), free(cmd_data), NULL);
	return (cmd_data);
}
