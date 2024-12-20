/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:08:10 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/12 16:38:14 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "syntax.h"

static bool	is_skip_quote(char line_chr, char *quote_flag)
{
	if (*quote_flag == OUT && line_chr == SINGLE)
	{
		*quote_flag = SINGLE;
		return (true);
	}
	else if (*quote_flag == OUT && line_chr == DOUBLE)
	{
		*quote_flag = DOUBLE;
		return (true);
	}
	if (*quote_flag == SINGLE && line_chr == SINGLE)
	{
		*quote_flag = OUT;
		return (true);
	}
	else if (*quote_flag == DOUBLE && line_chr == DOUBLE)
	{
		*quote_flag = OUT;
		return (true);
	}
	return (false);
}

char	*remove_quotes(char *line)
{
	char	*result;
	char	quote_flag;
	int		i;

	if (line == NULL)
		return (NULL);
	result = malloc(ft_strlen(line) + 1);
	if (result == NULL)
		return (NULL);
	quote_flag = OUT;
	i = 0;
	while (*line)
	{
		if (is_skip_quote(*line, &quote_flag) == true)
		{
			line++;
			continue ;
		}
		result[i++] = *line;
		line++;
	}
	result[i] = '\0';
	return (result);
}

//int	main(int argc, char **argv, char **envp)
//{
//	(void)argc;
//	(void)argv;
//	//char	*line = "hello \'wo\'$ world\"$PATH!!!\"";
//   char	*line = "\"value = \"\"$HOME!?$SHELL$\"\'($HOME)\'";
//   char	*com;
//	t_env	*env_lst = create_env_lst(envp);
//
//	char *result_line = expand_quotes(env_lst, line);
//   if (result_line == NULL)
//   {
//   	env_lstclear(&env_lst);
//   	return (0);
//   }
//   printf("\x1b[33m%s\x1b[0m\n", line);
//   com = ft_strjoin("echo ", line);
//   printf("echo\n");
//   system(com);
//	printf("./expand\n%s\n", result_line);
//	env_lstclear(&env_lst);
//	free(result_line);
//}
