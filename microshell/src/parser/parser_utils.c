/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:24:44 by ttakino           #+#    #+#             */
/*   Updated: 2024/12/06 13:52:10 by ttakino          ###   ########.fr       */
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
