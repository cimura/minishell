/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:54:04 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/10  by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"
#include "exec.h"

static int	set_pwd(t_env *env_lst, char *cwd, char *key)
{
	t_env	*pwd_node;
	char	*new_value;

	pwd_node = get_node_from_key(env_lst, key);
	if (pwd_node == NULL)
		return (0);
	new_value = ft_strdup(cwd);
	if (new_value == NULL)
		return (1);
	free(pwd_node->value);
	pwd_node->value = new_value;
	return (0);
}

static int	rapper_chdir(char *path)
{
	int	status;

	status = chdir(path);
	if (status != 0)
	{
		print_error_msg("cd", false, path, "No such file or directory");
	}
	return (status);
}

static int	cd_with_arg(t_env *env_lst, char *arg, char *old, char *path)
{
	int	status;

	if (arg == NULL)
	{
		status = chdir(path);
		if (status != 0)
			print_error_msg("cd", false, "", "HOME not set");
	}
	else if (ft_strncmp(arg, "-", 2) == 0
		&& !is_envnode_exist(env_lst, "OLDPWD"))
	{
		print_error_msg("cd", false, "", "OLDPWD not set");
		status = 1;
	}
	else if (ft_strncmp(arg, "-", 2) == 0)
	{
		status = rapper_chdir(old);
		if (status == 0)
			ft_putendl_fd(old, STDOUT_FILENO);
	}
	else
		status = rapper_chdir(path);
	return (status);
}

static int	change_dir(t_env *env_lst, char *arg, char *old, char **cwd)
{
	int		status;
	char	*path;

	if (arg == NULL)
		path = ft_strdup(get_value_from_key(env_lst, "HOME"));
	else if (ft_strcmp(arg, "-") == 0)
		path = ft_strdup(old);
	else
		path = normalize_path(arg, *cwd);
	if (path == NULL)
		return (1);
	status = cd_with_arg(env_lst, arg, old, path);
	free(*cwd);
	*cwd = path;
	return (status);
}

int	cd(char **args, t_env *env_lst, t_mobile *mobile)
{
	char	*old;

	if (args == NULL)
		return (1);
	if (args[0] != NULL && args[1] != NULL)
	{
		print_error_msg("cd", false, "", "too many arguments");
		return (1);
	}
	old = ft_strdup(get_value_from_key(env_lst, OLD));
	if (old == NULL)
		return (1);
	if (set_pwd(env_lst, mobile->cwd, OLD) != 0)
		return (free(old), 1);
	if (change_dir(env_lst, args[0], old, &mobile->cwd) != 0)
		return (free(old), 1);
	free(old);
	if (set_pwd(env_lst, mobile->cwd, NEW) != 0)
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
