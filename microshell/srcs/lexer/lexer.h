/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:28:31 by ttakino           #+#    #+#             */
/*   Updated: 2024/10/16 17:33:22 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H

# define LEXER_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/include/libft.h"

typedef struct s_token
{
	char			**command_line;
	struct s_token	*next;
}	t_token;

void	ft_token_lst_clear(t_token **lst, void (*del)(char **));
void	ft_token_lstadd_back(t_token **lst, t_token *new);

void	ft_free_commands(char **commands);
void	ft_print_commands(char **commands);

#endif