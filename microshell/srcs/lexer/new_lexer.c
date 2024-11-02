#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libft/include/libft.h"
#include "lexer.h"

// typedef struct s_token
// {
// 	char	**command_line;
// 	struct s_token	*next;
// }	t_token;

t_list	*add_node_from_storage(t_list *head, char *storage)
{
	t_list	*new;
	char	*content;

	if (ft_strlen(storage) == 0)
		return (head);

	content = ft_strdup(storage);
	if (content == NULL)
		return (ft_lstclear(&head, free), NULL);

	new = ft_lstnew(content);
	if (new == NULL)
		return (ft_lstclear(&head, free), free(content), content = NULL, NULL);
	// printf("new->content = %s\n", (char *)new->content);

	ft_lstadd_back(&head, new);
	ft_bzero(storage, ft_strlen(storage));
	return (head);
}

int	case_meta(char *storage, char *line, int i)
{
	int	si;

	si = 0;
	while (line[i] != '\0' && ft_strchr("|&;()<>", line[i]) != NULL)
	{
		// printf("meta/%c\n", line[i]);
		storage[si] = line[i];
		i++;
		si++;
	}
	storage[si] = '\0';
	return (i);
}

int	case_whitespace(char *line, int i)
{
	while (line[i] != '\0' && ft_strchr(" \t", line[i]) != NULL)
	{
		// printf("space tab/%c\n", line[i]);
		i++;
	}
	return (i);
}

int	case_normal(char *storage, char *line, int i)
{
	int		si;
	char	in_quote;

	in_quote = 0;
	si = 0;
	while (line[i] != '\0')
	{
		if (!in_quote && ft_strchr("\"\'", line[i]))
		{
			in_quote = line[i];
		}
		else if (in_quote == line[i])
			in_quote = 0;
		else if (!in_quote && ft_strchr("|&;()<> \t\v\r\f\n", line[i]) != NULL)
			break ;
		storage[si] = line[i];
		i++;
		si++;
	}
	storage[si] = '\0';
	printf("storage: %s\n", storage);
	return (i);
}

t_list	*create_token_lst(char *line)
{
	int		i;
	char	*storage;
	t_list	*head;

	storage = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	if (storage == NULL)
		return (NULL);
	head = NULL;
	i = 0;
	while (line[i] != '\0')
	{
		// meta
		if (ft_strchr("|&;()<>", line[i]) != NULL)
			i = case_meta(storage, line, i);
		// whitespace
		else if (ft_strchr(" \t\v\r\f\n", line[i]) != NULL)
			i = case_whitespace(line, i);
		// normal
		else
			i = case_normal(storage, line, i);

		head = add_node_from_storage(head, storage);
		// printf("after head\n");
		if (head == NULL)
			return (free(storage), storage = NULL, NULL);
	}
	free(storage);
	storage = NULL;
	return (head);
}

int	count_token_until_pipe(t_list *lst)
{
	int	size;

	size = 0;
	while (lst != NULL && ft_strncmp(lst->content, "|", 1) != 0)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

char	**create_until_pipe_array(t_list *normal, int size)
{
	int		i;
	char	**command_line;

	command_line = malloc((size + 1) * sizeof(char *));
	if (command_line == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		command_line[i] = ft_strdup(normal->content);
		normal = normal->next;
		i++;
	}
	command_line[i] = NULL;
	return (command_line);
}

t_token	*create_pipe_lst(t_list *normal)
{
	int		size;
	t_token	*new;
	t_token	*head;

	head = NULL;
	while (normal != NULL)
	{
		if (ft_strncmp(normal->content, "|", 1) == 0)
			normal = normal->next;
		new = malloc(sizeof(t_token));
		if (new == NULL)
			return (NULL);
		size = count_token_until_pipe(normal);
		new->command_line = create_until_pipe_array(normal, size);
		new->next = NULL;
		token_lstadd_back(&head, new);
		while (size > 0)
		{
			normal = normal->next;
			size--;
		}
	}
	return (head);
}

t_token	*lexer(char	*line)
{
	t_list	*normal;
	t_token	*per_pipe;

	normal = create_token_lst(line);
	// printf("token lst good\n");
	per_pipe = create_pipe_lst(normal);
	// printf("pipe lst good\n");
	if (normal == NULL)
		return (NULL);
	return (per_pipe);
}

int	main(int argc, char **argv)
{
	t_token	*head;
	t_token	*words;
	int	i;
	int	j;

	if (argc == 1)
		return (0);
	i = 1;
	while (argv[i] != NULL)
	{
		// printf("%s\n", argv[i]);
		words = lexer(argv[i]);
		if (words == NULL)
			return (printf("Error\n"), 1);
		head = words;
		while (words != NULL)
		{
			j = 0;
			while (words->command_line[j] != NULL)
				printf("--\t%s\n", words->command_line[j++]);
			printf("\n");
			words = words->next;
		}
		token_lst_clear(&head, free_commands);
		i++;
	}
	return (0);
}
