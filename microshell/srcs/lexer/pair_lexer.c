/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:40:57 by sshimura          #+#    #+#             */
/*   Updated: 2024/10/14 17:02:11 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../libft/include/libft.h"

typedef	struct s_token
{
	char	**command_line;
	struct s_token	*next;
}	t_token;

// ex
// cat infile | grep "in">outfile

void	ft_free_commands(char **commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		free(commands[i]);
		i++;
	}
	free(commands);
}

int	count_meta_char(char *line, char *meta_char)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (strchr(meta_char, line[i]))
		{
			if (line[i + 1] == line[i])
				i++;
			count++;
		}
		i++;
	}
	return (count);
}

char	*create_new_line(char *line, char *meta_char)
{
	char	*result;
	int		n_meta;
	int		ri;
	int		li;

	n_meta = count_meta_char(line, meta_char);
	// printf("count_meta: %d\n", n_meta);

	// ">" ---> " > "　三倍になる + '\0'
	result = malloc(strlen(line) + n_meta * 3 + 1);
	if (!result)
		return (NULL);
	ri = 0;
	li = 0;
	while (line[li] != '\0')
	{
		if (strchr(meta_char, line[li]))
		{
			result[ri++] = ' ';
			if (line[li + 1] == line[li])
				result[ri++] = line[li++];
			result[ri++] = line[li++];
			result[ri++] = ' ';
		}
		else
			result[ri++] = line[li++];
	}
	result[ri] = '\0';
	return (result);
}

char	**ft_lexer(char *command_line)
{
	char	*meta_char;
	char	**split_pipe;
	char	*tmp;
	int		i = 0;

	meta_char = "|&;()<>";
	split_pipe = ft_split(command_line, '|');
	if (!split_pipe)
		return (NULL);
	while (split_pipe[i] != NULL)
	{
		tmp = create_new_line(split_pipe[i], meta_char);
		if (!tmp)
			return (ft_free_commands(split_pipe), NULL);
		free(split_pipe[i]);
		split_pipe[i] = tmp;
		i++;
	}
	split_pipe[i] = NULL;
	return (split_pipe);
}

int	main(int argc, char **argv)
{
	char	**commands;
	char	*meta_char = "|&;()<>";
	int		i;

	if (argc != 2)
		return (1);

	commands = ft_lexer(argv[1]);
	if (commands == NULL)
		return (1);
	i = 0;
	while (commands[i])
	{
		printf("%s\n", commands[i]);
		i++;
	}
	ft_free_commands(commands);
	return (0);
}