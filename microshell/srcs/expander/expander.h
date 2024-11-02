/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:49:07 by sshimura          #+#    #+#             */
/*   Updated: 2024/11/02 17:34:44 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <stdlib.h>
# include <stdio.h>
# include "../libft/include/libft.h"
# include "../env/env_lst.h"

enum	e_status
{
	SINGLE,
	DOUBLE,
	OUT
};

typedef struct s_expand_lst
{
	char				*str;
	int					status;
	struct s_expand_lst	*next;
}	t_expand_lst;

// *** expander_util.c ***
int				str_count(char *line, char *meta_char);
void			expand_lstclear(t_expand_lst **lst);
void			expand_lstadd_back(t_expand_lst **lst, t_expand_lst *new);
char			*ft_strndup(const char *str, size_t n);
int				count_until_char(char *line, char *needle);
// *** expander_helper.c ***
char			*expand_env_variable(t_env *env_lst, char *lst_line);

#endif
