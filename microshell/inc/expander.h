/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:49:07 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/09 18:25:08 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# include "env_lst.h"
# include "utils.h"

typedef struct s_expand_lst
{
	char				*str;
	int					status;
	struct s_expand_lst	*next;
}	t_expand_lst;

// *** expander.c ***
int				expander(t_env *env_lst,
					t_command_lst *per_pipe, int end_status);

// *** expander_lst.c ***
int				add_new_node_expand_lst(t_expand_lst **head,
					char *expanded, int is_expanded);
void			expand_lstadd_back(t_expand_lst **head, t_expand_lst *new);
void			expand_lstclear(t_expand_lst **head);
t_expand_lst	*expand_lstnew(char	*str, int status);
int				expand_lstsize(t_expand_lst *lst);

// *** add_node_with_split_ifs.c ***
int				add_node_with_split_ifs(t_env *env_lst,
					t_expand_lst **head, char *expand);

// *** expand_dollar.c ***
char			*expand_env_variable(t_env *env_lst,
					char *lst_line, int end_status);

// ** expand_dollar_utils.c ***

char			*env_query(t_env *env_lst,
					char *new, char *line_ptr, int end_status);
char			*non_expandble_str(char *new, char *line_ptr, char *stopper);
int				count_until_char(char *line, char *needle);
int				dollar_variable_size(char *line_ptr);
char			*get_value_from_key(t_env *env_lst, char *key);

// *** expand_quotes.c ***
char			*remove_quotes(char *line);

#endif
