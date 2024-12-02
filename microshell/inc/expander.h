/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:49:07 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/02 20:49:27 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# include "env_lst.h"
# include "utils.h"

// *** expander.c ***
int		expander(t_env *env_lst, t_command_lst *per_pipe, int end_status);

// *** expand_dollar.c ***
char	*expand_env_variable(t_env *env_lst, char *lst_line, int end_status);

// ** expand_dollar_utils.c ***

char	*env_query(t_env *env_lst, char *new, char *line_ptr, int end_status);
char	*non_expandble_str(char *new, char *line_ptr, char *stopper);
int		count_until_char(char *line, char *needle);
int		count_key_size(char *line_ptr);
char	*get_value_from_key(t_env *env_lst, char *key);

// *** expand_quotes.c ***
char	*remove_quotes(char *line);

#endif
