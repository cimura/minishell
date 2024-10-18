/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:05:10 by ttakino           #+#    #+#             */
/*   Updated: 2024/10/18 14:52:11 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H

# define ENV_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "../libft/include/libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

void	ft_free_env_node(t_env *node);
void	ft_env_lstadd_back(t_env **lst, t_env *new);
void	ft_env_lstclear(t_env **lst, void (*del)(t_env *));

t_env	*ft_env_list(char *envp[]);

void	env(t_env *env_lst);
int		export(char *command, t_env *env_lst);

void	env_with_arg(char *first_arg, char *second_arg, t_env *env_lst, char **envp);

#endif
