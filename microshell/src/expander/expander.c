/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:24:16 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/09 21:33:50 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	store_cmddata_to_newlst(t_expand_lst *current,
	char **new_cmdline, int *new_is_expanded, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		new_cmdline[i] = ft_strdup(current->str);
		if (new_cmdline[i] == NULL)
			return (free_ptr_array(new_cmdline), free(new_is_expanded), 1);
		new_is_expanded[i] = current->status;
		current = current->next;
		i++;
	}
	new_cmdline[i] = NULL;
	new_is_expanded[i] = END;
	return (0);
}

// This function frees the expand_list
static int	apply_new_command_lst(t_command_lst *per_pipe, t_expand_lst **head)
{
	char			**new_cmdline;
	int				*new_is_expanded;
	int				size;

	size = expand_lstsize(*head);
	new_is_expanded = malloc((size + 1) * sizeof(int));
	if (new_is_expanded == NULL)
		return (expand_lstclear(head), 1);
	new_cmdline = malloc((size + 1) * sizeof(char *));
	if (new_cmdline == NULL)
		return (expand_lstclear(head), free(new_is_expanded), 1);
	if (store_cmddata_to_newlst(*head, new_cmdline, new_is_expanded, size) != 0)
		return (expand_lstclear(head),
			free_ptr_array(new_cmdline), free(new_is_expanded), 1);
	free_ptr_array(per_pipe->command_line);
	per_pipe->command_line = new_cmdline;
	free(per_pipe->is_expanded);
	per_pipe->is_expanded = new_is_expanded;
	expand_lstclear(head);
	return (0);
}

static char	*expand_env_remove_quotes(t_command_lst *per_pipe,
	t_env *env_lst, int i, int end_status)
{
	char	*expanded;
	char	*tmp;

	if (i > 0 && ft_strncmp(per_pipe->command_line[i - 1], "<<", 3) == 0)
		tmp = ft_strdup(per_pipe->command_line[i]);
	else
	{
		tmp = expand_env_variable(env_lst,
				per_pipe->command_line[i], end_status);
		if (tmp && ft_strcmp(per_pipe->command_line[i], tmp) != 0)
			per_pipe->is_expanded[i] = ENV;
	}
	expanded = NULL;
	if (tmp)
		expanded = remove_quotes(tmp);
	if (expanded && ft_strcmp(tmp, expanded) != 0)
		per_pipe->is_expanded[i] += QUOTE;
	free(tmp);
	return (expanded);
}

static int	handle_quotes_env_variable(t_env *env_lst,
	t_command_lst *per_pipe, int end_status)
{
	t_expand_lst	*head;
	int				local_status;
	int				i;
	char			*expanded;

	head = NULL;
	i = 0;
	while (per_pipe->command_line[i] != NULL)
	{
		local_status = 0;
		expanded = expand_env_remove_quotes(per_pipe, env_lst, i, end_status);
		if (expanded == NULL)
			return (expand_lstclear(&head), 1);
		if (per_pipe->is_expanded[i] == ENV && is_ifs_in_str(env_lst, expanded))
			local_status = add_node_with_split_ifs(env_lst, &head, expanded);
		else if (per_pipe->is_expanded[i] != ENV || *expanded != '\0'
			|| is_envnode_exist(env_lst, &per_pipe->command_line[i][1]))
			local_status = add_new_node_expand_lst(&head,
					expanded, per_pipe->is_expanded[i]);
		if (local_status != 0)
			return (expand_lstclear(&head), free(expanded), 1);
		free(expanded);
		i++;
	}
	return (apply_new_command_lst(per_pipe, &head));
}

int	expander(t_env *env_lst, t_command_lst *per_pipe, int end_status)
{
	while (per_pipe != NULL)
	{
		if (handle_quotes_env_variable(env_lst, per_pipe,
				end_status) == 1)
			return (1);
		per_pipe = per_pipe->next;
	}
	return (0);
}
