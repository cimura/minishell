/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:32:36 by sshimura          #+#    #+#             */
/*   Updated: 2024/11/29 17:05:10 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*env_query(t_env *env_lst, char *new, char *line_ptr, int end_status)
{
	char	*to_expand;
	char	*env_value;

	to_expand = ft_strndup(line_ptr, count_key_size(line_ptr));
	if (to_expand == NULL)
		return (free(new), NULL);
	if (to_expand[0] == '?')
		env_value = ft_itoa(end_status);
	else if (line_ptr[0] == '\0' || is_whitespace(line_ptr[0]))
		env_value = ft_strdup("$");
	else
		env_value = ft_strdup(get_value_from_key(env_lst, to_expand));
	free(to_expand);
	if (env_value == NULL)
		return (free(new), NULL);
	new = ft_strmerge(new, env_value);
	return (new);
}

char	*non_expandble_str(char *new, char *line_ptr, char *stopper)
{
	char	*join_part;

	join_part = ft_strndup(line_ptr, count_until_char(line_ptr, stopper));
	if (join_part == NULL)
		return (free(new), NULL);
	new = ft_strmerge(new, join_part);
	return (new);
}

int	count_until_char(char *line, char *needle)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr(needle, line[i]) != NULL)
			return (i);
		i++;
	}
	return (i);
}
