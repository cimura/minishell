/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:36:17 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/12 16:36:19 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_ptr_array(char **ptr)
{
	int	i;

	if (ptr == NULL)
		return ;
	i = 0;
	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
}

char	*ft_strndup(const char *str, size_t n)
{
	char	*result;
	size_t	str_len;
	size_t	i;

	i = 0;
	str_len = ft_strlen((char *)str);
	if (n < str_len)
		result = malloc(sizeof(char) * (n + 1));
	else
		result = malloc(sizeof(char) * (str_len + 1));
	if (result == NULL)
		return (NULL);
	while (str[i] != '\0' && n > i)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strmerge(char *s1, char *s2)
{
	char	*new;

	if (s1 == NULL || s2 == NULL)
	{
		if (s1)
			free(s1);
		if (s2)
			free(s2);
		return (NULL);
	}
	new = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (new);
}

int	count_char_array_words(char **ptr)
{
	int	c;

	c = 0;
	while (ptr[c] != NULL)
		c++;
	return (c);
}

bool	is_whitespace(char check_chr)
{
	if (check_chr == ' ' || check_chr == '\t' || check_chr == '\n' || \
		check_chr == '\v' || check_chr == '\f' || check_chr == '\r')
		return (true);
	else
		return (false);
}

// void	d_print_per_pipe(t_command_lst *lst)
// {
// 	int	i;

// 	while (lst != NULL)
// 	{
// 		i = 0;
// 		while (lst->command_line[i] != NULL)
// 		{
// 			printf("%s: %d\n", lst->command_line[i], lst->is_expanded[i]);
// 			i++;
// 		}
// 		if (lst->next != NULL)
// 			printf("-------------pipe-------------\n");
// 		lst = lst->next;
// 	}
// }

// void	d_print_until_redirection(t_cmd_data *until_redirection)
// {
// 	int	i;

// 	if (until_redirection != NULL)
// 		printf("-----------until_redirection-----------\n");
// 	i = 0;
// 	if (until_redirection->path != NULL)
// 		printf("path = %s\n", until_redirection->path);
// 	if (until_redirection->cmd != NULL)
// 	{
// 		printf("cmd = \n");
// 		while (until_redirection->cmd[i] != NULL)
// 		{
// 			printf("%s\n", until_redirection->cmd[i]);
// 			i++;
// 		}
// 	}
// 	printf("------------------end-------------------\n");
// }

// void	d_print_char_array(char **array)
// {
// 	int	i;

// 	i = 0;
// 	while (array[i] != NULL)
// 	{
// 		fprintf(stderr, "%s\n", array[i]);
// 		i++;
// 	}
// }
