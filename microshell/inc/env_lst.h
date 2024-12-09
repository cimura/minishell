/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:27:28 by ttakino           #+#    #+#             */
/*   Updated: 2024/12/09 21:06:03 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_LST_H

# define ENV_LST_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	char			*cwd;
}	t_env;

// *** create_env_lst.c ***
void	env_lstadd_back(t_env **lst, t_env *new);
void	env_lstclear(t_env **lst);
t_env	*get_node_from_key(t_env *env_lst, char *key);
t_env	*create_env_lst(char *envp[]);

// *** env_lst_utils.c ***
char	*get_value_from_key(t_env *env_lst, char *key);
bool	is_envnode_exist(t_env *env_lst, char *key);

// *** env_lst_to_array.c ***
char	**env_lst_to_array(t_env *env_lst);

#endif