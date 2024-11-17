/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:42:54 by sshimura          #+#    #+#             */
/*   Updated: 2024/11/17 19:01:17 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

// new[1]であるから，joinしないと文字列を格納できない．
// これは最初でmallocのbytesを決め打ちしないためにこうしてる

char	*get_value_from_key(t_env *env_lst, char *key)
{
	int	longer;

	if (ft_strlen(key) > ft_strlen(env_lst->key))
		longer = ft_strlen(key);
	else
		longer = ft_strlen(env_lst->key);
	while (env_lst != NULL)
	{
		if (ft_strncmp(key, env_lst->key, longer) == 0)
			return (env_lst->value);
		env_lst = env_lst->next;
	}
	return ("");
}

static int	count_key_size(char *line_ptr)
{
	int	size;

	size = 0;
	if (line_ptr[0] == '?')
		return (1);
	if (!(line_ptr[0] >= 'A' && line_ptr[0] <= 'Z') && line_ptr[0] != '_'
		&& !(line_ptr[0] >= 'a' && line_ptr[0] <= 'z'))
		return (size);
	while (line_ptr[size] != '\0' && line_ptr[size] != '=')
	{
		if (!(line_ptr[size] >= 'A' && line_ptr[size] <= 'Z')
			&& line_ptr[size] != '_'
			&& !(line_ptr[size] >= 'a' && line_ptr[size] <= 'z')
			&& !(line_ptr[size] >= '0' && line_ptr[size] <= '9'))
			return (size);
		size++;
	}
	return (size);
}

static char	*env_query(t_env *env_lst, char *new, char *line_ptr, int end_status)
{
	char	*to_expand;
	char	*env_value;
	char	*tmp;

	to_expand = ft_strndup(line_ptr, count_key_size(line_ptr));
	if (to_expand == NULL)
		return (free(new), new = NULL, NULL);
	if  (to_expand[0] == '?')
		env_value = ft_strdup(ft_itoa(end_status));	
	else if (ft_strlen(to_expand) == 0)
		env_value = "$";
	else
		env_value = get_value_from_key(env_lst, to_expand);
	free(to_expand);
	to_expand = NULL;
	tmp = ft_strjoin(new, env_value);
	if (tmp == NULL)
		return (free(new), new = NULL, NULL);
	free(new);
	new = tmp;
	return (new);
}

static char	*non_expandble_str(char *new, char *line_ptr)
{
	char	*to_dollar;
	char	*tmp;

	to_dollar = ft_strndup(line_ptr, count_until_char(line_ptr, "$"));
	if (to_dollar == NULL)
		return (free(new), new = NULL, NULL);
	tmp = ft_strjoin(new, to_dollar);
	if (tmp == NULL)
		return (free(to_dollar), to_dollar = NULL, free(new), new = NULL, NULL);
	free(to_dollar);
	to_dollar = NULL;
	free(new);
	new = tmp;
	return (new);
}

char	*expand_env_variable(t_env *env_lst, char *lst_line, int end_status)
{
	int		i;
	char	*new;

	new = malloc(1);
	new[0] = '\0';
	i = 0;
	while (lst_line[i])
	{
		if (lst_line[i] == '$')
		{
			i++;
			new = env_query(env_lst, new, &lst_line[i], end_status);
			if (new == NULL)
				return (NULL);
			i += count_key_size(&lst_line[i]);
		}
		else
		{
			new = non_expandble_str(new, &lst_line[i]);
			if (new == NULL)
				return (NULL);
			i += count_until_char(&lst_line[i], "$");
		}
	}
	return (new);
}
