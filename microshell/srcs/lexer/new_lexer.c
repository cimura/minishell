#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//libftのボーナスが使えなかったので違うとこから取ってきた
#include "../../../../Libft/include/libft.h"

typedef struct s_token
{
	char	**command_line;
	struct s_token	*next;
}	t_token;

int	add_node_from_storage(t_list **head, char *storage)
{
	t_list	*new;
	char	*content;

	if (ft_strlen(storage) == 0)
		return (1);

	content = ft_strdup(storage);
	if (content == NULL)
		return (0);

	new = ft_lstnew(content);
	if (new == NULL)
		return (ft_lstclear(head, free), free(content), content = NULL, 0);
	printf("new->content = %s\n", (char *)new->content);

	ft_lstadd_back(head, new);
	ft_bzero(storage, ft_strlen(storage));
	return (1);
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

int	case_isspace(char *storage, char *line, int i)
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
	while (line[i] != '\0' && ft_strchr("|&;()<> \t", line[i]) == NULL)
	{
		printf("normal/%c\n", line[i]);
		storage[si] = line[i];
		if (ft_strchr("\"\'", line[i]))
		{
			in_quote = line[i];
			i++;
			si++;
			while (line[i] != '\0' && in_quote != line[i])
			{
				printf("quote/%c\n", line[i]);
				storage[si++] = line[i++];
			}
			storage[si] = line[i];
		}
		i++;
		si++;
	}
	storage[si] = '\0';
	return (i);
}

t_list	*count_words_until_pipe(char *line)
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
		if (!add_node_from_storage(&head, storage))
			return (free(storage), storage = NULL, NULL);

		// meta
		if (ft_strchr("|&;()<>", line[i]) != NULL)
			i = case_meta(storage, line, i);
		// isspace
		else if (ft_strchr(" \t", line[i]) != NULL)
			i = case_isspace(storage, line, i);
		// normal
		else
			i = case_normal(storage, line, i);
	}
	if (!add_node_from_storage(&head, storage))
		return (free(storage), storage = NULL, NULL);
	free(storage);
	storage = NULL;
	return (head);
}

//void	set_command_line(char *line, char **command_line)
//{

//}

//t_token	*lexer(char *line)
//{
//	int		words;
//	t_token	*head;
//	t_token	*new;

//	head = NULL;
//	new = malloc(sizeof(t_token));
//	if (new == NULL)
//		return (NULL);
//	words = count_words_until_pipe(line);
//	new->command_line = malloc(words * sizeof(char *));
//	if (new->command_line == NULL)
//		return (free(new), new = NULL, NULL);
//	set_command_line(line, new->command_line);
//}

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
		words = count_words_until_pipe(argv[i]);
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
