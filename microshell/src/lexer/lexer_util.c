/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:24:44 by ttakino           #+#    #+#             */
/*   Updated: 2024/11/28 18:48:39 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	token_lstclear(t_token **lst)
{
	t_token	*current;
	t_token	*next;

	if (lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		free_ptr_array(current->command_line);
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	token_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

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
// void	d_print_token_lst(t_token *token)
// {
// 	printf("-token-\n");
// 	while (token != NULL)
// 	{
// 		d_print_char_array(token->command_line);
// 		token = token->next;
// 		if (token != NULL)
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
