/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:48:03 by sshimura          #+#    #+#             */
/*   Updated: 2024/07/20 01:08:52 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strncpy(unsigned char *dst, unsigned char *src, size_t len)
{
	size_t	i;

	i = 0;
	if (dst < src)
	{
		while (i < len)
		{
			dst[i] = src[i];
			i++;
		}
	}
	else
	{
		while (i < len)
		{
			dst[len - 1] = src[len - 1];
			len--;
		}
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_ptr;
	unsigned char	*src_ptr;

	dst_ptr = (unsigned char *)dst;
	src_ptr = (unsigned char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	ft_strncpy(dst_ptr, src_ptr, len);
	return ((void *)dst_ptr);
}
