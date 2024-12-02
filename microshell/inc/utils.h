/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:24:28 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/02 15:50:00 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include "libft.h"
# include "env_lst.h"
# include "parser.h"
# include "exec.h"

// *** utils.c ***
void	free_ptr_array(char **ptr);
int		count_char_array_words(char **ptr);
char	*ft_strndup(const char *str, size_t n);
char	*ft_strmerge(char *s1, char *s2);;
bool	is_whitespace(char check_chr);

// *** utils2.c ***
int		count_key_size(char *line_ptr);
void	free_cmd_data(t_cmd_data *data);
bool	is_redirection(char *arg);

// *** main_helper.c ***
void	clear_exit(t_env *env_lst, t_command_lst *per_pipe, int exit_status);

#endif
