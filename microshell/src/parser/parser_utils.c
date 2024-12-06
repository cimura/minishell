/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:24:44 by ttakino           #+#    #+#             */
/*   Updated: 2024/12/06 15:06:53 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

void	command_lstclear(t_command_lst **lst)
{
	t_command_lst	*current;
	t_command_lst	*next;

	if (lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		free_ptr_array(current->command_line);
		free(current->is_expanded);
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	command_lstadd_back(t_command_lst **lst, t_command_lst *new)
{
	t_command_lst	*last;

	last = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
}

char	**create_until_pipe_array(t_list *normal, int size)
{
	int		i;
	char	**command_line;

	command_line = malloc((size + 1) * sizeof(char *));
	if (command_line == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		command_line[i] = ft_strdup(normal->content);
		if (command_line[i] == NULL)
			return (free_ptr_array(command_line), NULL);
		normal = normal->next;
		i++;
	}
	command_line[i] = NULL;
	return (command_line);
}

bool	*create_is_expanded_array(int size)
{
	bool	*is_expanded;
	int		i;

	is_expanded = malloc((size + 1) * sizeof(bool));
	if (is_expanded == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		is_expanded[i] = false;
		i++;
	}
	is_expanded[i] = NULL;
	return (is_expanded);
}

// debug
// void	d_print_command_lst_lst(t_command_lst *per_pipe)
// {
// 	printf("-per_pipe-\n");
// 	while (per_pipe != NULL)
// 	{
// 		d_print_char_array(per_pipe->command_line);
// 		per_pipe = per_pipe->next;
// 		if (per_pipe != NULL)
// 			printf("-------------pipe------------\n");
// 	}
// }

//void	print_commands(char **commands)
//{
//	int	i;
//
//	i = 0;
//	while (commands[i])
//	{
//		printf("%s\n", commands[i++]);
//	}
//}
