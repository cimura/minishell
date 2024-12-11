/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node_with_split_ifs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:12:52 by ttakino           #+#    #+#             */
/*   Updated: 2024/12/10 19:02:59 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	count_words(char *str, char *delimiters)
{
	int		i;
	int		c;
	bool	is_next_count;

	is_next_count = true;
	c = 0;
	i = 0;
	while (str[i])
	{
		if (is_next_count && ft_strchr(delimiters, str[i]) == NULL)
		{
			c++;
			is_next_count = false;
		}
		else if (!is_next_count && ft_strchr(delimiters, str[i]))
			is_next_count = true;
		else if (!ft_strchr(" \t\n", *str) && ft_strchr(delimiters, *str))
			c++;
		i++;
	}
	return (c);
}

static char	*pick_out_word(char *str, char *delimiters)
{
	char	*new;
	int		len;

	len = 0;
	while (ft_strchr(delimiters, str[len]) == NULL)
		len++;
	new = ft_strndup(str, len);
	if (new == NULL)
		return (NULL);
	return (new);
}

static int	register_split_ptr_array(char *str, char *delimiters, char **split)
{
	bool	is_word_head;

	is_word_head = true;
	while (*str)
	{
		if (is_word_head && ft_strchr(delimiters, *str) == NULL)
		{
			*split = pick_out_word(str, delimiters);
			if (*split == NULL)
				return (1);
			is_word_head = false;
			split++;
		}
		else if (!is_word_head && ft_strchr(delimiters, *str))
			is_word_head = true;
		else if (!ft_strchr(" \t\n", *str) && ft_strchr(delimiters, *str))
		{
			*split = ft_strdup("");
			if (*split == NULL)
				return (1);
			split++;
		}
		str++;
	}
	return (*split = NULL, 0);
}

static char	**ft_split_multi_delimiters(char *str, char *delimiters)
{
	char	**split;

	split = malloc((count_words(str, delimiters) + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	if (register_split_ptr_array(str, delimiters, split) != 0)
		return (free_ptr_array(split), NULL);
	return (split);
}

int	add_node_with_split_ifs(t_env *env_lst, t_expand_lst **head, char *expand)
{
	t_expand_lst	*current;
	char			*delimiters;
	char			**split;
	int				i;

	delimiters = get_value_from_key(env_lst, "IFS");
	if (!is_envnode_exist(env_lst, "IFS"))
		delimiters = " \t\n";
	split = ft_split_multi_delimiters(expand, delimiters);
	if (split == NULL)
		return (1);
	i = 0;
	while (split[i])
	{
		current = expand_lstnew(split[i], ENV);
		if (current == NULL)
			return (free_ptr_array(split), 1);
		expand_lstadd_back(head, current);
		i++;
	}
	free_ptr_array(split);
	return (0);
}
