/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:40:57 by sshimura          #+#    #+#             */
/*   Updated: 2024/10/28 16:42:19 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	count_meta_char(char *line, char *meta_char)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (ft_strchr(meta_char, line[i]))
		{
			if (line[i + 1] == line[i])
				i++;
			count++;
		}
		i++;
	}
	return (count);
}

static void	write_result(char *result, char *line, char *meta_char)
{
	int	ri;
	int	li;

	ri = 0;
	li = 0;
	while (line[li] != '\0')
	{
		if (ft_strchr(meta_char, line[li]))
		{
			result[ri++] = ' ';
			if (line[li + 1] == line[li])
				result[ri++] = line[li++];
			result[ri++] = line[li++];
			result[ri++] = ' ';
		}
		else if (line[li] == '\t')
			line[li++] = ' ';
		else
			result[ri++] = line[li++];
	}
	result[ri] = '\0';
}

// newline:  ">" ---> " > "　number of metacharacter * 3
static char	*cover_metachar_by_space(char *line, char *meta_char)
{
	char	*result;
	int		n_meta;

	n_meta = count_meta_char(line, meta_char);
	result = malloc(ft_strlen(line) + n_meta * 3 + 1);
	if (result == NULL)
		return (NULL);
	write_result(result, line, meta_char);
	return (result);
}

static char	**ft_split_pipe(char *command_line)
{
	char	*meta_char;
	char	**split_pipe;
	char	*tmp;
	int		i;

	meta_char = "|&;()<>";
	split_pipe = ft_split(command_line, '|');
	if (split_pipe == NULL)
		return (NULL);
	i = 0;
	while (split_pipe[i] != NULL)
	{
		tmp = cover_metachar_by_space(split_pipe[i], meta_char);
		if (tmp == NULL)
			return (free_commands(split_pipe), NULL);
		free(split_pipe[i]);
		split_pipe[i] = tmp;
		i++;
	}
	split_pipe[i] = NULL;
	return (split_pipe);
}

t_token	*lexer(char *command_line)
{
	t_token	*new;
	t_token	*head;
	char	**split_pipe;
	int		i;

	split_pipe = ft_split_pipe(command_line);
	if (split_pipe == NULL)
		return (NULL);
	head = NULL;
	i = 0;
	while (split_pipe[i] != NULL)
	{
		new = malloc(sizeof(t_token));
		if (new == NULL)
			return (free_commands(split_pipe), NULL);
		new->command_line = ft_split(split_pipe[i], ' ');
		if (new->command_line == NULL)
			return (free_commands(split_pipe), free(new), new = NULL,
				token_lst_clear(&head, free_commands), NULL);
		new->next = NULL;
		token_lstadd_back(&head, new);
		i++;
	}
	free_commands(split_pipe);
	return (head);
}

//int	main(int argc, char **argv)
//{
//	t_token	*token;
//	t_token	*head;
//	int		i;

//	if (argc != 2)
//		return (1);
//	printf("command: %s\n", argv[1]);
//	token = lexer(argv[1]);
//	if (token == NULL)
//		return (1);
//	head = token;
//	i = 0;
//	while (token != NULL)
//	{
//		print_commands(token->command_line);
//		printf("|\n");
//		token = token->next;
//	}
//	token_lst_clear(&head, free_commands);
//	return (0);
//}
