/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:55:45 by sshimura          #+#    #+#             */
/*   Updated: 2024/11/26 16:41:43 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	is_plus_exist(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0' && arg[i] != '=')
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (true);
		i++;
	}
	return (false);
}

char	*generate_new_value(char *old_value, char *arg)
{
	char	*new_value;

	if (is_plus_exist(arg))
		new_value = ft_strjoin(old_value, ft_strchr(arg, '=') + 1);
	else
		new_value = ft_strdup(ft_strchr(arg, '=') + 1);
	free(old_value);
	if (new_value == NULL)
		return (NULL);
	return (new_value);
}

static int	count_keylen(char *str)
{
	int	c;

	c = 0;
	while (str[c] != '\0' && str[c] != '+' && str[c] != '=')
		c++;
	return (c);
}

t_env	*create_new_env_node(char *arg)
{
	t_env	*new;
	int		klen;
	int		vlen;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	klen = count_keylen(arg);
	vlen = ft_strlen(ft_strchr(arg, '=') + 1);
	new->key = ft_strndup(arg, klen);
	if (new->key == NULL)
		return (free(new), NULL);
	new->value = ft_strndup(ft_strchr(arg, '=') + 1, vlen);
	if (new->value == NULL)
		return (free(new->key), NULL);
	new->next = NULL;
	return (new);
}


