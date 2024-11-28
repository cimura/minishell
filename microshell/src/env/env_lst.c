/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:47:18 by ttakino           #+#    #+#             */
/*   Updated: 2024/11/28 22:49:34 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_lst.h"
#include "utils.h"

void	env_lstclear(t_env **lst)
{
	t_env	*current;
	t_env	*next;

	if (lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		current->key = NULL;
		free(current->value);
		current->value = NULL;
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

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

// PATH=/usr/bin -> "PATH"		(key)	
// PATH=/usr/bin -> "/usr/bin"	(value)
static int	set_key_value(t_env *new, char *line)
{
	char	*value_ptr;
	int		klen;
	int		vlen;

	value_ptr = ft_strchr(line, '=') + 1;
	klen = count_key_size(line);
	vlen = ft_strlen(value_ptr);
	new->key = ft_strndup(line, klen);
	if (new->key == NULL)
		return (1);
	if (ft_strncmp("SHLVL", new->key, ft_strlen("SHLVL")) == 0)
	{
		if (ft_atoi(value_ptr) >= 999)
			new->value = ft_strdup("0");
		else
			new->value = ft_itoa(ft_atoi(value_ptr) + 1);
	}
	else
		new->value = ft_strndup(value_ptr, vlen);
	if (new->value == NULL)
		return (free(new->key), 1);
	return (0);
}

t_env	*get_node_from_key(t_env *env_lst, char *key)
{
	while (env_lst != NULL)
	{
		if (ft_strncmp(key, env_lst->key, ft_strlen(env_lst->key) + 1) == 0)
			return (env_lst);
		env_lst = env_lst->next;
	}
	return (NULL);
}

t_env	*create_env_lst(char *envp[])
{
	int		i;
	t_env	*head;
	t_env	*new;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (NULL);
		if (set_key_value(new, envp[i]) == 1)
			return (free(new), new = NULL,
				env_lstclear(&head), NULL);
		new->next = NULL;
		env_lstadd_back(&head, new);
		i++;
	}
	if (head == NULL)
		exit(1);
	return (head);
}

// int    main(int argc, char *argv[], char *envp[])
// {
// 	int	i;
// 	t_env	*head;
// 	t_env	*env_lst;

// 	env_lst = create_env_lst(envp);
// 	if (!env_lst)
// 		return (1);
// 	head = env_lst;
// 	i = 0;
// 	while (env_lst != NULL)
// 	{
// 		printf("%s=%s\n", env_lst->key, env_lst->value);
// 		env_lst = env_lst->next;
// 	}
// 	env_lstclear(&head);
// }
