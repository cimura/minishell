/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 00:01:53 by cimy              #+#    #+#             */
/*   Updated: 2024/12/11 12:28:46 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H

# define SYNTAX_H

# include <stdbool.h>
# include "env_lst.h"
# include "parser.h"
# include "utils.h"

# define SINGLE	'\''
# define DOUBLE	'\"'
# define OUT	'\0'

// *** check_syntax.c ***
int		check_syntax_before_parser(char *line, int *status);
int		check_syntax(t_command_lst *per_pipe, t_env *env_lst);

// *** syntax_utils.c ***
bool	is_redirection(char *arg);
int		check_quotation(char *line);
int		pipe_redirect_combination_error(char *arg, char *next, t_env *env_lst);

#endif
