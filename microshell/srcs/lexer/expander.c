/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:08:10 by sshimura          #+#    #+#             */
/*   Updated: 2024/10/27 15:47:52 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static t_expand_lst	*create_quoted_node(char *line)
{
	t_expand_lst	*new;
	char			*meta;

	new = malloc(sizeof(t_expand_lst));
	if (new == NULL)
		return (NULL);
	if (*line == '\'')
		meta = "'\'";
	else if (*line == '\"')
		meta = "\"";
	else
		meta = "\'\"";
	if (*line == '\'')
		new->status = SINGLE;
	else if (*line == '\"')
		new->status = DOUBLE;
	else
		new->status = OUT;
	if (*line == '\'' || *line == '\"')
		line++;
	new->str = ft_strndup(line, count_until_char(line, meta));
	if (new->str == NULL)
		return (free(new), new = NULL, NULL);
	new->next = NULL;
	return (new);
}

static t_expand_lst	*create_quoted_lst(char *line)
{
	int				i;
	t_expand_lst	*new;
	t_expand_lst	*head;

	if (str_count(line, "\'") % 2 != 0
		|| str_count(line, "\"") % 2 != 0)
		return (NULL);
	head = NULL;
	i = 0;
	while (line[i])
	{
		new = create_quoted_node(&line[i]);
		if (new == NULL)
			return (expand_lstclear(&head), NULL);
		if (line[i] == '\'' || line[i] == '\"')
			i += ft_strlen(new->str) + 2;
		else
			i += ft_strlen(new->str);
		expand_lstadd_back(&head, new);
	}
	return (head);
}

static int	handle_doller_expand(t_env *env_lst, t_expand_lst *expand_lst)
{
	char	*old;

	while (expand_lst != NULL)
	{
		if (expand_lst->status != SINGLE)
		{
			old = expand_lst->str;
			expand_lst->str = expand_env_variable(env_lst, expand_lst->str);
			if (expand_lst->str == NULL)
				return (free(old), old = NULL, 1);
			free(old);
			old = NULL;
		}
		expand_lst = expand_lst->next;
	}
	return (0);
}

// hello -> wo -> world
// 最初の要素だけコピーしてあとはjoin, NULLチェックは必要
static char	*join_lst(t_expand_lst *expand_lst)
{
	char	*result;
	char	*tmp;

	result = ft_strdup(expand_lst->str);
	if (result == NULL)
		return (NULL);
	expand_lst = expand_lst->next;
	while (expand_lst != NULL)
	{
		tmp = ft_strjoin(result, expand_lst->str);
		if (tmp == NULL)
			return (free(result), result = NULL, NULL);
		free(result);
		result = tmp;
		expand_lst = expand_lst->next;
	}
	return (result);
}

// この関数を呼べば展開されて返ってくる
char	*expander(t_env *env_lst, char *line)
{
	t_expand_lst	*expand_lst;
	char			*result;

	expand_lst = create_quoted_lst(line);
	if (!expand_lst)
		return (NULL);
	if (handle_doller_expand(env_lst, expand_lst) == 1)
	{
		expand_lstclear(&expand_lst);
		return (NULL);
	}
	result = join_lst(expand_lst);
	expand_lstclear(&expand_lst);
	return (result);
}

//int	main(int argc, char **argv, char **envp)
//{
//	(void)argc;
//	(void)argv;
//	//char	*line = "hello \'wo\'$ world\"$PATH!!!\"";
//   char	*line = "\"value = \"\"$HOME!?$SHELL$\"\'($HOME)\'";
//   char	*com;
//	t_env	*env_lst = create_env_lst(envp);
//
//	char *result_line = expander(env_lst, line);
//   if (result_line == NULL)
//   {
//   	env_lstclear(&env_lst, free_env_node);
//   	return (0);
//   }
//   printf("\x1b[33m%s\x1b[0m\n", line);
//   com = ft_strjoin("echo ", line);
//   printf("echo\n");
//   system(com);
//	printf("./expand\n%s\n", result_line);
//	env_lstclear(&env_lst, free_env_node);
//	free(result_line);
//}
