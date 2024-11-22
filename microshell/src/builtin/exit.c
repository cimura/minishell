/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:53:50 by sshimura          #+#    #+#             */
/*   Updated: 2024/11/20 16:13:33 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	white_space(char check_chr)
{
	if (check_chr == ' ' || check_chr == '\t' || check_chr == '\n' || \
		check_chr == '\v' || check_chr == '\f' || check_chr == '\r')
		return (1);
	else
		return (0);
}

static int	decide_sign(const char *str, int *indx)
{
	int	sign;
	int	i;

	i = *indx;
	sign = 1;
	while (white_space(str[i]))
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
		if (!ft_isdigit(arg[i]))
			return (false);
		i++;
	}
	return (true);
}

static unsigned char	ex_atoi(char *arg)
{
	int		i;
	int		sign;
	int		result;

	i = 0;
	sign = decide_sign(arg, &i);
	result = 0;
	if (!ft_isnum(&arg[i]))
	{
		ft_putendl_fd(" numeric argument required", STDERR_FILENO);
		return (2);
	}
	while (arg[i] <= '9' && arg[i] >= '0')
	{
		result = result * 10 + (arg[i] - '0');
		i++;
	}
	return ((unsigned char)result * sign);
}

int	ft_exit(char **args, int *status)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (args == NULL || args[0] == NULL)
		return (0);
	else if (args[1] != NULL)
	{
		ft_putendl_fd(" too many arguments", STDERR_FILENO);
		*status = 1;
		return (1);
	}
	else
		*status = (int)ex_atoi(args[0]);
	return (*status);
}
