/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:44:20 by ttakino           #+#    #+#             */
/*   Updated: 2024/10/16 17:15:18 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

// envコマンドは引数なしでは、環境変数のリストを表示
// 引数1つではそのリスト＋その引数を表示
// 引数2つでは、２つ目の引数をプロセスを作成して、execve関数に渡して実行（cdが実行できないことからもわかる）

// exportだとおそらく、リストに環境変数を追加する感じだと思う。
void	env(t_env *env)
{
	
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