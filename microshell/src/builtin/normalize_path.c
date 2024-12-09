/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 23:24:08 by cimy              #+#    #+#             */
/*   Updated: 2024/12/09 12:55:28 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

typedef struct	s_stack
{
	int		tail;
	int		max;
	char	**ptr;
}	t_stack;

static int	init_stack(t_stack **stack, char **sp)
{
	*stack = malloc(sizeof(t_stack));
	if (*stack == NULL)
		return (1);
	(*stack)->tail = -1;
	(*stack)->max = count_char_array_words(sp) + 1;
	(*stack)->ptr = sp;
	if ((*stack)->ptr == NULL)
		return (1);
	return (0);
}

static void	push(t_stack **stack, char *arg)
{
	if ((*stack)->tail > (*stack)->max)
		return ;
	(*stack)->tail++;
	(*stack)->ptr[(*stack)->tail] = arg;
}

static void	pop(t_stack **stack)
{
	if ((*stack)->tail == -1)
		return ;
	(*stack)->ptr[(*stack)->tail] = NULL;
	(*stack)->tail--;
}

static char	**val_manager(const char *path, char *pwd)
{
	int		i;
	int		path_len;
	int		pwd_len;
	char	*sp_src;

	i = 0;
	path_len = ft_strlen(path);
	pwd_len = ft_strlen(pwd);
	if (path[0] == '/')
	{
		sp_src = malloc(path_len + 1);
		if (sp_src == NULL)
			return (NULL);
		ft_strlcpy(sp_src, path, path_len + 1);
	}
	else
	{
		sp_src = malloc(pwd_len + path_len + 1);
		if (sp_src == NULL)
			return (NULL);
		i += ft_strlcpy(&sp_src[i], pwd, pwd_len + 1);
		i += ft_strlcpy(&sp_src[i], "/", 2);
		i += ft_strlcpy(&sp_src[i], path, path_len + 1);
	}
	return (ft_split(sp_src, '/'));
}

static int	create_stack(const char *path, char *pwd, t_stack **stack)
{
	int		i;
	char	**sp;

	sp = val_manager(path, pwd);
	if (sp == NULL)
		return (1);
	if (init_stack(stack, sp) == 1)
		return (1);
	i = 0;
	while (sp[i] != NULL)
	{
		if (ft_strncmp(sp[i], "..", 3) == 0)
			pop(stack);
		else if (ft_strncmp(sp[i], ".", 2) == 0)
			;
		else
			push(stack, sp[i]);
		i++;
	}
	(*stack)->ptr[(*stack)->tail + 1] = NULL;
	return (0);
}

char	*normalize_path(const char *path, char *pwd)
{
	int		i;
	int		ri;
	char	*result;
	t_stack	*stack;

	i = 0;
	ri = 0;
	result = malloc(ft_strlen(path) + ft_strlen(pwd) + 1);
	if (result == NULL)
		return (NULL);
	if (create_stack(path, pwd, &stack) == 1)
		return (NULL);
	if (stack->ptr[0] == NULL)
		return ("/");
	while (stack->ptr[i] != NULL)
	{
		ri += ft_strlcpy(&result[ri], "/", 2);
		ri += ft_strlcpy(&result[ri], stack->ptr[i],
				ft_strlen(stack->ptr[i]) + 1);
		i++;
	}
	return (result);
}

// ******** test for normalize_path ********

#include <string.h>
#define GREEN "\x1b[32m"
#define RED "\x1b[31m"
#define RESET "\x1b[0m"

int	main() {
	char	*path = "./A/B/C/../D/E////F/..///././.";
	char	*result = normalize_path(path, "/It's/PWD/PATH");

	/*
	 	expected
		/It's/PWD/PATH/A/B/D/E
	*/

	printf("BEFORE	:%s\n", path);
	printf("AFTER	:%s\n", result);
}

// **********************************************



//static char	*normalize_path(const char *path, char *pwd)
//{
//	char	**sp;
//	char	*result;
//	int		i;
//	int		ri;

//	sp = val_manager(path, pwd, &result);
//	if (sp == NULL)
//		return (NULL);
//	ri = 0;
//	i = 0;
//	printf("%s\n", result);
//	while (sp[i] != NULL)
//	{
//		if (sp[i + 1] != NULL && ft_strncmp(sp[i + 1], "..", 3) == 0)
//			i += 2;
//		else if (ft_strncmp(sp[i], ".", 2) == 0
//			|| ft_strncmp(sp[i], "..", 3) == 0)
//			i++;
//		else
//		{
//			ri += ft_strlcpy(&result[ri], "/", 2);
//			ri += ft_strlcpy(&result[ri], sp[i], ft_strlen(sp[i]) + 1);
//			i++;
//		}
//	}
//	free_ptr_array(sp);
//	return (result);
//}