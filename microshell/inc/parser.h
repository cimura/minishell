/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:28:30 by ttakino           #+#    #+#             */
/*   Updated: 2024/12/11 12:29:08 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include "libft.h"

# define END	-1
# define NONE	0
# define ENV	1
# define QUOTE	2
# define BOTH	3

typedef struct s_command_lst
{
	char					**command_line;
	int						*is_expanded;
	struct s_command_lst	*next;
	pid_t					pid;
}	t_command_lst;

// *** parser_helper.c ***
t_list			*create_t_lst(char *line);

// *** parser_util.c ***
void			command_lstclear(t_command_lst **lst);
void			command_lstadd_back(t_command_lst **lst, t_command_lst *new);
char			**create_until_pipe_array(t_list *normal, int size);
int				*create_is_expanded_array(int size);

// *** parser.c ***
t_command_lst	*parser(char *line);

#endif
