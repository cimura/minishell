/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:08:10 by sshimura          #+#    #+#             */
/*   Updated: 2024/10/23 18:02:34 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_expand_lst	*create_quoted_lst(char *line)
{
	int				i;
	t_expand_lst	*new;
	t_expand_lst	*head;

	if (str_count(line, "\'") % 2 != 0
		|| str_count(line, "\"") % 2 != 0)
		return (NULL);
	head = NULL;
	i = 0;
	while (line[i])
	{
		new = malloc(sizeof(t_expand_lst));
		if (new == NULL)
			return (expand_lstclear(&head), NULL);
		if (line[i] == '\'')
			i += split_quoted_segment(new, head, &line[++i], SINGLE);
		else if (line[i] == '\"')
			i += split_quoted_segment(new, head, &line[++i], DOUBLE);
		else
			i += split_quoted_segment(new, head, &line[i], OUT);
		new->next = NULL;
		expand_lstadd_back(&head, new);
	}
	return (head);
}

int	handle_doller_expand(t_expand_lst *expand_lst)
{
	char	*old;

	while (expand_lst != NULL)
	{
		if (expand_lst->status != SINGLE)
		{
			old = expand_lst->str;
			expand_lst->str = expand_env_variable(expand_lst->str);
			if (expand_lst->str == NULL)
				return (free(old), old = NULL, 1);
			free(old);
			old = NULL;
		}
		expand_lst = expand_lst->next;
	}
	return (0);
}

// hello -> wo -> world
// 最初の要素だけコピーしてあとはjoin, NULLチェックは必要
static char	*join_lst(t_expand_lst *expand_lst)
{
	char	*result;
	char	*tmp;

	result = ft_strdup(expand_lst->str);
	if (result == NULL)
		return (NULL);
	expand_lst = expand_lst->next;
	while (expand_lst != NULL)
	{
		tmp = ft_strjoin(result, expand_lst->str);
		if (tmp == NULL)
			return (NULL);
		free(result);
		result = tmp;
		expand_lst = expand_lst->next;
	}
	return (result);
}

// この関数を呼べば展開されて返ってくる
char	*expander(char *line)
{
	t_expand_lst	*expand_lst;
	char			*result;

	expand_lst = create_quoted_lst(line);
	if (!expand_lst)
		return (NULL);
	if (handle_doller_expand(expand_lst) == 1)
	{
		expand_lstclear(&expand_lst);
		return (NULL);
	}
	result = join_lst(expand_lst);
	expand_lstclear(&expand_lst);
	return (result);
}

// int	main()
// {
// 	char	*line = "hello \'wo\'$PATH world\"!!!\"";

// 	char *result_line = expander(line);
// 	printf("%s\n", result_line);
// 	free(result_line);
// }
