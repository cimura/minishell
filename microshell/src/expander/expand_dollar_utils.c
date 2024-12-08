/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:32:36 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/08 16:00:01 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*env_query(t_env *env_lst, char *new, char *line_ptr, int end_status)
{
	char	*to_expand;
	char	*for_join;

	to_expand = ft_strndup(line_ptr, dollar_variable_size(line_ptr));
	if (to_expand == NULL)
		return (free(new), NULL);
	if (*line_ptr == '?')
		for_join = ft_itoa(end_status);
	else if (*to_expand == '\0')
		for_join = ft_strdup("$");
	else
		for_join = ft_strdup(get_value_from_key(env_lst, to_expand));
	free(to_expand);
	if (for_join == NULL)
		return (free(new), NULL);
	new = ft_strmerge(new, for_join);
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
