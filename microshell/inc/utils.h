/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:24:28 by sshimura          #+#    #+#             */
/*   Updated: 2024/11/27 16:09:11 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

void	free_ptr_array(char **ptr);
int		count_char_array_words(char **ptr);
char	*ft_strndup(const char *str, size_t n);
int		white_space(char check_chr);

// Debug
void	d_print_char_array(char **array);

#endif
