#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "expander.h"

typedef struct s_token
{
	char	**command_line;
	struct s_token	*next;
}	t_token;

typedef struct s_words
{
	char	*word;
	struct s_words	*next;
}	t_words;

char	*copy_word(char *line, int condition_expr)
{
	char	*cpy;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (line[i] != '\0' && condition_expr)
		len++;
	cpy = ft_strndup(line, len);
	if (cpy == NULL)
		return (NULL);
	return (cpy);
}

t_words	*count_words_until_pipe(char *line)
{
	int	num;
	int	i;
	char	in_quote;
	int	word_start;
	t_words	words;

	num = 0;
	in_quote = 0;
	word_start = 1;
	i = 0;
	while (line[i] != '\0')
	{
		//if (in_quote == 0 && line[i] == '|')
		//	break ;
		// meta
		if (in_quote == 0 && strchr("&;()<>", line[i]) != NULL)
		{
			words.word = copy_word()
			num++;
			printf("meta/%c\n", line[i]);
			word_start = 1;
			while (line[i + 1] != '\0' && strchr("|&;()<>", line[i + 1]) != NULL)
			{
				i++;
			}
		}
		// space or tab
		else if (in_quote == 0 && strchr(" \t", line[i]) != NULL)
		{
			word_start = 1;
		}
		// quote
		else if (in_quote == 0 && strchr("\'\"", line[i]) != NULL)
		{
			in_quote = line[i];
			if (word_start == 1)
			{
				num++;
				printf("quote on start/%c\n", line[i]);
				word_start = 0;
			}
		}
		else if (in_quote != 0 && in_quote == line[i])
		{
			in_quote = 0;
		}
		// normal
		else if (in_quote == 0 && word_start == 1)
		{
			num++;
			printf("normal/%c\n", line[i]);
			word_start = 0;
		}
		
		i++;
	}
	return (num);
}

void	set_command_line(char *line, char **command_line)
{

}

t_token	*lexer(char *line)
{
	int		words;
	t_token	*head;
	t_token	*new;

	head = NULL;
	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	words = count_words_until_pipe(line);
	new->command_line = malloc(words * sizeof(char *));
	if (new->command_line == NULL)
		return (free(new), new = NULL, NULL);
	set_command_line(line, new->command_line);
}

int	main(int argc, char **argv)
{
	int	words;
	int	i;

	if (argc == 1)
		return (0);
	i = 1;
	while (argv[i] != NULL)
	{
		words = count_words_until_pipe(argv[i]);
		printf("%s: %dwords\n", argv[i], words);
		i++;
	}
	return (0);
}