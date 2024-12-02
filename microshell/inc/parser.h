/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:28:30 by ttakino           #+#    #+#             */
/*   Updated: 2024/12/02 14:15:49 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <stdio.h>
# include "libft.h"

typedef struct s_command_lst
{
	char					**command_line;
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
