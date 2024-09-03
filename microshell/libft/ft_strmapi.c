/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:49:03 by sshimura          #+#    #+#             */
/*   Updated: 2024/07/20 01:15:08 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_int_strlen(const char *str)
{
	int	count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	s_len;
	char			*result;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (s[0] == '\0')
		return (ft_strdup(""));
	s_len = ft_int_strlen(s);
	result = (char *)malloc(sizeof(char) * (s_len + 1));
	if (result == NULL)
		return (NULL);
	while (i < s_len)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
