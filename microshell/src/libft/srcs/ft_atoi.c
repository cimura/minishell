/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:56:59 by sshimura          #+#    #+#             */
/*   Updated: 2024/11/20 15:54:43 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	whitespace(char check_chr)
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
	while (whitespace(str[i]))
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

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = decide_sign(str, &i);
	result = 0;
	while (str[i] <= '9' && str[i] >= '0')
	{
		if (result > (LONG_MAX - (str[i] - '0')) / 10)
		{
			if (sign > 0)
				return ((int)LONG_MAX);
			else
				return ((int)LONG_MIN);
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return ((int)result * sign);
}
