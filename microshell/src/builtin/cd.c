/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:54:04 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/03 17:04:22 by cimy             ###   ########.fr       */
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
		return (0);
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

static int	rapper_chdir(char *arg)
{
	int	status;

	status = chdir(arg);
	if (status != 0)
		perror(arg);
	return (status);
}

static int	change_dir(t_env *env_lst, char *arg, char *oldpwd)
{
	int	local;

	if (arg == NULL)
	{
		local = chdir(get_value_from_key(env_lst, "HOME"));
		if (local != 0)
			ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
	}
	else
	{
		if (ft_strncmp(arg, "-", 2) == 0)
		{
			local = chdir(oldpwd);
			if (local != 0)
				ft_putendl_fd("cd: OLDPWD not set", STDERR_FILENO);
		}
		else
			local = rapper_chdir(arg);
	}
	return (local);
}

int	cd(char **args, t_env *env_lst)
{
	char	*old;

	if (args == NULL)
		return (1);
	if (args[0] != NULL && args[1] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	old = get_value_from_key(env_lst, OLD);
	if (set_pwd(env_lst, OLD) != 0)
		return (1);
	if (change_dir(env_lst, args[0], old) != 0)
		return (1);
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
