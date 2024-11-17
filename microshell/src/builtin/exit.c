/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:53:50 by sshimura          #+#    #+#             */
/*   Updated: 2024/11/17 18:49:45 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// TODO
int	ft_exit(char **args, int *status)
{
	printf("exit\n");
	if (args == NULL || args[0] == NULL)
		return (0);
	else if (args[1] != NULL)
	{
		printf("Too many arguments\n");
		*status = 1;
		return (1);
	}
	else
		*status = ft_atoi(args[0]);
	return (*status);
}
