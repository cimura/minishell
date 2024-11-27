/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 00:01:53 by cimy              #+#    #+#             */
/*   Updated: 2024/11/27 16:23:10 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H

# define SYNTAX_H

# include <stdbool.h>
# include <sys/stat.h>
# include "env_lst.h"
# include "lexer.h"
# include "utils.h"

// *** check_syntax.c ***
int		stash_token_empty_ptrs(t_token *token);
int		check_syntax_before_lexer(char *line);
int		check_syntax(t_token *token);

// *** check_syntax.c ***
bool	is_redirection(char *arg);
int		check_quotation(char *line);
int		dir_permission(char *arg);
int		pipe_redirect_combination_error(char *arg, char *next);
int		check_permission(t_token *token);
#endif
