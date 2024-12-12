/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_stack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:50:01 by cimy              #+#    #+#             */
/*   Updated: 2024/12/12 17:57:50 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

int	init_stack(t_stack *stack, char **sp)
{
	stack->tail = -1;
	stack->max = count_char_array_words(sp) + 1;
	stack->ptr = malloc(sizeof(char *) * (stack->max + 1));
	if (stack->ptr == NULL)
		return (1);
	return (0);
}

void	push(t_stack *stack, char *arg)
{
	if (stack->tail > stack->max)
		return ;
	stack->tail++;
	stack->ptr[stack->tail] = ft_strdup(arg);
}

void	pop(t_stack *stack)
{
	if (stack->tail == -1)
		return ;
	free(stack->ptr[stack->tail]);
	stack->ptr[stack->tail] = NULL;
	stack->tail--;
}

void	free_stack(t_stack *stack)
{
	free_ptr_array(stack->ptr);
}
