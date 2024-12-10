/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:05:10 by ttakino           #+#    #+#             */
/*   Updated: 2024/12/10 15:55:35 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H

# define BUILTIN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>
# include "env_lst.h"
# include "utils.h"

typedef struct s_stack
{
	int		tail;
	int		max;
	char	**ptr;
}	t_stack;

enum
{
	NOPIPE,
	WITHPIPE
};

// *** builtin ***
int		cd(char **args, t_env *env_lst, t_mobile *mobile);
int		echo(char **args);
int		env(t_env *env_lst);
int		ft_exit(char **args, int *status, int print);
int		export(char **args, t_env *env_lst);
int		pwd(char *cwd);
int		unset(char **args, t_env *env_lst);

// *** cd_stack.c ***
int		init_stack(t_stack *stack, char **sp);
void	push(t_stack *stack, char *arg);
void	pop(t_stack *stack);
void	free_stack(t_stack *stack);

// *** normalize_path.c ***
char	*normalize_path(char *path, char *pwd);

// *** export_util.c ***
int		generate_new_value(t_env *old_node, char *arg);
t_env	*create_new_env_node(char *arg);

// *** export_util2.c ***
char	*get_max_key(t_env *env_lst);
int		count_env_lst(t_env *env_lst);
void	print_with_format(t_env *env_lst);

#endif
