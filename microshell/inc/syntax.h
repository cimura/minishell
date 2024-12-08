/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 00:01:53 by cimy              #+#    #+#             */
/*   Updated: 2024/12/08 19:08:41 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H

# define SYNTAX_H

# include <stdbool.h>
# include "env_lst.h"
# include "parser.h"
# include "utils.h"

// *** check_syntax.c ***
int		check_syntax_before_parser(char *line, int *status);
int		check_syntax(t_command_lst *per_pipe, t_env *env_lst);

// *** syntax_utils.c ***
bool	is_redirection(char *arg);
bool	is_ifs_in_str(t_env *env_lst, char *key);
int		check_quotation(char *line);
int		pipe_redirect_combination_error(char *arg, char *next, t_env *env_lst);

#endif
