/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:28:30 by ttakino           #+#    #+#             */
/*   Updated: 2024/12/02 13:35:34 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
// # include "utils.h"

typedef struct s_token
{
	char			**command_line;
	struct s_token	*next;
	pid_t			pid;
}	t_token;

// *** parser_helper.c ***
t_list	*create_token_lst(char *line);

// *** parser_util.c ***
void	token_lstclear(t_token **lst);
void	token_lstadd_back(t_token **lst, t_token *new);

// *** parser.c ***
t_token	*parser(char	*line);

// debug
// void	d_print_token_lst(t_token *token);

#endif
