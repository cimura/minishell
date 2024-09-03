/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:13:13 by cimy              #+#    #+#             */
/*   Updated: 2024/07/20 01:10:06 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		len;
	char	*result;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	len = ft_strlen(s1);
	while (s1[start] != '\0' && ft_strchr(set, s1[start]) != NULL)
		start++;
	while (len > start && ft_strchr(set, s1[len - 1]) != NULL)
		len--;
	result = ft_substr(s1, start, len - start);
	return (result);
}
