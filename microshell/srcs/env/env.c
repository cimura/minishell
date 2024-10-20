/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:32:43 by ttakino           #+#    #+#             */
/*   Updated: 2024/10/20 17:54:33 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// ***************************************************************************
// util

// char	*get_exec_path(char **paths, char **command, char **envp)
// {
// 	int		i;
// 	char	*path;
// 	char	*before_join;

// 	i = 0;
// 	// error_check(paths, command, envp);
// 	while (paths[i] != NULL)
// 	{
// 		before_join = ft_strjoin(paths[i], "/");
// 		path = ft_strjoin(before_join, command[0]);
// 		free(before_join);
// 		if (access(path, F_OK) == 0)
// 			return (path);
// 		free(path);
// 		i++;
// 	}
// 	return (NULL);
// }

// char	**setup_paths(char *envp[])
// {
// 	char	**paths;

// 	if (!envp || !*envp)
// 		return (NULL);
// 	paths = ft_split(getenv("PATH"), ':');
// 	return (paths);
// }
// //

// // *************************************************************************

// void	env_with_arg(char *first_arg, char *second_arg, t_env *env_lst, char **envp)
// {
//   // 引数なし->リストを表示
//   if (!first_arg && !second_arg)
//   {
//     int	i;

//     i = 0;
//     while (env_lst != NULL)
//     {
//       printf("%s=%s\n", env_lst->key, env_lst->value);
//       env_lst = env_lst->next;
//     }
//   }
//   // リストに加えて表示 (仮)
//   else if (first_arg && !second_arg)
//   {
//     int	i;

//     i = 0;
//     while (env_lst != NULL)
//     {
//       printf("%s=%s\n", env_lst->key, env_lst->value);
//       env_lst = env_lst->next;
//     }
//     printf("%s\n", first_arg);
//   }
//   else if (first_arg && second_arg)
//   {
//     pid_t pid;
//     char **paths = setup_paths(envp);

//     pid = fork();
//     if (pid == -1)
//       perror("fork");
//     if (pid == 0)
//     {
//       char **command = ft_split(second_arg, ' ');
//       char *executable_path  = get_exec_path(paths, command, envp);
//       execve(executable_path, &command[0], envp);
//       perror("execve failed");
//       exit(EXIT_FAILURE);
//     }
//     else
//       wait(NULL);
//   }
// }

// 引数なしでいいと思う
void	env(t_env *env_lst)
{
	int	i;

	i = 0;
	while (env_lst != NULL)
	{
		printf("%s=%s\n", env_lst->key, env_lst->value);
		env_lst = env_lst->next;
	}
}

// int    main(int argc, char *argv[], char *envp[])
// {
// 	int	i;
// 	t_env	*head;
// 	t_env	*env_lst;

// 	env_lst = ft_env_lst(envp);
// 	if (!env_lst)
// 		return (1);
// 	head = env_lst;
// 	i = 0;

// 	env(env_lst);
// //   if (argc == 1)
// //     env_with_arg(NULL, NULL, env_lst, envp);
// //   else if (argc == 2)
// //     env_with_arg(argv[1], NULL, env_lst, envp);
// //   else if (argc == 3)
// //     env_with_arg(argv[1], argv[2], env_lst, envp);

// 	// while (env_lst != NULL)
// 	// {
// 	// 	printf("%s=%s\n", env_lst->key, env_lst->value);
// 	// 	env_lst = env_lst->next;
// 	// }
// 	ft_env_lstclear(&head, ft_free_env_node);
// }
