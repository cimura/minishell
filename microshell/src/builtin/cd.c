/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:54:04 by sshimura          #+#    #+#             */
/*   Updated: 2024/11/13 20:04:59 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static t_env	*get_node_from_key(t_env *env_lst, char *key)
{
	while (env_lst != NULL)
	{
		if (ft_strncmp(key, env_lst->key, ft_strlen(env_lst->key)) == 0)
			return (env_lst);
		env_lst = env_lst->next;
	}
	return (NULL);
}

#define OLD "OLDPWD"
#define NEW "PWD"

static int	set_pwd(t_env *env_lst, char *flag)
{
	t_env	*pwd_node;
	char	*cwd;

	pwd_node = get_node_from_key(env_lst, flag);
	if (pwd_node == NULL)
		return (1);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd faild");
		return (1);
	}
	free(pwd_node->value);
	pwd_node->value = cwd;
	return (0);
}

int	cd(char **args, t_env *env_lst)
{
	if (args == NULL || args[1] != NULL)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	else if (args[0] == NULL)
		return (0);
	if (set_pwd(env_lst, OLD) != 0)
		return (1);
	if (chdir(args[0]) != 0)
	{
		perror(args[0]);
		return (1);
	}
	if (set_pwd(env_lst, NEW) != 0)
		return (1);
	return (0);
}

//int	main(int argc, char **argv, char **envp)
//{
//	t_env	*env_lst;
//	int		status;
//	char	*old_pwd;
//	char	*new_pwd;

//	(void)argc;
//	env_lst = create_env_lst(envp);
//	if (env_lst == NULL)
//		return (1);
//	old_pwd = get_node_from_key(env_lst, "OLDPWD")->value;
//	new_pwd = get_node_from_key(env_lst, "PWD")->value;
//	printf("OLD_PWD: %s, PWD: %s\n", old_pwd, new_pwd);
//	printf("Before: ");
//	pwd();
//	status = cd(&argv[1], env_lst);
//	printf("After: ");
//	pwd();
//	old_pwd = get_node_from_key(env_lst, "OLDPWD")->value;
//	new_pwd = get_node_from_key(env_lst, "PWD")->value;
//	printf("OLD_PWD: %s, PWD: %s\n", old_pwd, new_pwd);
//	env_lstclear(&env_lst, free_env_node);
//	return (status);
//}
