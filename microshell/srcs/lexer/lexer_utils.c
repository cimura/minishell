/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:24:44 by ttakino           #+#    #+#             */
/*   Updated: 2024/10/16 17:29:40 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_token_lst_clear(t_token **lst, void (*del)(char **))
{
	t_token	*current;
	t_token	*next;

	if (lst == NULL || del == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		del(current->command_line);
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	ft_token_lstadd_back(t_token **lst, t_token *new)
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

void	ft_free_commands(char **commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		free(commands[i]);
		i++;
	}
	free(commands);
}

void	ft_print_commands(char **commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		printf("%s\n", commands[i++]);
	}
}
