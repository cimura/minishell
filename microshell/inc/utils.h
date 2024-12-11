/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:24:28 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/11 12:28:57 by cimy             ###   ########.fr       */
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

# define CONTINUE	3
# define GREEN		"\x1b[32m"
# define RED		"\x1b[31m"
# define RESET		"\x1b[0m"

// *** utils.c ***
void	free_ptr_array(char **ptr);
int		count_char_array_words(char **ptr);
char	*ft_strndup(const char *str, size_t n);
char	*ft_strmerge(char *s1, char *s2);;
bool	is_whitespace(char check_chr);

// *** utils2.c ***
int		dollar_variable_size(char *line_ptr);
void	free_cmd_data(t_cmd_data *data);
bool	is_redirection(char *arg);
void	print_error_msg(char *cmd_name, bool arg_decorate,
			char *arg_name, char *err_msg);
void	clear_exit(t_env *env_lst, t_command_lst *per_pipe, int exit_status);

// *** utils3.c ***
bool	is_ifs_in_str(t_env *env_lst, char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strcpy(char *dst, char *src, int size);
int		init_mobile(t_env *env_lst, t_mobile *mobile);

#endif
