/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:05:10 by ttakino           #+#    #+#             */
/*   Updated: 2024/11/13 17:45:20 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H

# define BUILTIN_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "env_lst.h"
# include "libft.h"

void	env(t_env *env_lst);
int		export(char **args, t_env *env_lst);
void	unset(char **args, t_env *env_lst);
void	echo(char **args);
int		cd(char **args);
void	pwd(void);
void	ft_exit(char **args);

#endif
