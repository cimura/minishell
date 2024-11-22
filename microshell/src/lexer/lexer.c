/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:06:34 by ttakino           #+#    #+#             */
/*   Updated: 2024/11/13 23:52:07 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
// #include "expander.h"

static int	count_token_until_pipe(t_list *lst)
{
	int	size;

	size = 0;
	while (lst != NULL && ft_strncmp(lst->content, "|", 1) != 0)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

static char	**create_until_pipe_array(t_list *normal, int size)
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

static t_token	*create_pipe_lst(t_list *normal)
{
	int		size;
	t_token	*new;
	t_token	*head;

	head = NULL;
	while (normal != NULL)
	{
		if (ft_strncmp(normal->content, "|", 1) == 0)
			normal = normal->next;
		new = malloc(sizeof(t_token));
		if (new == NULL)
			return (token_lstclear(&head), NULL);
		size = count_token_until_pipe(normal);
		new->command_line = create_until_pipe_array(normal, size);
		if (new->command_line == NULL)
			return (token_lstclear(&head), free(new), NULL);
		new->next = NULL;
		token_lstadd_back(&head, new);
		while (size > 0)
		{
			normal = normal->next;
			size--;
		}
	}
	return (head);
}

t_token	*lexer(char	*line)
{
	t_list	*normal;
	t_token	*per_pipe;

	normal = create_token_lst(line);
	if (normal == NULL)
		return (NULL);
	per_pipe = create_pipe_lst(normal);
	if (per_pipe == NULL)
		return (ft_lstclear(&normal, free), NULL);
	ft_lstclear(&normal, free);
	return (per_pipe);
}

// int	main(int argc, char **argv)
// {
// 	t_token	*head;
// 	t_token	*words;
// 	int	i;
// 	int	j;

// 	if (argc == 1)
// 		return (0);
// 	i = 1;
// 	while (argv[i] != NULL)
// 	{
// 		// printf("\x1b[36m%s\n\x1b[0m", argv[i]);
// 		words = lexer(argv[i]);
// 		if (words == NULL)
// 			return (printf("Error\n"), 1);
// 		head = words;
// 		while (words != NULL)
// 		{
// 			j = 0;
// 			while (words->command_line[j] != NULL)
// 			{
// 				printf("%s", words->command_line[j++]);
// 				if (words->command_line[j] != NULL)
// 					printf(",");
// 			}
// 			words = words->next;
// 			if (words != NULL)
// 				printf("\t");
// 		}
// 		token_lstclear(&head);
// 		i++;
// 	}
// 	return (0);
// }
