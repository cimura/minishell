/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_empty.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:13:57 by ttakino           #+#    #+#             */
/*   Updated: 2024/11/23 20:28:54 by ttakino          ###   ########.fr       */
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

char	**create_new_cmdline(char **old_cmdline)
{
	int		i;
	char	**new_cmdline;
	int		ni;

	new_cmdline = malloc((count_valid_words(old_cmdline) + 1)
			* sizeof(char *));
	if (new_cmdline == NULL)
		return (NULL);
	i = 0;
	ni = 0;
	while (old_cmdline[i] != NULL)
	{
		if (old_cmdline[i][0] == '\0')
		{
			i++;
			continue ;
		}
		new_cmdline[ni] = ft_strdup(old_cmdline[i]);
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
		new_cmdline = create_new_cmdline(token->command_line);
		if (new_cmdline == NULL)
			return (1);
		free_ptr_array(token->command_line);
		token->command_line = new_cmdline;
		token = token->next;
	}
	return (0);
}
