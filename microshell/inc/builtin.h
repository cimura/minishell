/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:05:10 by ttakino           #+#    #+#             */
/*   Updated: 2024/11/24 19:42:26 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H

# define BUILTIN_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "env_lst.h"
# include "libft.h"
# include "utils.h"

int	env(t_env *env_lst);
int	export(char **args, t_env *env_lst);
int	unset(char **args, t_env *env_lst);
int	echo(char **args);
int	cd(char **args, t_env *env_lst);
int	pwd(void);
int	ft_exit(char **args, int *status);

t_env	*get_max_key(t_env *env_lst);
int		count_env_lst(t_env *env_lst);
void	print_with_format(t_env *env_lst);

#endif
