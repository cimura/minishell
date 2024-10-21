/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:00:50 by ttakino           #+#    #+#             */
/*   Updated: 2024/10/21 12:43:06 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// 1 -> 見つからない 0 -> 見つかる
int    ft_strstr(char *haystack, char *needle)
{
    int    i;

    i = 0;
    if (needle[i] == '\0' || !haystack || *haystack == '\0')
        return (1);
    while (needle[i] != '\0')
    {
        if (strchr(haystack, needle[i]) != NULL)
            return (0);
        i++;
    }
    return (1);
}

// key部分にspecial_charの1文字が含まれるかどうかを検索する
bool	is_special_char_in_key(char *arg)
{
	char	*special_char;
	int		i;

	// TODO
	special_char = "|&;()<> \t\n*";
	i = 0;
	while (arg[i] != '\0' && arg[i] != '=')
	{
		if (ft_strchr(special_char, arg[i]) != NULL)
			return (true);
		i++;
	}
	return (false);
}

// 与えられたarg(key)があった場合に、そのノードを返す関数
t_env	*get_node_having_same_key(char *arg, t_env *env_lst)
{
	while (env_lst != NULL)
	{
		if (ft_strncmp(arg, env_lst->key, ft_strlen(env_lst->key)) == 0)
			return (env_lst);
		env_lst = env_lst->next;
	}
	return (NULL);
}

t_env	*set_key_value_registered(t_env *new, char *arg)
{
	int	klen;
	int	vlen;

	vlen = ft_strlen(ft_strchr(arg, '=') + 1);
	klen = ft_strlen(arg) - vlen - 1;
	new->key = malloc(klen + 1);
	if (!new->key)
		return (free(new), new = NULL, NULL);
	new->value = malloc(vlen + 1);
	if (!new->value)
		return (free(new), new = NULL, free(new->key), new->key = NULL, NULL);
	new->key = ft_memmove(new->key, arg, klen);
	new->key[klen] = '\0';
	new->value = ft_memmove(new->value, (ft_strchr(arg, '=') + 1), vlen);
	new->value[vlen] = '\0';
	return (new);
}

// 10.20 (Sun) bashで、export FOOなどの終了ステータスを見た場合、全部0だった
// returnを全部0にしている
int	export(char *arg, t_env *env_lst)
{
	t_env	*new;

	if (!arg || *arg == '\0')
		return (0);
	// 引数が key=value の形になっていなかっらはじく
	if (!ft_strchr(arg, '='))
		return (0);

	if (is_special_char_in_key(arg) == true)
		return (0);
	new = get_node_having_same_key(arg, env_lst);
	if (new == NULL)
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (0);
		new = set_key_value_registered(new, arg);
		if (new == NULL)
			return (free(new), new = NULL, 0);
		new->next = NULL;
		ft_env_lstadd_back(&env_lst, new);
	}
	else
	{
		printf("\x1b[36mThere is a node having a same key.\x1b[0m\n%s\n", new->key);
		new = set_key_value_registered(new, arg);
		if (new == NULL)
			return (0);
	}
	return (0);
}

// int    main(int argc, char *argv[], char *envp[])
// {
// 	int	i;
// 	t_env	*head;
// 	t_env	*env_lst;

// 	env_lst = ft_env_lst(envp);
// 	if (!env_lst)
// 		return (1);
// 	if (argc != 2)
// 		return (0);
// 	int status = export(argv[1], env_lst);
// 	head = env_lst;
// 	i = 0;
// 	while (env_lst != NULL)
// 	{
// 		printf("%s=%s\n", env_lst->key, env_lst->value);
// 		env_lst = env_lst->next;
// 	}
// 	ft_env_lstclear(&head, ft_free_env_node);
// 	return (status);
// }
