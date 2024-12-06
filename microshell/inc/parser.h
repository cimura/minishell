/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:28:30 by ttakino           #+#    #+#             */
/*   Updated: 2024/12/06 13:41:20 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include "libft.h"

// typedef struct s_token
// {
// 	char	*str;
// 	bool	is_expanded;
// }	t_token;

typedef struct s_command_lst
{
	char					**command_line;
	bool					*is_expanded;
	struct s_command_lst	*next;
	pid_t					pid;
}	t_command_lst;

// *** parser_helper.c ***
t_list			*create_command_lst(char *line);

// *** parser_util.c ***
void			command_lstclear(t_command_lst **lst);
void			command_lstadd_back(t_command_lst **lst, t_command_lst *new);

// *** parser.c ***
t_command_lst	*parser(char *line);

#endif
