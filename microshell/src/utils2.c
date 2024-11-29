/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:46:20 by ttakino           #+#    #+#             */
/*   Updated: 2024/11/29 14:49:19 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	count_key_size(char *line_ptr)
{
	int	size;

	size = 0;
	if (line_ptr[0] == '?')
		return (1);
	if (!(line_ptr[0] >= 'A' && line_ptr[0] <= 'Z') && line_ptr[0] != '_'
		&& !(line_ptr[0] >= 'a' && line_ptr[0] <= 'z'))
		return (size);
	while (line_ptr[size] != '\0' && line_ptr[size] != '=')
	{
		if (!(line_ptr[size] >= 'A' && line_ptr[size] <= 'Z')
			&& line_ptr[size] != '_'
			&& !(line_ptr[size] >= 'a' && line_ptr[size] <= 'z')
			&& !(line_ptr[size] >= '0' && line_ptr[size] <= '9'))
			return (size);
		size++;
	}
	return (size);
}

void	free_cmd_data(t_cmd_data *data)
{
	free(data->path);
	data->path = NULL;
	free_ptr_array(data->cmd);
	free(data);
	data = NULL;
}
