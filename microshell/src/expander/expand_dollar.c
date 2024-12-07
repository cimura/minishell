/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:42:54 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/05 16:10:19 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	*single_quotes(char *new, char *line_ptr)
{
	new = ft_strmerge(new, ft_strdup("\'"));
	if (new == NULL)
		return (NULL);
	new = non_expandble_str(new, line_ptr, "\'");
	new = ft_strmerge(new, ft_strdup("\'"));
	return (new);
}

static char	*double_quotes(t_env *env_lst, char *new,
	char *line_ptr, int end_status)
{
	int	i;

	new = ft_strmerge(new, ft_strdup("\""));
	line_ptr = non_expandble_str(ft_strdup(""), line_ptr, "\"");
	if (new == NULL || line_ptr == NULL)
		return (NULL);
	i = 0;
	while (line_ptr[i])
	{
		if (line_ptr[i] == '$')
		{
			new = env_query(env_lst, new, &line_ptr[++i], end_status);
			i += count_dollar_variable_size(&line_ptr[i]);
		}
		else
		{
			new = non_expandble_str(new, &line_ptr[i], "$");
			i += count_until_char(&line_ptr[i], "$");
		}
		if (new == NULL)
			return (NULL);
	}
	free(line_ptr);
	new = ft_strmerge(new, ft_strdup("\""));
	return (new);
}

static char	*join_expanded_word(char *new, t_env *env_lst,
	char *line, int end_status)
{
	if (line[0] == '$')
		new = env_query(env_lst, new, &line[1], end_status);
	else if (line[0] == '~' && line[1] == '/')
		new = ft_strmerge(new, ft_strdup(get_value_from_key(env_lst, "HOME")));
	else if (line[0] == '\'')
		new = single_quotes(new, &line[1]);
	else if (line[0] == '\"')
		new = double_quotes(env_lst, new, &line[1], end_status);
	else
		new = non_expandble_str(new, &line[0], "$\'\"");
	if (new == NULL)
		return (NULL);
	return (new);
}

static int	skip_joined_word(char *line_ptr)
{
	if (line_ptr[0] == '$')
		return (count_dollar_variable_size(&line_ptr[1]) + 1);
	else if (line_ptr[0] == '\'')
		return (count_until_char(&line_ptr[1], "\'") + 2);
	else if (line_ptr[0] == '\"')
		return (count_until_char(&line_ptr[1], "\"") + 2);
	else if (line_ptr[0] == '~' && line_ptr[1] == '/')
		return (1);
	else
		return (count_until_char(line_ptr, "$\'\""));
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
		new = join_expanded_word(new, env_lst, &line[i], end_status);
		if (new == NULL)
			return (NULL);
		i += skip_joined_word(&line[i]);
	}
	return (new);
}
