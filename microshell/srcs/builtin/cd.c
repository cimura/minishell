/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:54:04 by sshimura          #+#    #+#             */
/*   Updated: 2024/10/23 19:26:55 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	cd(char **args)
{
	if (args[0] == NULL)
		return (0);
	else if (args[1] != NULL)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	if (chdir(args[0]) != 0)
	{
		perror(args[0]);
		return (1);
	}
	return (0);
}

//int	main(int argc, char **argv)
//{
//	int	status;
//	(void)argc;
//	printf("Before: ");
//	pwd();
//	status = cd(&argv[1]);
//	printf("After: ");
//	pwd();
//	return (status);
//}
