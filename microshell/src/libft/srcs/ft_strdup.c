/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:44:38 by sshimura          #+#    #+#             */
/*   Updated: 2024/11/13 15:34:55 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*result;
	size_t	str_len;
	int		i;

	i = 0;
	str_len = ft_strlen((char *)str);
	result = malloc(sizeof(char) * (str_len + 1));
	if (result == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
