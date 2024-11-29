/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 01:01:06 by cimy              #+#    #+#             */
/*   Updated: 2024/11/29 16:24:02 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digit_count(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n > 0)
	{
		while (n > 0)
		{
			n = n / 10;
			count++;
		}
	}
	else
	{
		while (n < 0)
		{
			n = n / 10;
			count++;
		}
	}
	return (count);
}

static char	*malloc_memory(int n, int digit)
{
	char	*result;

	result = NULL;
	if (n < 0)
	{
		result = (char *)malloc(sizeof(char) * (digit + 2));
		if (result != NULL)
		{
			result[0] = '-';
			result[digit + 1] = '\0';
		}
	}
	else if (n >= 0)
	{
		result = (char *)malloc(sizeof(char) * (digit + 1));
		if (result != NULL)
			result[digit] = '\0';
	}
	return (result);
}

char	*ft_itoa(int n)
{
	int		digit;
	char	*result;

	digit = digit_count(n);
	result = malloc_memory(n, digit);
	if (result == NULL)
		return (NULL);
	while (digit > 0)
	{
		if (n >= 0)
			result[--digit] = (n % 10) + '0';
		else
			result[--digit + 1] = -(n % 10) + '0';
		n = n / 10;
	}
	return (result);
}
