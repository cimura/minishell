/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:32:43 by ttakino           #+#    #+#             */
/*   Updated: 2024/10/18 10:38:18 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

// *******************************************************************************************
// util
void	ft_env_lstclear(t_env **lst, void (*del)(t_env *))
{
	t_env	*current;
	t_env	*next;

	if (lst == NULL || del == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		del(current);
		free(current);
		current = next;
	}
	*lst = NULL;
}

int	set_key_value(t_env *new, char *line)
{
	int	len;
	int	klen;
	int	vlen;

	len = ft_strlen(line);
	vlen = ft_strlen(ft_strchr(line, '=') + 1);
	klen = len - vlen - 1;
	new->key = malloc(klen + 1);
	if (!new->key)
		return (0);
	new->value = malloc(vlen + 1);
	if (!new->value)
		return (free(new->key), new->key = NULL, 0);
	new->key = ft_memmove(new->key, line, klen);
	new->key[klen] = '\0';
	new->value = ft_memmove(new->value, &line[klen + 1], vlen);
	new->value[vlen] = '\0';
	return (1);
}

t_env	*ft_env_list(char *envp[])
{
	int		i;
	t_env	*head;
	t_env	*new;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (NULL);
		if (!set_key_value(new, envp[i]))
			return (free(new), new = NULL,
				ft_env_lstclear(&head, ft_free_env_node), NULL);
		new->next = NULL;
		ft_env_lstadd_back(&head, new);
		i++;
	}
	return (head);
}

void	ft_env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	last = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
}

void	ft_free_env_node(t_env *node)
{
	free(node->key);
	node->key = NULL;
	free(node->value);
	node->value = NULL;
}

char	*get_exec_path(char **paths, char **command, char **envp)
{
	int		i;
	char	*path;
	char	*before_join;

	i = 0;
	// error_check(paths, command, envp);
	while (paths[i] != NULL)
	{
		before_join = ft_strjoin(paths[i], "/");
		path = ft_strjoin(before_join, command[0]);
		free(before_join);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	**setup_paths(char *envp[])
{
	char	**paths;

	if (!envp || !*envp)
		return (NULL);
	paths = ft_split(getenv("PATH"), ':');
	return (paths);
}
//

// *******************************************************************************************



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

void	env_with_arg(char *first_arg, char *second_arg, t_env *env_lst, char **envp)
{
  // 引数なし->リストを表示
  if (!first_arg && !second_arg)
  {
    int	i;

    i = 0;
    while (env_lst != NULL)
    {
      printf("%s=%s\n", env_lst->key, env_lst->value);
      env_lst = env_lst->next;
    }
  }
  // リストに加えて表示 (仮)
  else if (first_arg && !second_arg)
  {
    int	i;

    i = 0;
    while (env_lst != NULL)
    {
      printf("%s=%s\n", env_lst->key, env_lst->value);
      env_lst = env_lst->next;
    }
    printf("%s\n", first_arg);
  }
  else if (first_arg && second_arg)
  {
    pid_t pid;
    char **paths = setup_paths(envp);

    pid = fork();
    if (pid == -1)
      perror("fork");
    if (pid == 0)
    {
      char **command = ft_split(second_arg, ' ');
      char *executable_path  = get_exec_path(paths, command, envp);
      execve(executable_path, &command[0], envp);
      perror("execve failed");
      exit(EXIT_FAILURE);
    }
    else
      wait(NULL);
  }
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
  if (argc == 1)
    env_with_arg(NULL, NULL, env_lst, envp);
  else if (argc == 2)
    env_with_arg(argv[1], NULL, env_lst, envp);
  else if (argc == 3)
    env_with_arg(argv[1], argv[2], env_lst, envp);

	// while (env_lst != NULL)
	// {
	// 	printf("%s=%s\n", env_lst->key, env_lst->value);
	// 	env_lst = env_lst->next;
	// }
	ft_env_lstclear(&head, ft_free_env_node);
}