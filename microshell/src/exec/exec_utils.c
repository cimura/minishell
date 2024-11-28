/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 23:54:54 by cimy              #+#    #+#             */
/*   Updated: 2024/11/28 15:30:36 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// void	print_commands(char **commands)
// {
// 	int	i;

// 	i = 0;
// 	while (commands[i])
// 	{
// 		printf("%s\n", commands[i++]);
// 	}
// }

void	free_cmd_data(t_cmd_data *data)
{
	free(data->path);
	data->path = NULL;
	free_ptr_array(data->cmd);
	free(data);
	data = NULL;
}
