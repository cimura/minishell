/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_empty.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:13:57 by ttakino           #+#    #+#             */
/*   Updated: 2024/11/23 19:59:08 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"
#include "utils.h"

static int	count_valid_words(char **command_line)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	while (command_line[i] != NULL)
	{
		if (ft_strlen(command_line[i]) > 0)
			c++;
		i++;
	}
	return (c);
}

static char	**set_new_cmdline(char **command_line, char **new_cmdline)
{
	int	i;
	int	ni;

	i = 0;
	ni = 0;
	while (command_line[i] != NULL)
	{
		if (command_line[i][0] == '\0')
		{
			i++;
			continue ;
		}
		new_cmdline[ni] = ft_strdup(command_line[i]);
		if (new_cmdline[ni] == NULL)
			return (free_ptr_array(new_cmdline), NULL);
		i++;
		ni++;
	}
	new_cmdline[ni] = NULL;
	return (new_cmdline);
}

int	stash_token_empty_ptrs(t_token *token)
{
	char	**new_cmdline;

	while (token != NULL)
	{
		new_cmdline = malloc(count_valid_words(token->command_line)
				* sizeof(char *));
		if (new_cmdline == NULL)
			return (1);
		new_cmdline = set_new_cmdline(token->command_line, new_cmdline);
		if (new_cmdline == NULL)
			return (1);
		free_ptr_array(token->command_line);
		token->command_line = new_cmdline;
		token = token->next;
	}
	return (0);
}
