/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:28:30 by ttakino           #+#    #+#             */
/*   Updated: 2024/11/03 14:46:33 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <stdio.h>
# include "../libft/include/libft.h"

typedef struct s_token
{
	char			**command_line;
	struct s_token	*next;
}	t_token;

// *** lexer_helper.c ***
t_list	*create_token_lst(char *line);

// *** lexer_util.c ***
void	token_lst_clear(t_token **lst, void (*del)(char **));
void	token_lstadd_back(t_token **lst, t_token *new);
void	free_commands(char **commands);

// *** lexer.c ***
t_token	*lexer(char	*line);

#endif
