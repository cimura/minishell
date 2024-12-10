/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 23:24:08 by cimy              #+#    #+#             */
/*   Updated: 2024/12/10 17:17:25 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

static char	*create_base_sp(char *pwd, char *path)
{
	int		i;
	int		pwd_len;
	int		path_len;
	char	*sp_src;

	pwd_len = ft_strlen(pwd);
	path_len = ft_strlen(path);
	i = 0;
	if (path[0] == '/')
	{
		sp_src = malloc(path_len + 1);
		if (sp_src == NULL)
			return (NULL);
		ft_strcpy(sp_src, path, path_len + 1);
	}
	else
	{
		sp_src = malloc(pwd_len + path_len + 2);
		if (sp_src == NULL)
			return (NULL);
		i += ft_strcpy(&sp_src[i], pwd, pwd_len);
		i += ft_strcpy(&sp_src[i], "/", 1);
		i += ft_strcpy(&sp_src[i], path, path_len);
	}
	return (sp_src);
}

static char	**val_manager(char *path, char *pwd)
{
	char	*sp_src;
	char	**sp;

	sp_src = create_base_sp(pwd, path);
	if (sp_src == NULL)
		return (NULL);
	sp = ft_split(sp_src, '/');
	free(sp_src);
	return (sp);
}

static int	create_stack(char *path, char *pwd, t_stack *stack)
{
	int		i;
	char	**sp;

	sp = val_manager(path, pwd);
	if (sp == NULL)
		return (1);
	if (init_stack(stack, sp) == 1)
		return (free_ptr_array(sp), 1);
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
	free_ptr_array(sp);
	stack->ptr[stack->tail + 1] = NULL;
	return (0);
}

char	*normalize_path(char *path, char *pwd)
{
	int		i;
	int		ri;
	char	*result;
	t_stack	stack;

	i = 0;
	ri = 0;
	result = malloc(ft_strlen(path) + ft_strlen(pwd) + 2);
	if (result == NULL)
		return (NULL);
	if (create_stack(path, pwd, &stack) == 1)
		return (free_stack(&stack), NULL);
	if (stack.ptr[0] == NULL)
		return (free_stack(&stack), "/");
	while (stack.ptr[i] != NULL)
	{
		ri += ft_strcpy(&result[ri], "/", 1);
		ri += ft_strcpy(&result[ri], stack.ptr[i],
				ft_strlen(stack.ptr[i]));
		i++;
	}
	free_stack(&stack);
	return (result);
}

// ******** test for normalize_path ********

// #include <string.h>
// #define GREEN "\x1b[32m"
// #define RED "\x1b[31m"
// #define RESET "\x1b[0m"

// int	main() {
// 	char	*path = "./A/B/C/../D/E////F/..///././.";
// 	char	*result = normalize_path(path, "/It's/PWD/PATH");

// 	/*
// 	 	expected
// 		/It's/PWD/PATH/A/B/D/E
// 	*/

// 	printf("BEFORE	:%s\n", path);
// 	printf("AFTER	:%s\n", result);
// }

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
//			ri += ft_strcpy(&result[ri], "/", 2);
//			ri += ft_strcpy(&result[ri], sp[i], ft_strlen(sp[i]) + 1);
//			i++;
//		}
//	}
//	free_ptr_array(sp);
//	return (result);
//}