/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:26:27 by ttakino           #+#    #+#             */
/*   Updated: 2024/11/26 14:50:23 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

int	echo(char **args)
{
	int	is_option;
	int	i;

	is_option = 0;
	i = 0;
	if (args == NULL || args[0] == NULL)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	if (ft_strncmp(args[0], "-n", 3) == 0)
		is_option = 1;
	if (is_option)
		i++;

	while (args[i] != NULL)
	{
		// printf("args[%d]: %s\n", i, args[i]);
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (is_option != 1)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

// int    main(int argc, char *argv[]) {
//    // char    *haystack = "d?=HOGE";
//    // char    *needle = "|&;<>()$' ?\t\n";

//    // int    ret = ft_strstr(haystack, needle);
//    // if (ret == 0)
//    //     printf("found\n");
//    // if (ret == 1)
//    //     printf("not found\n");

//    // echo(&argv[1]);
//    char **s = &argv[1];
//    echo(s);
// }
