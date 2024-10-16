/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:40:57 by sshimura          #+#    #+#             */
/*   Updated: 2024/10/16 14:13:48 by ttakino          ###   ########.fr       */
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

void	_ft_lstclear(t_token **lst, void (*del)(char **))
{
	t_token	*current;
	t_token	*next;

	if (lst == NULL || del == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		del(current->command_line);
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	_ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	last = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
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

void	ft_print_commands(char **commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		printf("%s\n", commands[i++]);
	}
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
		else if (line[li] == '\t')
			line[li++] = ' ';
		else
			result[ri++] = line[li++];
	}
	result[ri] = '\0';
	return (result);
}

char	**ft_split_pipe(char *command_line)
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

t_token	*ft_lexer(char *command_line)
{
	t_token	*new;
	t_token	*head;
	char	**split_pipe;
	int		i;

	split_pipe = ft_split_pipe(command_line);
	if (!split_pipe)
		return (NULL);
	head = NULL;
	i = 0;
	while (split_pipe[i] != NULL)
	{
		new = malloc(sizeof(t_token));
		if (!new)
			return (ft_free_commands(split_pipe), NULL);
		new->command_line = ft_split(split_pipe[i], ' ');
		if (!new->command_line)
			return (ft_free_commands(split_pipe), free(new), new = NULL,
					_ft_lstclear(&head, ft_free_commands), NULL);
		new->next = NULL;
		_ft_lstadd_back(&head, new);
		i++;
	}
	ft_free_commands(split_pipe);
	return (head);
}

int	main(int argc, char **argv)
{
	t_token	*token;
	t_token	*head;
	char	**commands;
	int		i;

	if (argc != 2)
		return (1);

	printf("command: %s\n", argv[1]);
	token = ft_lexer(argv[1]);
	if (token == NULL)
		return (1);
	head = token;
	i = 0;
	while (token != NULL)
	{
		ft_print_commands(token->command_line);
		printf("|\n");
		token = token->next;
	}
	_ft_lstclear(&head, ft_free_commands);
	return (0);
}
