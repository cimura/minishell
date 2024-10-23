/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:54:22 by sshimura          #+#    #+#             */
/*   Updated: 2024/10/21 12:54:25 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "builtin.h"

void	pwd(void)
{
	char *cwd;

	//cwd = malloc(100);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd failed");
		return ;
	}
	printf("%s\n", cwd);
	free(cwd);
}
