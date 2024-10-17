/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:05:10 by ttakino           #+#    #+#             */
/*   Updated: 2024/10/17 17:14:24 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H

# define ENV_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "../libft/include/libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

#endif
