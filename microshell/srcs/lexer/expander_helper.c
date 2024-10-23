/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:42:54 by sshimura          #+#    #+#             */
/*   Updated: 2024/10/23 18:05:02 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

// new[1]であるから，joinしないと文字列を格納できない．
// これは最初でmallocのbytesを決め打ちしないためにこうしてる

char	*env_query(char *new, char *line_ptr)
{
	char	*to_expand;
	char	*env_value;
	char	*tmp;

	to_expand = ft_strndup(line_ptr, count_until_char(line_ptr, " \t\n*"));
	if (!to_expand)
		return (free(new), new = NULL, NULL);
	env_value = getenv(to_expand);
	if (!env_value)
		env_value = "";
	free(to_expand);
	to_expand = NULL;
	tmp = ft_strjoin(new, env_value);
	if (!tmp)
		return (free(new), new = NULL, NULL);
	free(new);
	new = tmp;
	return (new);
}

char	*non_expandble_str(char *new, char *line_ptr)
{
	int		len;
	char	*tmp;

	len = strlen(new);
	tmp = ft_strjoin(new, line_ptr);
	if (tmp == NULL)
		return (free(new), new = NULL, NULL);
	free(new);
	new = tmp;
	new[len + 1] = '\0';
	return (new);
}

char	*expand_env_variable(char *lst_line)
{
	int		i;
	int		len;
	char	*new;

	new = malloc(1);
	new[0] = '\0';
	i = 0;
	while (lst_line[i])
	{
		if (lst_line[i] == '$')
		{
			i++;
			new = env_query(new, &lst_line[i]);
			i += count_until_char(&lst_line[i], " \t\n*");
		}
		else
		{
			new = non_expandble_str(new, &lst_line[i]);
			i++;
		}
	}
	len = ft_strlen(new);
	new[len] = '\0';
	return (new);
}

int	split_quoted_segment(t_expand_lst *new, t_expand_lst *head,
							char *line_ptr, int flag)
{
	if (flag == SINGLE)
	{
		new->status = SINGLE;
		new->str = ft_strndup(line_ptr, count_until_char(line_ptr, "\'"));
		if (new->str == NULL)
			return (expand_lstclear(&head), free(new), new = NULL, -1);
		return (count_until_char(line_ptr, "\'") + 1);
	}
	else if (flag == DOUBLE)
	{
		new->status = DOUBLE;
		new->str = ft_strndup(line_ptr, count_until_char(line_ptr, "\""));
		if (new->str == NULL)
			return (expand_lstclear(&head), free(new), new = NULL, -1);
		return (count_until_char(line_ptr, "\"") + 1);
	}
	else
	{
		new->status = OUT;
		new->str = ft_strndup(line_ptr, count_until_char(line_ptr, "\'\""));
		if (new->str == NULL)
			return (expand_lstclear(&head), free(new), new = NULL, -1);
		return (count_until_char(line_ptr, "\'\""));
	}
}
