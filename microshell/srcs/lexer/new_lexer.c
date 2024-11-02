#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libft/include/libft.h"
#include "lexer.h"

typedef struct s_token
{
	char	**command_line;
	struct s_token	*next;
}	t_token;

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
	printf("new->content = %s\n", (char *)new->content);

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
		printf("meta/%c\n", line[i]);
		storage[si] = line[i];
		i++;
		si++;
	}
	storage[si] = '\0';
	return (i);
}

int	case_whitespace(char *storage, char *line, int i)
{
	while (line[i] != '\0' && ft_strchr(" \t", line[i]) != NULL)
	{
		printf("space tab/%c\n", line[i]);
		i++;
	}
	return (i);
}

int	case_normal(char *storage, char *line, int i)
{
	int		si;
	char	in_quote;

	in_quote = '\0';
	si = 0;
	while (line[i] != '\0' && (!in_quote && ft_strchr("|&;()<> \t\v\r\f\n", line[i]) == NULL))
	{
		if (!in_quote && ft_strchr("\"\'", line[i]))
		{
			in_quote = line[i];
		}
		else if (in_quote == line[i])
			in_quote = 0;

		printf("normal/%c\n", line[i]);
		storage[si] = line[i];
		i++;
		si++;
	}
	storage[si] = '\0';
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
			i = case_whitespace(storage, line, i);
		// normal
		else
			i = case_normal(storage, line, i);

		head = add_node_from_storage(head, storage);
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
}

t_token	*create_pipe_lst(t_list *normal)
{
	t_token	*head;
	t_token	*new;
	int		size;
	int		i;

	head = NULL;
	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	size = count_token_until_pipe(normal);
	new->command_line = malloc(size * sizeof(char *));
	if (new->command_line == NULL)
		return (free(new), new = NULL, NULL);
	i = 0;
	while (normal != NULL)
	{
		if (ft_strncmp(normal->content, "|", 1) != 0)
		{
			new->command_line[i] = NULL;
			new->next = NULL;
			token_lstadd_back(&head, new);
			normal = normal->next;
			new = malloc(sizeof(t_token));
			if (new == NULL)
				return (token_lst_clear(&head, free_commands), NULL);
			size = count_token_until_pipe(normal);
			new->command_line = malloc(size * sizeof(char *));
			if (new->command_line == NULL)
				return (token_lst_clear(&head, free_commands),
					 free(new), new = NULL, NULL);
			i = 0;
			continue ;
		}
		new->command_line[i] = ft_strdup(normal->content);
		if (new->command_line[i] == NULL)
			return (token_lst_clear(&head, free_commands), 
				free_commands(new->command_line), free(new), new = NULL, NULL);
		i++;
		normal = normal->next;
	}
}

t_token	*lexer(char	*line)
{
	t_list	*normal;
	t_token	*per_pipe;

	normal = create_token_lst(line);
	if (normal == NULL)
		return (NULL);
}

int	main(int argc, char **argv)
{
	t_list	*head;
	t_list	*words;
	int	i;

	if (argc == 1)
		return (0);
	i = 1;
	while (argv[i] != NULL)
	{
		printf("\t%s\n", argv[i]);
		words = create_token_lst(argv[i]);
		if (words == NULL)
			return (printf("Error\n"), 1);
		head = words;
		while (words != NULL)
		{
			printf("--%s\n", (char *)words->content);
			words = words->next;
		}
		ft_lstclear(&head, free);
		i++;
	}
	return (0);
}
