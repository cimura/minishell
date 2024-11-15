/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:53:50 by sshimura          #+#    #+#             */
/*   Updated: 2024/11/15 17:51:56 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// TODO
int	ft_exit(char **args)
{
	int	status;

	if (args == NULL || args[0] == NULL)
		exit(0);
	status = ft_atoi(args[0]);
	exit(status);
	return (0);
}
