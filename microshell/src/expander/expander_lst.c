/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 16:27:45 by ttakino           #+#    #+#             */
/*   Updated: 2024/12/09 18:15:03 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "syntax.h"

int	add_new_node_expand_lst(t_expand_lst **head,
	char *expanded, int is_expanded)
{
	t_expand_lst	*current;

	current = expand_lstnew(expanded, is_expanded);
	if (current == NULL)
		return (1);
	expand_lstadd_back(head, current);
	return (0);
}

void	expand_lstadd_back(t_expand_lst **head, t_expand_lst *new)
{
	t_expand_lst	*last;

	last = *head;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
}

void	expand_lstclear(t_expand_lst **head)
{
	t_expand_lst	*current;
	t_expand_lst	*next;

	if (head == NULL)
		return ;
	current = *head;
	while (current != NULL)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
	*head = NULL;
}

t_expand_lst	*expand_lstnew(char	*str, int status)
{
	t_expand_lst	*new;

	new = malloc(sizeof(t_expand_lst));
	if (new == NULL)
		return (NULL);
	new->str = ft_strdup(str);
	if (new->str == NULL)
		return (free(new), NULL);
	new->status = status;
	new->next = NULL;
	return (new);
}

int	expand_lstsize(t_expand_lst *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

// int	main(int argc, char *argv[], char *envp[])
// {
// 	t_env			*env_lst;
// 	t_command_lst	*per_pipe;
// 	int				i;

// 	if (argc == 1)
// 		return (0);
// 	env_lst = create_env_lst(envp);
// 	if (env_lst == NULL)
// 	{
// 		ft_putendl_fd("cannot create env_lst", 2);
// 		return (1);
// 	}
// 	i = 1;
// 	while (argv[i] != NULL)
// 	{
// 		per_pipe = parser(argv[i]);
// 		if (per_pipe == NULL)
// 		{
// 			env_lstclear(&env_lst);
// 			ft_putendl_fd("cannot create token list", 2);
// 			return (1);
// 		}
// 		printf("before\n");
// 		d_print_per_pipe(per_pipe);
// 		printf("\n");
// 		if (handle_quotes_env_variable(env_lst, per_pipe, 0) != 0)
// 		{
// 			env_lstclear(&env_lst);
// 			command_lstclear(&per_pipe);
// 			ft_putendl_fd("expander failed", 2);
// 			return (1);
// 		}
// 		printf("after\n");
// 		d_print_per_pipe(per_pipe);
// 		command_lstclear(&per_pipe);
// 		i++;
// 	}
// 	env_lstclear(&env_lst);
// 	return (0);
// }
