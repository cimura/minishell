/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:54:04 by sshimura          #+#    #+#             */
/*   Updated: 2024/10/21 12:54:16 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "builtin.h"

void	cd(char *path)
{
	//int ret = chdir(path);
	//printf("return value is %d\n", ret);
	// success -> 0, fail -> -1;
	
	if (chdir(path) != 0)
		perror("chdir failed");
	// free(path);
}
