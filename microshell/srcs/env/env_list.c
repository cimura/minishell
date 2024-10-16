/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:47:18 by ttakino           #+#    #+#             */
/*   Updated: 2024/10/16 15:48:52 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

typedef    struct s_env
{
    char    *key;
    char    *value;
    struct s_env    *next;
}    t_env;

int    init_key_value(t_env *new, char *line)
{
    int    len;

    len = strlen(line);
    new->key = malloc(len - strchr(line, '=') + 1);
    if (!new->key)
        return (0);
    // -1は=を飛ばす、+1は
    new->value = malloc(strlen(strchr(line, '=')) - 1 + 1);
	if (!new->value)
		return (free(new->key), new->key = NULL, 0);
	return (1);
}

t_env    *ft_env_list(char *envp[])
{
    int        i;
    t_env    *head;
    t_env    *new;

    head = NULL;

    i = 0;
    while (envp[i])
    {
        new = malloc(sizeof(t_env));
        if (!new)
            return (NULL);
        if (!init_key_value(new, line))
			return (free(new), new = NULL, NULL);
		
        i++;
    }
}

int    main(int argc, char *argv[], char *envp[])
{
    char *str = "hello, world";
    printf("%s\n", strchr(str, ','));
}