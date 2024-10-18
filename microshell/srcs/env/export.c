/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:00:50 by ttakino           #+#    #+#             */
/*   Updated: 2024/10/18 15:05:20 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	export(char *arg, t_env *env_lst)
{
	t_env	*new;
	int		klen;
	int		vlen;

	// 引数が key=value の形になっていなかったら正常終了にした（仮）
	if (!ft_strchr(arg, '='))
		return (1);

	// あとは新しいノード作ってenv_lstに追加してるだけ
	vlen = ft_strlen(ft_strchr(arg, '=') + 1);
	klen = ft_strlen(arg) - vlen - 1;
	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->key = malloc(klen + 1);
	if (!new->key)
		return (free(new), new = NULL, 0);
	new->value = malloc(vlen + 1);
	if (!new->value)
		return (free(new), new = NULL, free(new->key), new->key = NULL, 0);
	new->key = ft_memmove(new->key, arg, klen);
	new->key[klen] = '\0';
	new->value = ft_memmove(new->value, (ft_strchr(arg, '=') + 1), vlen);
	new->value[vlen] = '\0';
	new->next = NULL;
	ft_env_lstadd_back(&env_lst, new);
	return (1);
}

int    main(int argc, char *argv[], char *envp[])
{
	int	i;
	t_env	*head;
	t_env	*env_lst;

	env_lst = ft_env_list(envp);
	if (!env_lst)
		return (1);
	if (argc != 2)
		return (0);
	export(argv[1], env_lst);
	head = env_lst;
	i = 0;
	while (env_lst != NULL)
	{
		printf("%s=%s\n", env_lst->key, env_lst->value);
		env_lst = env_lst->next;
	}
	ft_env_lstclear(&head, ft_free_env_node);
}
