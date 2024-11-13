/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:46:48 by cimy              #+#    #+#             */
/*   Updated: 2024/09/09 10:57:42 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	count_word(char const *str, char charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != charset && (i == 0 || str[i - 1] == charset))
			count++;
		i++;
	}
	return (count);
}

static size_t	ft_strlen(char const *str, char charset, int indx)
{
	size_t	count;

	count = 0;
	while (str[indx] != '\0' && str[indx] != charset)
	{
		count++;
		indx++;
	}
	return (count);
}

static char	**free_all(char **result, int i)
{
	while (i >= 0)
	{
		free(result[i]);
		i--;
	}
	free(result);
	return (NULL);
}

static char	**loop(char **result, const char *str, char charset, int word_count)
{
	int	i;
	int	j;
	int	str_len;
	int	str_indx;

	i = 0;
	str_indx = 0;
	while (i < word_count)
	{
		while (str[str_indx] == charset)
			str_indx++;
		str_len = ft_strlen(str, charset, str_indx);
		result[i] = malloc(str_len + 1);
		if (!result[i])
			return (free_all(result, i - 1));
		j = 0;
		while (j < str_len)
			result[i][j++] = str[str_indx++];
		result[i][j] = '\0';
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *str, char charset)
{
	char	**result;
	int		word_count;

	if (!str)
		return (NULL);
	word_count = count_word(str, charset);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	return (loop(result, str, charset, word_count));
}
