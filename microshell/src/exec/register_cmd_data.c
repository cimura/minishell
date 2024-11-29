/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_cmd_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:04:16 by cimy              #+#    #+#             */
/*   Updated: 2024/11/29 16:58:30 by ttakino          ###   ########.fr       */
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
		if (access(candidate, X_OK) == 0)
		{
			*path = candidate;
			break ;
		}
		free(candidate);
		i++;
	}
	return (0);
}

static int	register_path(char *cmd, char **path, t_env *env_lst)
{
	char	*env_path;
	char	**com_sep;

	*path = NULL;
	if (access(cmd, X_OK) == 0)
	{
		*path = ft_strdup(cmd);
		if (*path == NULL)
			return (1);
		return (0);
	}
	env_path = get_value_from_key(env_lst, "PATH");
	com_sep = ft_split(env_path, ':');
	if (com_sep == NULL)
		return (1);
	if (set_cmd_in_path(cmd, com_sep, path) == 1)
		return (free_ptr_array(com_sep), 1);
	free_ptr_array(com_sep);
	return (0);
}

static bool	is_redirection(char *word)
{
	if (ft_strncmp(word, ">", 2) == 0
		|| ft_strncmp(word, ">>", 3) == 0
		|| ft_strncmp(word, "<", 2) == 0
		|| ft_strncmp(word, "<<", 3) == 0)
		return (true);
	return (false);
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

t_cmd_data	*register_cmd_data(t_token *token, t_env *env_lst)
{
	t_cmd_data	*cmd_data;

	cmd_data = malloc(sizeof(t_cmd_data));
	if (cmd_data == NULL)
		return (NULL);
	if (register_path(token->command_line[0], &(cmd_data->path), env_lst) != 0)
		return (free(cmd_data), NULL);
	cmd_data->cmd = filter_cmd_args(&token->command_line[0]);
	if (cmd_data->cmd == NULL)
		return (free(cmd_data->path), free(cmd_data), NULL);
	return (cmd_data);
}
