/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:28:30 by ttakino           #+#    #+#             */
/*   Updated: 2024/11/29 16:14:53 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

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

// *** lexer_helper.c ***
t_list	*create_token_lst(char *line);

// *** lexer_util.c ***
void	token_lstclear(t_token **lst);
void	token_lstadd_back(t_token **lst, t_token *new);

// *** lexer.c ***
t_token	*lexer(char	*line);

// debug
// void	d_print_token_lst(t_token *token);

#endif
