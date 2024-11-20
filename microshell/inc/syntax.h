/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 00:01:53 by cimy              #+#    #+#             */
/*   Updated: 2024/11/21 00:30:33 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H

# define SYNTAX_H

#include <stdbool.h>
#include "env_lst.h"
#include "lexer.h"

int check_syntax(t_env *env_lst, t_token *token);

#endif