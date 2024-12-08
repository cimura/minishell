/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 16:27:45 by ttakino           #+#    #+#             */
/*   Updated: 2024/12/08 19:27:03 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "syntax.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	n;

	if (s1 == NULL || s2 == NULL)
		return (1);
	n = ft_strlen(s1);
	i = ft_strlen(s2);
	if (n < i)
		n = i;
	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

// static int	set_array_argument(char *expand, t_command_lst *per_pipe, int i)
// {
// 	if (expand && ft_strcmp(per_pipe->command_line[i], expand) != 0)
// 		per_pipe->is_expanded[i] = true;
// 	if (expand == NULL)
// 		return (1);
// 	free(per_pipe->command_line[i]);
// 	per_pipe->command_line[i] = expand;
// 	return (0);
// }

// static t_list	*create_token_lst(char *command_line)
// {
// 	int		i;
// 	t_list	*head;
// 	t_list	*new_node;

// 	head = NULL;
// 	i = 0;
// 	while (command_line[i])
// 	{
// 		new_node = ft_lstnew(command_line[i]);
// 		if (new_node == NULL)
// 			return (ft_lstclear(&head, free), NULL);
// 		ft_lstadd_back(&head, new_node);
// 		i++;
// 	}
// 	return (head);
// }

void	expand_lstadd_back(t_expand_lst **head, t_expand_lst *new)
{
	t_expand_lst	*last;

	last = *head;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
}

void	expand_lstclear(t_expand_lst **head)
{
	t_expand_lst	*current;
	t_expand_lst	*next;

	if (head == NULL)
		return ;
	current = *head;
	while (current != NULL)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
	*head = NULL;
}

t_expand_lst	*expand_lstnew(char	*str, int status)
{
	t_expand_lst	*new;

	new = malloc(sizeof(t_expand_lst));
	if (new == NULL)
		return (NULL);
	new->str = ft_strdup(str);
	if (new->str == NULL)
		return (free(new), NULL);
	new->status = status;
	new->next = NULL;
	return (new);
}

int	expand_lstsize(t_expand_lst *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

static int	count_words(char *str, char *delimiters)
{
	int		i;
	int		c;
	bool	is_next_count;

	is_next_count = true;
	c = 0;
	i = 0;
	while (str[i])
	{
		if (is_next_count && ft_strchr(delimiters, str[i]) == NULL)
		{
			c++;
			is_next_count = false;
		}
		else if (!is_next_count && ft_strchr(delimiters, str[i]))
			is_next_count = true;
		i++;
	}
	return (c);
}

static char	*pick_out_word(char *str, char *delimiters)
{
	char	*new;
	int		len;

	len = 0;
	while (ft_strchr(delimiters, str[len]) == NULL)
		len++;
	new = ft_strndup(str, len);
	if (new == NULL)
		return (NULL);
	return (new);
}

char	**ft_split_multi_delimiters(char *str, char *delimiters)
{
	char	**split;
	int		size;
	int		i;
	bool	is_word_head;

	size = count_words(str, delimiters);
	split = malloc((size + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	split[size] = NULL;
	is_word_head = true;
	i = 0;
	while (*str) 
	{
		if (is_word_head && ft_strchr(delimiters, *str) == NULL)
		{
			split[i] = pick_out_word(str, delimiters);
			if (split[i] == NULL)
				return (free_ptr_array(split), NULL);
			is_word_head = false;
			i++;
		}
		else if (!is_word_head && ft_strchr(delimiters, *str))
		{
			is_word_head = true;
		}
		str++;
	}
	return (split);
}

int	add_node_with_split_ifs(t_env *env_lst, t_expand_lst **head, char *expand)
{
	t_expand_lst	*current;
	char			*delimiters;
	char			**split;
	int				i;

	delimiters = get_value_from_key(env_lst, "IFS");
	if (!is_envnode_exist(env_lst, "IFS"))
		delimiters = " \t\n";
	split = ft_split_multi_delimiters(expand, delimiters);
	if (split == NULL)
		return (1);
	i = 0;
	while (split[i])
	{
		current = expand_lstnew(split[i], ENV);
		if (current == NULL)
			return (free_ptr_array(split), 1);
		expand_lstadd_back(head, current);
		i++;
	}
	free_ptr_array(split);
	return (0);
}

// This function frees the expand_list
int	apply_new_command_lst(t_command_lst *per_pipe, t_expand_lst **head)
{
	char			**new_cmdline;
	int				*new_is_expanded;
	int				size;
	int				i;
	t_expand_lst	*current;

	size = expand_lstsize(*head);
	new_is_expanded = malloc((size) * sizeof(int));
	if (new_is_expanded == NULL)
		return (expand_lstclear(head), 1);
	new_cmdline = malloc((size + 1) * sizeof(char *));
	if (new_cmdline == NULL)
		return (expand_lstclear(head), free(new_is_expanded), 1);
	current = *head;
	i = 0;
	while (i < size)
	{
		new_cmdline[i] = ft_strdup(current->str);
		if (new_cmdline[i] == NULL)
			return (expand_lstclear(head), free_ptr_array(new_cmdline), 1);
		new_is_expanded[i] = current->status;
		current = current->next;
		i++;
	}
	new_cmdline[i] = NULL;
	free_ptr_array(per_pipe->command_line);
	per_pipe->command_line = new_cmdline;
	free(per_pipe->is_expanded);
	per_pipe->is_expanded = new_is_expanded;
	return (expand_lstclear(head), 0);
}

int	handle_quotes_env_variable(t_env *env_lst,
	t_command_lst *per_pipe, int end_status)
{
	t_expand_lst	*head;
	t_expand_lst	*current;
	int				i;
	int				status;
	char			*expand;
	char			*tmp;

	head = NULL;
	i = 0;
	while (per_pipe->command_line[i] != NULL)
	{
		status = 0;
		if (per_pipe->command_line[i + 1] != NULL
			&& ft_strncmp(per_pipe->command_line[i], "<<", 3) == 0)
			expand = remove_quotes(per_pipe->command_line[++i]);
		else
		{
			tmp = expand_env_variable(env_lst,
					per_pipe->command_line[i], end_status);
			if (tmp && ft_strcmp(per_pipe->command_line[i], tmp) != 0)
				status = ENV;
			expand = remove_quotes(tmp);
			if (expand && ft_strcmp(tmp, expand) != 0)
				status += QUOTE;
			free(tmp);
		}
		if (expand == NULL)
			return (expand_lstclear(&head), 1);
		if (status == ENV && is_ifs_in_str(env_lst, expand))
		{
			if (add_node_with_split_ifs(env_lst, &head, expand) != 0)
				return (expand_lstclear(&head), free(expand), 1);
		}
		else
		{
			current = expand_lstnew(expand, status);
			if (current == NULL)
				return (expand_lstclear(&head), free(expand), 1);
			expand_lstadd_back(&head, current);
		}
		free(expand);
		i++;
	}
	return (apply_new_command_lst(per_pipe, &head));
}

void	d_print_per_pipe(t_command_lst *lst)
{
	int	i;

	while (lst != NULL)
	{
		i = 0;
		while (lst->command_line[i] != NULL)
		{
			printf("%s: %d\n", lst->command_line[i], lst->is_expanded[i]);
			i++;
		}
		if (lst->next != NULL)
			printf("-------------pipe-------------\n");
		lst = lst->next;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env			*env_lst;
	t_command_lst	*per_pipe;
	int				i;

	if (argc == 1)
		return (0);
	env_lst = create_env_lst(envp);
	if (env_lst == NULL)
	{
		ft_putendl_fd("cannot create env_lst", 2);
		return (1);
	}
	i = 1;
	while (argv[i] != NULL)
	{
		per_pipe = parser(argv[i]);
		if (per_pipe == NULL)
		{
			env_lstclear(&env_lst);
			ft_putendl_fd("cannot create token list", 2);
			return (1);
		}
		printf("before\n");
		d_print_per_pipe(per_pipe);
		printf("\n");
		if (handle_quotes_env_variable(env_lst, per_pipe, 0) != 0)
		{
			env_lstclear(&env_lst);
			command_lstclear(&per_pipe);
			ft_putendl_fd("expander failed", 2);
			return (1);
		}
		printf("after\n");
		d_print_per_pipe(per_pipe);
		command_lstclear(&per_pipe);
		i++;
	}
	env_lstclear(&env_lst);
	return (0);
}
