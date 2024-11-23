/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 00:01:53 by cimy              #+#    #+#             */
/*   Updated: 2024/11/23 19:28:47 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H

# define SYNTAX_H

#include <stdbool.h>
#include <sys/stat.h>
#include "env_lst.h"
#include "lexer.h"

int	stash_token_empty_ptrs(t_token *token);
int check_syntax_before_lexer(char *line);
int check_syntax(t_token *token, t_env *env_lst);

#endif
