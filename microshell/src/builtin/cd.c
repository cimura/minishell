/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:54:04 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/08 15:05:25 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"
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
	if (cwd)
	{
		free(pwd_node->value);
		pwd_node->value = cwd;
	}
	return (0);
}

static int	rapper_chdir(char *arg)
{
	int	status;

	status = chdir(arg);
	if (status != 0)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(arg);
	}
	return (status);
}

static int	change_dir(t_env *env_lst, char *arg, char *oldpwd)
{
	int	status;

	if (arg == NULL)
	{
		status = chdir(get_value_from_key(env_lst, "HOME"));
		if (status != 0)
			print_error_msg("cd", false, "", "HOME not set");
	}
	else
	{
		if (ft_strncmp(arg, "-", 2) == 0)
		{
			status = chdir(oldpwd);
			if (status != 0)
				print_error_msg("cd", false, "", "OLDPWD not set");
			else
				ft_putendl_fd(oldpwd, STDOUT_FILENO);
		}
		else
			status = rapper_chdir(arg);
	}
	return (status);
}

int	cd(char **args, t_env *env_lst)
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
	if (set_pwd(env_lst, OLD) != 0)
		return (free(old), 1);
	if (change_dir(env_lst, args[0], old) != 0)
		return (free(old), 1);
	free(old);
	if (set_pwd(env_lst, NEW) != 0)
		return (1);
	return (0);
}

//static char	**val_manager(const char *path, char *pwd, char **result)
//{
//	int		i;
//	int		path_len;
//	int		pwd_len;
//	char	*ptr;
//
//	i = 0;
//	path_len = ft_strlen(path);
//	pwd_len = ft_strlen(pwd);
//	if (path[0] == '/')
//	{
//		*result = malloc(path_len + 1);
//		if (*result == NULL)
//			return (NULL);
//		ft_strlcpy(*result, path, path_len + 1);
//	}
//	else
//	{
//		*result = malloc(pwd_len + path_len + 1);
//		if (*result == NULL)
//			return (NULL);
//		ptr = *result;
//		i += ft_strlcpy(&ptr[i], pwd, pwd_len + 1);
//		i += ft_strlcpy(&ptr[i], "/", 2);
//		i += ft_strlcpy(&ptr[i], path, path_len + 1);
//	}
//	return (ft_split(*result, '/'));
//}

//static char	*normalize_path(const char *path, char *pwd)
//{
//	char	**sp;
//	char	*result;
//	int		i;
//	int		ri;
//
//	sp = val_manager(path, pwd, &result);
//	if (sp == NULL)
//		return (NULL);
//	ri = 0;
//	i = 0;
//	printf("%s\n", result);
//	while (sp[i] != NULL)
//	{
//		if (sp[i + 1] != NULL && ft_strncmp(sp[i + 1], "..", 3) == 0)
//			i += 2;
//		else if (ft_strncmp(sp[i], ".", 2) == 0
//			|| ft_strncmp(sp[i], "..", 3) == 0)
//			i++;
//		else
//		{
//			ri += ft_strlcpy(&result[ri], "/", 2);
//			ri += ft_strlcpy(&result[ri], sp[i], ft_strlen(sp[i]) + 1);
//			i++;
//		}
//	}
//	free_ptr_array(sp);
//	return (result);
//}

// ******** test for cannonical_file_path ********

//#include <string.h>
//#define GREEN "\x1b[32m"
//#define RED "\x1b[31m"
//#define RESET "\x1b[0m"
//
//int	main() {
//	char	*path = "../../../dd/cimy/../cimy/coding/42/my_shell/";
//	char	*result = normalize_path(path, "/It's/PWD/PATH");
//
//	// expected
//	// Users/cimy/coding/42/my_shell/microshell/src/libft/srcs
//
//	printf("BEFORE: %s\n", path);
//	printf("AFTER: %s\n", result);
//}
//
// ***********************************************

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
