/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_to_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:28:31 by ttakino           #+#    #+#             */
/*   Updated: 2024/11/28 18:02:16 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	env_lstsize(t_env *env_lst)
{
	int	size;

	size = 0;
	while (env_lst != NULL)
	{
		if (env_lst->key && env_lst->value)
			size++;
		env_lst = env_lst->next;
	}
	return (size);
}

static char	*generate_key_value_str(t_env node)
{
	char	*key_equal;
	char	*result;

	key_equal = ft_strjoin(node.key, "=");
	if (key_equal == NULL)
		return (NULL);
	result = ft_strjoin(key_equal, node.value);
	free(key_equal);
	key_equal = NULL;
	return (result);
}

char	**env_lst_to_array(t_env *env_lst)
{
	char	**env_array;
	int		i;

	env_array = malloc((env_lstsize(env_lst) + 1) * sizeof(char *));
	if (env_array == NULL)
		return (NULL);
	i = 0;
	while (env_lst != NULL)
	{
		if (env_lst->value == NULL)
		{
			env_lst = env_lst->next;
			continue ;
		}
		env_array[i] = generate_key_value_str(*env_lst);
		if (env_array[i] == NULL)
			return (free_ptr_array(env_array), NULL);
		i++;
		env_lst = env_lst->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

//int	main(int argc, char **argv, char **envp)
//{
//	t_env	*env_lst;
//	char	**env_array;

//	(void)argc;
//	(void)argv;
//	env_lst = create_env_lst(envp);
//	if (env_lst == NULL)
//		return (1);
//	env_array = env_lst_to_array(env_lst);
//	if (env_array == NULL)
//		return (env_lstclear(&env_lst), 1);
//	int	i = 0;
//	while (env_array[i] != NULL)
//	{
//		printf("%s\n", env_array[i]);
//		i++;
//	}
//	env_lstclear(&env_lst);
//	free_ptr_array(env_array);
//	return (0);
//}
