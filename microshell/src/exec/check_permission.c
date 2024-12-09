/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_permission.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:53:42 by ttakino           #+#    #+#             */
/*   Updated: 2024/12/09 15:34:53 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"

static int	dir_permission(char *arg)
{
	struct stat	st;

	if (stat(arg, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			print_error_msg("", false, arg, "Is a directory");
			return (126);
		}
		else if (access(arg, X_OK) != 0)
		{
			print_error_msg("", false, arg, "Permission denied");
			return (126);
		}
	}
	return (0);
}

int	check_permission(char **command_line)
{
	int	dir_perm;

	if (command_line[0] == NULL
		|| ft_strchr(command_line[0], '/') == NULL)
		return (0);
	dir_perm = dir_permission(command_line[0]);
	if (dir_perm != 0)
		return (dir_perm);
	if (access(command_line[0], F_OK) != 0)
	{
		print_error_msg("", false, command_line[0],
			"No such file or directory");
		return (127);
	}
	return (0);
}
