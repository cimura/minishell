/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:54:04 by sshimura          #+#    #+#             */
/*   Updated: 2024/11/28 18:35:59 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
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
	if (args == NULL || args[0] == NULL)
		return (0);
	else if (args[1] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
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
//	env_lstclear(&env_lst);
//	return (status);
//}
