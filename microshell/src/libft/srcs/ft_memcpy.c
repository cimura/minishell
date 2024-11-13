/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:49:10 by sshimura          #+#    #+#             */
/*   Updated: 2024/07/20 01:06:23 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			count;
	unsigned char	*dst_ptr;
	unsigned char	*src_ptr;

	count = 0;
	dst_ptr = (unsigned char *)dst;
	src_ptr = (unsigned char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (count < n)
	{
		dst_ptr[count] = src_ptr[count];
		count++;
	}
	return (dst);
}
