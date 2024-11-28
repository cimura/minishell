/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:42:54 by sshimura          #+#    #+#             */
/*   Updated: 2024/11/28 15:00:12 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

// new[1]であるから，joinしないと文字列を格納できない．
// これは最初でmallocのbytesを決め打ちしないためにこうしてる

static char	*env_query(t_env *env_lst, char *new, char *line_ptr, int end_status)
{
	char	*to_expand;
	char	*env_value;

	to_expand = ft_strndup(line_ptr, count_key_size(line_ptr));
	if (to_expand == NULL)
		return (free(new), NULL);
	if  (to_expand[0] == '?')
		env_value = ft_itoa(end_status);
	else if (line_ptr[0] == '\0' || white_space(line_ptr[0]) == 1)
		env_value = ft_strdup("$");
	else
		env_value = ft_strdup(get_value_from_key(env_lst, to_expand));
	free(to_expand);
	if (env_value == NULL)
		return (free(new), NULL);
	new = ft_strmerge(new, env_value);
	return (new);
}

static char	*non_expandble_str(char *new, char *line_ptr, char *stopper)
{
	char	*join_part;

	join_part = ft_strndup(line_ptr, count_until_char(line_ptr, stopper));
	if (join_part == NULL)
		return (free(new), NULL);
	new = ft_strmerge(new, join_part);
	return (new);
}

static char	*single_quotes(char *new, char *line_ptr)
{
	new = ft_strmerge(new, ft_strdup("\'"));
	if (new == NULL)
		return (NULL);
	new = non_expandble_str(new, line_ptr, "\'");
	new = ft_strmerge(new, ft_strdup("\'"));
	return (new);
}

static char	*double_quotes(t_env *env_lst, char *new, char *line_ptr, int end_status)
{
	int	i;

	new = ft_strmerge(new, ft_strdup("\""));
	line_ptr = non_expandble_str(ft_strdup(""), line_ptr, "\"");
	if (new == NULL || line_ptr == NULL)
		return (NULL);
	i = 0;
	//printf("line_ptr=%c\n", line_ptr[0]);
	//printf("line_ptr: %s\n", line_ptr);
	while (line_ptr[i])
	{
		if (line_ptr[i] == '$')
		{
			i++;
			new = env_query(env_lst, new, &line_ptr[i], end_status);
			i += count_key_size(&line_ptr[i]);
		}
		else
		{
			new = non_expandble_str(new, &line_ptr[i], "$");
			i += count_until_char(&line_ptr[i], "$");
		}
		if (new == NULL)
			return (NULL);
	}
	new = ft_strmerge(new, ft_strdup("\""));
	return (new);
}

char	*expand_env_variable(t_env *env_lst, char *line, int end_status)
{
	int		i;
	char	*new;

	new = ft_strdup("");
	if (new == NULL)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			new = env_query(env_lst, new, &line[i], end_status);
			i += count_key_size(&line[i]);
		}
		else if (line[i] == '\'')
		{
			i++;
			new = single_quotes(new, &line[i]);
			i += count_until_char(&line[i], "\'") + 1;
		}
		else if (line[i] == '\"')
		{
			i++;
			new = double_quotes(env_lst, new, &line[i], end_status);
			i += count_until_char(&line[i], "\"") + 1;
		}
		else
		{
			new = non_expandble_str(new, &line[i], "$\'\"");
			i += count_until_char(&line[i], "$\'\"");
		}
		if (new == NULL)
		return (NULL);
	}
	// printf("new: %s\n", new);
	return (new);
}
