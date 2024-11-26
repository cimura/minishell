/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:00:50 by ttakino           #+#    #+#             */
/*   Updated: 2024/11/26 16:38:18 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	parse_argument(char *arg, int *status)
{
	int	i;

	if (!(arg[0] >= 'A' && arg[0] <= 'Z') && arg[0] != '_'
		&& !(arg[0] >= 'a' && arg[0] <= 'z'))
	{
		*status = 1;
		return (1);
	}
	i = 0;
	while (arg[i] != '\0' && arg[i] != '=' && arg[i] != '+')
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
		{
			return (0);
		}
		if (!(arg[i] >= 'A' && arg[i] <= 'Z') && arg[i] != '_'
			&& !(arg[i] >= 'a' && arg[i] <= 'z')
			&& !(arg[i] >= '0' && arg[i] <= '9'))
		{
			*status = 1;
			return (1);
		}
		i++;
	}
	if (arg[0] == '\0' || ft_strchr(arg, '=') == NULL)
		return (1);
	return (0);
}

static int	register_new_env(char *arg, t_env *env_lst)
{
	t_env	*target;

	target = env_lst;
	while (target != NULL)
	{
		if (ft_strncmp(arg, target->key, ft_strlen(target->key)) == 0)
			break ;
		target = target->next;
	}
	if (target == NULL)
	{
		target = create_new_env_node(arg);
		if (target == NULL)
			return (1);
		env_lstadd_back(&env_lst, target);
	}
	else
	{
		target->value = generate_new_value(target->value, arg);
		if (target->value == NULL)
			return (1);
	}
	return (0);
}

void	no_args(t_env *env_lst)
{
	int		i;
	char	*now_min;
	char	*old_min;
	t_env	*head;

	head = env_lst;
	old_min = "\0";
	i = 0;
	while (i < count_env_lst(head))
	{
		env_lst = head;
		now_min = get_max_key(env_lst);
		while (env_lst != NULL)
		{
			if (ft_strncmp(env_lst->key, old_min, 4096) > 0
				&& ft_strncmp(env_lst->key, now_min, 4096) < 0)
				now_min = env_lst->key;
			env_lst = env_lst->next;
		}
		print_with_format(get_node_having_same_key(now_min, head));
		old_min = now_min;
		i++;
	}
}

int	with_args(char **args, t_env *env_lst)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (args[i] != NULL)
	{
		if (parse_argument(args[i], &status) == 1)
		{
			if (status == 1)
				ft_putendl_fd(" not a valid identifier", STDERR_FILENO);
			i++;
			continue ;
		}
		if (register_new_env(args[i], env_lst) == 1)
			return (1);
		i++;
	}
	return (status);
}

int	export(char **args, t_env *env_lst)
{
	int	status;

	status = 0;
	if (args[0] == NULL)
		no_args(env_lst);
	else
		status = with_args(args, env_lst);
	return (status);
}

// int    main(int argc, char *argv[], char *envp[])
// {
// 	int	i;
// 	t_env	*head;
// 	t_env	*env_lst;
// 	env_lst = create_env_lst(envp);
// 	if (env_lst == NULL)
// 		return (1);
// 	int status = export(&argv[1], env_lst);
// 	head = env_lst;
// 	i = 0;
// 	while (env_lst)
// 	{
// 		printf("%s=%s\n", env_lst->key, env_lst->value);
// 		env_lst = env_lst->next;
// 	}
// 	env_lstclear(&head);
// 	return (status);
// }
