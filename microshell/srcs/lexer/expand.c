/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:54:58 by sshimura          #+#    #+#             */
/*   Updated: 2024/10/21 17:44:09 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

typedef struct s_str_config
{
	int	ri;
	int	li;
	int	s_flag;
	int	d_flag;
}	t_str_config;

static int	ft_str_count(char *line, char *meta_char)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (ft_strchr(meta_char, line[i]))
		{
			count++;
		}
		i++;
	}
	return (count);
}

// bool	is_expand_error(char *line, int meta_count)
// {
// 	if (line[0] != '\'' && line[0] != '\"')
// 		return (NULL);

// 	if (meta_count % 2 != 0)
// 		return (NULL);
// }

void	init_str_config(t_str_config *conf)
{
	conf->ri = 0;
	conf->li = 0;
	conf->s_flag = 0;
	conf->d_flag = 0;
}



char	*overwrite(char *line, char *result)
{
	t_str_config	conf;

	init_str_config(&conf);
	while (line[conf.li])
	{
		if (conf.s_flag == 0 && conf.d_flag == 0 && line[conf.li++] == '\'')
			conf.s_flag = 1;
		else if (conf.s_flag == 0 && conf.d_flag == 0 && line[conf.li++] == '\"')
			conf.d_flag = 1;
		if (conf.s_flag == 1 && line[conf.li++] == '\'')
			conf.s_flag = 0;
		else if (conf.d_flag == 1 && line[conf.li++] == '\"')
			conf.d_flag = 0;
		// else if (conf.d_flag == 1)
		// {
		// 	if (line[conf.li] == '$')
		// }
		else
		{
			result[conf.ri] = line[conf.li];
			conf.li++;
			conf.ri++;
		}
	}
	if (conf.s_flag == 1 || conf.d_flag == 1)
		return (free(result), NULL);
	result[conf.ri] = '\0';
	return (NULL);
}


char	*ft_expand_env_variable(char **line_ptr)
{
	int	meta_count;

	char	*line = *line_ptr;
	char	*result;
	meta_count = ft_str_count(line, "\'");

	result = malloc(ft_strlen(line) - meta_count + 1);
	if (result == NULL)
		return (NULL);
	// while (line[li])
	// {
	// 	if (s_flag == 0 && d_flag == 0 && line[li++] == '\'')
	// 		s_flag = 1;
	// 	else if (s_flag == 0 && d_flag == 0 && line[li++] == '\"')
	// 		d_flag = 1;
	// 	if (s_flag == 1 && line[li++] == '\'')
	// 		s_flag = 0;
	// 	else if (d_flag == 1 && line[li++] == '\"')
	// 		d_flag = 0;
	// 	// else if (d_flag == 1)
	// 	// {
	// 	// 	if (line[li] == '$')
	// 	// }
	// 	else
	// 	{
	// 		result[ri] = line[li];
	// 		li++;
	// 		ri++;
	// 	}
	// }
	// if (s_flag == 1 || d_flag == 1)
	// 	return (free(result), NULL);
	// result[ri] = '\0';
	return (result);
}

// void	ft_expand(t_token *token, t_env *env_lst)
// {
// 	int		i;
// 	t_token	*head;

// 	head = token;
// 	while (token != NULL)
// 	{
// 		i = 0;
// 		while (token->command_line[i])
// 		{
// 			ft_expand_env_variable(env_lst, &command_line[i]);
// 			i++;
// 		}
// 		token = token->next;
// 	}
// }

// int	main()
// {
// 	// int	i;
// 	// t_env	*head;
// 	// t_env	*env_lst;

// 	// env_lst = ft_env_list(envp);
// 	// if (!env_lst)
// 	// 	return (1);
// 	// ft_expand()
// 	char *ptr = "\'\'\"hello\"\"";
// 	char *result = ft_expand_env_variable(&ptr);
// 	printf("result: %s\n", result);
// }