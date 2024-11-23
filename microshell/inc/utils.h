/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:24:28 by sshimura          #+#    #+#             */
/*   Updated: 2024/11/15 16:23:16 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

void	free_ptr_array(char **ptr);
int		count_char_array_words(char **ptr);

// Debug
void	d_print_char_array(char **array);

#endif