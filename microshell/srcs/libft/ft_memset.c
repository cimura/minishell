/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:47:17 by sshimura          #+#    #+#             */
/*   Updated: 2024/07/20 01:08:57 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*b_ptr;
	size_t			i;

	b_ptr = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		b_ptr[i] = c;
		i++;
	}
	return ((void *)b_ptr);
}
