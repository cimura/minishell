/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:47:18 by ttakino           #+#    #+#             */
/*   Updated: 2024/10/23 19:32:59 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_lst.h"

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
	int	len;
	int	klen;
	int	vlen;

	len = ft_strlen(line);
	vlen = ft_strlen(ft_strchr(line, '=') + 1);
	klen = len - vlen - 1;
	new->key = malloc(klen + 1);
	if (!new->key)
		return (0);
	new->value = malloc(vlen + 1);
	if (!new->value)
		return (free(new->key), new->key = NULL, 0);
	new->key = ft_memmove(new->key, line, klen);
	new->key[klen] = '\0';
	new->value = ft_memmove(new->value, &line[klen + 1], vlen);
	new->value[vlen] = '\0';
	return (1);
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
		if (!set_key_value(new, envp[i]))
			return (free(new), new = NULL,
				env_lstclear(&head), NULL);
		new->next = NULL;
		env_lstadd_back(&head, new);
		i++;
	}
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
