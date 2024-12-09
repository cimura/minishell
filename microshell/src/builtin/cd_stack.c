/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_stack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:50:01 by cimy              #+#    #+#             */
/*   Updated: 2024/12/09 21:50:30 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

int	init_stack(t_stack **stack, char **sp)
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

void	push(t_stack **stack, char *arg)
{
	if ((*stack)->tail > (*stack)->max)
		return ;
	(*stack)->tail++;
	(*stack)->ptr[(*stack)->tail] = arg;
}

void	pop(t_stack **stack)
{
	if ((*stack)->tail == -1)
		return ;
	(*stack)->ptr[(*stack)->tail] = NULL;
	(*stack)->tail--;
}
