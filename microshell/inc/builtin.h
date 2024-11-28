/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:05:10 by ttakino           #+#    #+#             */
/*   Updated: 2024/11/28 19:05:31 by sshimura         ###   ########.fr       */
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
// # include "utils.h"

int	env(t_env *env_lst);
int	export(char **args, t_env *env_lst);
int	unset(char **args, t_env *env_lst);
int	echo(char **args);
int	cd(char **args, t_env *env_lst);
int	pwd(void);
int	ft_exit(char **args, int *status);

// *** export_util.c ***
int		generate_new_value(t_env *old_node, char *arg);
t_env	*create_new_env_node(char *arg);

// *** export_util2.c ***
char	*get_max_key(t_env *env_lst);
// t_env	*get_node_having_same_key(char *arg, t_env *env_lst);
int		count_env_lst(t_env *env_lst);
void	print_with_format(t_env *env_lst);

#endif
