/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:26:27 by ttakino           #+#    #+#             */
/*   Updated: 2024/10/18 18:08:39 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libft/include/libft.h"

void    echo(char **arg)
{
    if (!arg || *arg == NULL)
    {    
        printf("\n");
        return;
    }
    if (strncmp(arg[0], "-n\0", 3) == 0)
    {
        arg++;
        while (*arg != NULL)
        {
            printf("%s", *arg);
            if (*(arg + 1) != NULL)
                printf(" ");
            arg++;
        }
    }
    else
    {
        while (*arg != NULL)
        {
            printf("%s", *arg);
            if (*(arg + 1) != NULL)
                printf(" ");
            arg++;
        }
        printf("\n");
    }
}

int    main(int argc, char *argv[]) {
    // char    *haystack = "d?=HOGE";
    // char    *needle = "|&;<>()$' ?\t\n";

    // int    ret = ft_strstr(haystack, needle);
    // if (ret == 0)
    //     printf("found\n");
    // if (ret == 1)
    //     printf("not found\n");

    // echo(&argv[1]);
    char **s = &argv[1];
    echo(s);
}
