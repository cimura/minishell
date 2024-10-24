/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:27:28 by ttakino           #+#    #+#             */
/*   Updated: 2024/10/23 19:31:45 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_LST_H

# define ENV_LST_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/include/libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

void	free_env_node(t_env *node);
void	env_lstadd_back(t_env **lst, t_env *new);
void	env_lstclear(t_env **lst, void (*del)(t_env *));

t_env	*create_env_lst(char *envp[]);

#endif