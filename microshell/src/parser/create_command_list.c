/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:26:46 by ttakino           #+#    #+#             */
/*   Updated: 2024/12/06 14:58:13 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

static int	add_node_from_storage(t_list **head, char *storage)
{
	t_list	*new;
	char	*content;

	if (ft_strlen(storage) == 0)
		return (0);
	content = ft_strdup(storage);
	if (content == NULL)
		return (ft_lstclear(head, free), 1);
	new = ft_lstnew(content);
	if (new == NULL)
		return (ft_lstclear(head, free), free(content), content = NULL, 1);
	ft_lstadd_back(head, new);
	ft_bzero(storage, ft_strlen(storage));
	return (0);
}

static int	case_meta(char *storage, char *line)
{
	int	i;
	int	si;

	i = 0;
	si = 0;
	while (line[i] != '\0' && ft_strchr("|&;()<>", line[i]) != NULL)
	{
		storage[si] = line[i];
		i++;
		si++;
	}
	storage[si] = '\0';
	return (i);
}

static int	case_whitespace(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && is_whitespace(line[i]))
		i++;
	return (i);
}

static int	case_normal(char *storage, char *line)
{
	int		i;
	int		si;
	char	in_quote;

	i = 0;
	si = 0;
	in_quote = 0;
	while (line[i] != '\0')
	{
		if (!in_quote && ft_strchr("\"\'", line[i]))
			in_quote = line[i];
		else if (in_quote == line[i])
			in_quote = 0;
		else if (!in_quote && ft_strchr("|&;()<> \t\v\r\f\n", line[i]) != NULL)
			break ;
		storage[si] = line[i];
		i++;
		si++;
	}
	storage[si] = '\0';
	return (i);
}

t_list	*create_t_lst(char *line)
{
	int		i;
	char	*storage;
	t_list	*head;

	storage = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	if (storage == NULL)
		return (NULL);
	head = NULL;
	i = 0;
	while (line[i] != '\0')
	{
		if (ft_strchr("|&;()<>", line[i]) != NULL)
			i += case_meta(storage, &line[i]);
		else if (ft_strchr(" \t\v\r\f\n", line[i]) != NULL)
			i += case_whitespace(&line[i]);
		else
			i += case_normal(storage, &line[i]);
		if (add_node_from_storage(&head, storage) == 1)
			return (free(storage), storage = NULL, NULL);
	}
	free(storage);
	storage = NULL;
	return (head);
}
