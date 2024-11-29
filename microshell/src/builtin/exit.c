/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:53:50 by sshimura          #+#    #+#             */
/*   Updated: 2024/11/29 18:41:52 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

#define ULONGLONG_MAX (unsigned long long)__LONG_LONG_MAX__ 

static int	decide_sign(const char *str, int *indx)
{
	int	sign;
	int	i;

	i = *indx;
	sign = 1;
	while (is_whitespace(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	*indx = i;
	return (sign);
}

static bool	ft_isnum(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (!ft_isdigit(arg[i]) && !is_whitespace(arg[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	ex_atoi(char *arg, int *status)
{
	int					i;
	int					sign;
	unsigned long long	result;

	i = 0;
	sign = decide_sign(arg, &i);
	result = 0;
	if (!ft_isnum(&arg[i]))
	{
		ft_putendl_fd(" numeric argument required", STDERR_FILENO);
		return (*status = 2, EXIT_FAILURE);
	}
	while (arg[i] <= '9' && arg[i] >= '0')
	{
		result = result * 10 + (arg[i] - '0');
		if ((result > ULONGLONG_MAX && sign == 1)
			|| (result > (ULONGLONG_MAX + 1) && sign == -1))
		{
			ft_putendl_fd(" numeric argument required", STDERR_FILENO);
			return (*status = 2, EXIT_FAILURE);
		}
		i++;
	}
	*status = (unsigned char)result * sign;
	return (EXIT_SUCCESS);
}

int	ft_exit(char **args, int *status)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (args == NULL || args[0] == NULL)
		return (0);
	if (ex_atoi(args[0], status) == 1)
		return (*status);
	if (args[1] != NULL)
	{
		ft_putendl_fd(" too many arguments", STDERR_FILENO);
		*status = 1;
		return (1);
	}
	return (*status);
}
