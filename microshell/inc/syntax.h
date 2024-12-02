/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 00:01:53 by cimy              #+#    #+#             */
/*   Updated: 2024/12/02 13:39:37 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H

# define SYNTAX_H

# include <stdbool.h>
# include <sys/stat.h>
# include "env_lst.h"
# include "parser.h"
# include "utils.h"

// *** check_syntax.c ***
int		check_syntax_before_parser(char *line);
int		check_syntax(t_token *token);

// *** syntax_utils.c ***
bool	is_redirection(char *arg);
int		check_quotation(char *line);
int		dir_permission(char *arg);
int		pipe_redirect_combination_error(char *arg, char *next);
int		check_permission(t_token *token);

#endif
