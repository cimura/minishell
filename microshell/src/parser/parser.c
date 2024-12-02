/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:06:34 by ttakino           #+#    #+#             */
/*   Updated: 2024/12/02 14:16:05 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

static int	count_command_lst_until_pipe(t_list *lst)
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

static t_command_lst	*create_pipe_lst(t_list *normal)
{
	int				size;
	t_command_lst	*new;
	t_command_lst	*head;

	head = NULL;
	while (normal != NULL)
	{
		if (ft_strncmp(normal->content, "|", 1) == 0)
			normal = normal->next;
		new = malloc(sizeof(t_command_lst));
		if (new == NULL)
			return (command_lstclear(&head), NULL);
		size = count_command_lst_until_pipe(normal);
		new->command_line = create_until_pipe_array(normal, size);
		if (new->command_line == NULL)
			return (command_lstclear(&head), free(new), NULL);
		new->next = NULL;
		command_lstadd_back(&head, new);
		while (size > 0)
		{
			normal = normal->next;
			size--;
		}
	}
	return (head);
}

t_command_lst	*parser(char	*line)
{
	t_list			*normal;
	t_command_lst	*per_pipe;

	normal = create_command_lst(line);
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
// 	t_command_lst	*head;
// 	t_command_lst	*words;
// 	int	j;

// 	if (argc == 1)
// 		return (0);
//   words = parser(argv[1]);
//   if (words == NULL)
//     return (printf("Error\n"), 1);
//   head = words;
//   while (words != NULL)
//   {
//     j = 0;
//     while (words->command_line[j] != NULL)
//     {
//       printf("%s", words->command_line[j]);
//       if (words->command_line[j] != NULL)
//         printf(",");
//       j++;
//     }
//     words = words->next;
//     if (words != NULL)
//       printf("\n");
//   }
//   command_lstclear(&head);
// 	return (0);
// }
