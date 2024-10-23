/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:08:10 by sshimura          #+#    #+#             */
/*   Updated: 2024/10/23 10:03:58 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

enum	e_status
{
	IN_SINGLE,
	IN_DOUBLE,
	OUT
};

typedef struct	s_expand_lst
{
	char				*str;
	struct s_expand_lst	*next;
	int					status;
}	t_expand_lst;

static int	ft_str_count(char *line, char *meta_char)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (ft_strchr(meta_char, line[i]))
		{
			count++;
		}
		i++;
	}
	return (count);
}

void	ft_expand_lstclear(t_expand_lst **lst, void (*del)(t_expand_lst *))
{
	t_expand_lst	*current;
	t_expand_lst	*next;

	if (lst == NULL || del == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		del(current);
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	ft_expand_lstadd_back(t_expand_lst **lst, t_expand_lst *new)
{
	t_expand_lst	*last;

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

void	ft_free_expand_node(t_expand_lst *node)
{
	free(node->str);
	node->str = NULL;
}

static char	*ft_strndup(const char *str, size_t n)
{
	char	*result;
	size_t	str_len;
	size_t	i;

	i = 0;
	str_len = ft_strlen((char *)str);
	if (n < str_len)
		result = malloc(sizeof(char) * (n + 1));
	else
		result = malloc(sizeof(char) * (str_len + 1));
	if (result == NULL)
		return (NULL);
	while (str[i] != '\0' && n > i)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}


int	ft_count_until_char(char *line, char *needle)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr(needle, line[i]) != NULL)
			return (i);
		i++;
	}
	return (i);
}

t_expand_lst	*create_expand_lst(char *line)
{
	int	i;
	t_expand_lst	*new;
	t_expand_lst	*head;

	if (ft_str_count(line, "\'") % 2 != 0
		|| ft_str_count(line, "\"") % 2 != 0)
		return (NULL);
	head = NULL;
	i = 0;
	while (line[i])
	{
		new = malloc(sizeof(t_expand_lst));
		if (!new)
			return (NULL);
		if (line[i] == '\'')
		{
			i++;
			new->status = IN_SINGLE;
			new->str = ft_strndup(&line[i], ft_count_until_char(&line[i], "\'"));
			i += ft_count_until_char(&line[i], "\'") + 1;
		}
		else if (line[i] == '\"')
		{
			i++;
			new->status = IN_DOUBLE;
			new->str = ft_strndup(&line[i], ft_count_until_char(&line[i], "\""));
			i += ft_count_until_char(&line[i], "\"") + 1;
		}
		else
		{
			new->status = OUT;
			new->str = ft_strndup(&line[i], ft_count_until_char(&line[i], "\'\""));
			i += ft_count_until_char(&line[i], "\'\"");
		}
		new->next = NULL;
		ft_expand_lstadd_back(&head, new);
	}
	return (head);
}

// TODO
// 文字列でOUT, IN_DOUBLEの状態のものを展開する
// ft_until_charとかを使ってjoinする
// *lst_line = "hello$SHELL world"
char	*expand(char *lst_line)
{
	int	i;
	char  *to_expand;
	char  *tmp;
	int len = 0;
	char  *env_value = NULL;
	char  *new = malloc(1);

	new[0] = '\0';
	i = 0;
	while (lst_line[i])
	{
		if (lst_line[i] == '$')
		{
			i++;
			// ホワイトスペースとかまで数える
			to_expand = ft_strndup(&lst_line[i], ft_count_until_char(&lst_line[i], " \t\n*"));
			
			// 今はgetenvを使ってるけど，env_listを確認してvalueを取り出すように変える
			env_value = getenv(to_expand);
			if (!env_value)
				env_value = "";
			free(to_expand);
			tmp = ft_strjoin(new, env_value);
			free(new);
			new = tmp;
			i += ft_count_until_char(&lst_line[i], " \t\n*");
		}
		else
		{
			// new[1]であるから，joinしないと文字列を格納できない．
			// これは最初でmallocのbytesを決め打ちしないためにこうしてる
			len = strlen(new);
			tmp = ft_strjoin(new, &lst_line[i]);
			free(new);
			new = tmp;
			new[len + 1] = '\0';
			i++;
		}
	}
	new[len + 1] = '\0';
	return (new);
}

void	handle_doller(t_expand_lst *expand_lst)
{
	char  *old;
	while (expand_lst != NULL)
	{
		// must expand
		if (expand_lst->status != IN_SINGLE)
		{
			old = expand_lst->str;
			expand_lst->str = expand(expand_lst->str);
			free(old);
		}
		expand_lst = expand_lst->next;
	}
}

int	main()
{
	t_expand_lst	*result;
	t_expand_lst	*head;
	char	*line = "hello \'wo\'$hoge world";

	result = create_expand_lst(line);
	if (!result)
		return (1);
	handle_doller(result);
	// join_lst(result);
	head = result;
	while (result != NULL)
	{
		printf("str: %s\n", result->str);
		result = result->next;
	}
	ft_expand_lstclear(&head, ft_free_expand_node);
}
