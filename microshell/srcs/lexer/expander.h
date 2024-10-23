/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:49:07 by sshimura          #+#    #+#             */
/*   Updated: 2024/10/23 19:29:56 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <string.h>
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
	struct s_expand_lst	*next;
	int					status;
}	t_expand_lst;

// *** expander_util.c ***
int				str_count(char *line, char *meta_char);
void			expand_lstclear(t_expand_lst **lst);
void			expand_lstadd_back(t_expand_lst **lst, t_expand_lst *new);
char			*ft_strndup(const char *str, size_t n);
int				count_until_char(char *line, char *needle);

// *** expander_helper.c ***
char			*env_query(t_env *env_lst, char *new, char *line_ptr);
char			*non_expandble_str(char *new, char *line_ptr);
char			*expand_env_variable(t_env *env_lst, char *lst_line);
int				split_quoted_segment(t_expand_lst *new, t_expand_lst *head,
					char *line_ptr, int flag);
t_expand_lst	*create_quoted_lst(char *line);

#endif