/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:47:18 by ttakino           #+#    #+#             */
/*   Updated: 2024/10/16 16:44:16 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	_ft_lstclear(t_env **lst, void (*del)(t_env *))
{
	t_env	*current;
	t_env	*next;

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

void	_ft_lstadd_back(t_env **lst, t_env *new)
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

void	ft_free_env_node(t_env *node)
{
	free(node->key);
	node->key = NULL;
	free(node->value);
	node->value = NULL;
}

int    set_key_value(t_env *new, char *line)
{
    int    len;
	int		klen;
	int		vlen;

    len = strlen(line);
	// PATH=/usr/bin -> "/usr/bin" (vlen)
	vlen = strlen(strchr(line, '=') + 1);
	// PATH=の"="を除く
	klen = len - vlen - 1;
    new->key = malloc(klen + 1);
    if (!new->key)
        return (0);
    // -1は=を飛ばす、+1は
    new->value = malloc(vlen + 1);
	if (!new->value)
		return (free(new->key), new->key = NULL, 0);
	
	new->key = memmove(new->key, line, klen);
	new->key[klen] = '\0';

	new->value = memmove(new->value, &line[klen + 1], vlen);
	new->value[vlen] = '\0';
	return (1);
}

t_env    *ft_env_list(char *envp[])
{
    int        i;
    t_env    *head;
    t_env    *new;

    head = NULL;

    i = 0;
    while (envp[i])
    {
        new = malloc(sizeof(t_env));
        if (!new)
            return (NULL);
        if (!set_key_value(new, envp[i]))
			return (_ft_lstclear(&head, ft_free_env_node), free(new), new = NULL, NULL);
		new->next = NULL;
		_ft_lstadd_back(&head, new);
        i++;
    }
	return (head);
}

int    main(int argc, char *argv[], char *envp[])
{
	int	i;
	t_env	*head;
	t_env	*env_lst;

	env_lst = ft_env_list(envp);
	if (!env_lst)
		return (1);
	head = env_lst;
	i = 0;
	while (env_lst != NULL)
	{
		printf("%s=%s\n", env_lst->key, env_lst->value);
		env_lst = env_lst->next;
	}
	_ft_lstclear(&head, ft_free_env_node);
}