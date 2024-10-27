/* ************************************************************************** */ /*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:28:31 by ttakino           #+#    #+#             */
/*   Updated: 2024/10/27 15:57:42 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

//# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/include/libft.h"

typedef struct s_token
{
	char			**command_line;
	struct s_token	*next;
}	t_token;

// *** lexer_util.c ***
void	token_lst_clear(t_token **lst, void (*del)(char **));
void	token_lstadd_back(t_token **lst, t_token *new);
void	free_commands(char **commands);
//void	print_commands(char **commands);

#endif
