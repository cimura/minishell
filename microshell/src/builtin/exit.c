/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:53:50 by sshimura          #+#    #+#             */
/*   Updated: 2024/11/17 15:32:28 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// TODO
int	ft_exit(char **args)
{
	int	status;

//	if (args == NULL || args[0] == NULL)
//		exit(0);
	status = ft_atoi(args[0]);
//	exit(status);
	return (status);
}
