/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:48:04 by ttakino           #+#    #+#             */
/*   Updated: 2024/10/12 18:15:36 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "micro.h"

// デバッグ用にmain書いて単体で実行してる -後で消す
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_count_command(char *line)
{
	int		cnt;
	int		i;
	char	*meta_c;
	int		flag;

	meta_c = "|&;()<>";
	flag = 0;
	cnt = 0;
	printf("line: %s\n", line);
	i = 0;
	while (line[i] != '\0')
	{
		if (flag && strchr(meta_c, line[i]))
		{
			cnt += 2;
			flag = 0;
		}
		if (line[i] == ' ' || line[i] == '\t')
		{
			cnt++;
			flag = 0;
		}
		else
			flag = 1;
		i++;
	}
	cnt++;
	return (cnt);
}

int	ft_strlen_meta(char *str, char *meta_c)
{
	int	i;

	i = 0;
	while (str[i] && !strchr(meta_c, str[i]))
		i++;
	return (i);
}

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

int	ft_cpy_commands(char **commands, char *line, int size)
{
	int		i;
	int		j;
	char	*meta_c;
	int		len;
	char	save;

	meta_c = "|&;()<> \t";
	i = 0;
	j = 0;
	while (i < size)
	{
		len = ft_strlen_meta(&line[j], meta_c);
		printf("len: %d\n", len);
		commands[i] = malloc((len + 1) * sizeof (char));
		if (!commands[i])
		{
			ft_free_commands(commands);
			return (0);
		}
		printf("j = %d\n", j);
		commands[i] = memmove(commands[i], &line[j], len);
		save = line[j + len];
		j += len + 1;
		if (line[j] == '<')
		{
			// "<<"だとわかるようにする
			j++;
		}
		else if (line[j] == '>')
		{
			// ">>"だとわかるようにする
			j++;
		}
		while (line[j] == save)
			j++;
		i++;
	}
	commands[i] = NULL;
	return (1);
}

char	**ft_lexer(char *line)
{
	int		size;
	char	**commands;
	int		i;
	char	*meta_c;
	int		len;

	size = ft_count_command(line);
	printf("size: %d\n", size);
	commands = malloc((size + 1) * sizeof(char *));
	if (!commands)
		return (NULL);
	ft_cpy_commands(commands, line, size);
	return (commands);
}

int	main(int argc, char **argv)
{
	char	**commands;
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
	return (0);
}
