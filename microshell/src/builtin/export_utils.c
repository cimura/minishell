/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:55:45 by sshimura          #+#    #+#             */
/*   Updated: 2024/11/29 17:04:08 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

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

int	generate_new_value(t_env *old_node, char *arg)
{
	char	*new_value;

	if (ft_strchr(arg, '=') == NULL)
	{
		return (0);
	}
	if (is_plus_exist(arg))
		new_value = ft_strjoin(old_node->value, ft_strchr(arg, '=') + 1);
	else
		new_value = ft_strdup(ft_strchr(arg, '=') + 1);
	if (new_value == NULL)
		return (1);
	free(old_node->value);
	old_node->value = new_value;
	return (0);
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
	new->key = ft_strndup(arg, klen);
	if (new->key == NULL)
		return (free(new), NULL);
	new->next = NULL;
	if (ft_strchr(arg, '=') == NULL)
	{
		new->value = NULL;
		return (new);
	}
	vlen = ft_strlen(ft_strchr(arg, '=') + 1);
	new->value = ft_strndup(ft_strchr(arg, '=') + 1, vlen);
	if (new->value == NULL)
		return (free(new->key), NULL);
	return (new);
}
