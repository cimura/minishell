/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:26:27 by ttakino           #+#    #+#             */
/*   Updated: 2024/10/23 19:26:20 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	echo(char **arg)
{
	int	is_option;

	is_option = 0;
	if (strncmp(arg[0], "-n\0", 3) == 0)
		is_option = 1;
	if (!arg || *arg == NULL)
	{
		printf("\n");
		return ;
	}
	if (is_option)
		arg++;
	while (*arg != NULL)
	{
		printf("%s", *arg);
		if (*(arg + 1) != NULL)
			printf(" ");
		arg++;
	}
	if (!is_option)
		printf("\n");
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
