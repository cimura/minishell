/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:54:22 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/09 21:49:05 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	pwd(char *save)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
		ft_putendl_fd(cwd, STDOUT_FILENO);
	else
		ft_putendl_fd(save, STDOUT_FILENO);
	free(cwd);
	return (0);
}
