/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:17:18 by ttakino           #+#    #+#             */
/*   Updated: 2024/12/09 15:19:26 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	is_ifs_in_str(t_env *env_lst, char *str)
{
	char	*ifs;
	int		i;

	ifs = " \t\n";
	if (is_envnode_exist(env_lst, "IFS"))
		ifs = get_value_from_key(env_lst, "IFS");
	i = 0;
	while (str[i])
	{
		if (ft_strchr(ifs, str[i]))
			return (true);
		i++;
	}
	return (false);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	n;

	if (s1 == NULL || s2 == NULL)
		return (1);
	n = ft_strlen(s1);
	i = ft_strlen(s2);
	if (n < i)
		n = i;
	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
