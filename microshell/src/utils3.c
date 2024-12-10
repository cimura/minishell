/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:17:18 by ttakino           #+#    #+#             */
/*   Updated: 2024/12/10 17:32:29 by sshimura         ###   ########.fr       */
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

int	ft_strcpy(char *dst, char *src, int size)
{
	int	i;

	i = 0;
	if (size <= 0)
		return (0);
	while (src[i] != '\0' && i < size)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

int	init_mobile(t_env *env_lst, t_mobile *mobile)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		ft_putendl_fd("shell-init: error retrieving current directory: "
			"getcwd: cannot access parent directories: "
			"No such file or directory", STDERR_FILENO);
		env_lstclear(&env_lst);
		exit(EXIT_FAILURE);
	}
	mobile->cwd = cwd;
	if (mobile->cwd == NULL)
	{
		env_lstclear(&env_lst);
		exit(EXIT_FAILURE);
	}
	mobile->status = 0;
	return (0);
}
