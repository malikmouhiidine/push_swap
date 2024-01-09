/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:25:13 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/08 15:45:37 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

t_list	*get_operations(void)
{
	t_list	*operations;
	char	*operation;

	operations = NULL;
	operation = get_next_line(0);
	while (operation)
	{
		if (!is_valid_operation(operation))
			exit_handler();
		ft_lstadd_back(&operations, ft_lstnew(operation));
		operation = get_next_line(0);
	}
	return (operations);
}

t_list	*swap(t_list *stack)
{
	int	*tmp;

	if (stack && stack->next)
	{
		tmp = stack->content;
		stack->content = stack->next->content;
		stack->next->content = tmp;
	}
	return (stack);
}

void	push(t_list **stack_a, t_list **stack_b)
{
	t_list	*tmp;

	if (*stack_a)
	{
		tmp = (*stack_a)->next;
		(*stack_a)->next = *stack_b;
		*stack_b = *stack_a;
		*stack_a = tmp;
	}
}

t_list	*rotate(t_list *stack)
{
	t_list	*tmp;
	t_list	*last;

	if (stack && stack->next)
	{
		tmp = stack;
		stack = stack->next;
		last = stack;
		while (last->next)
			last = last->next;
		last->next = tmp;
		tmp->next = NULL;
	}
	return (stack);
}

t_list	*reverse_rotate(t_list *stack)
{
	t_list	*tmp;
	t_list	*last;

	if (stack && stack->next)
	{
		last = stack;
		while (last->next->next)
			last = last->next;
		tmp = last->next;
		last->next = NULL;
		tmp->next = stack;
		stack = tmp;
	}
	return (stack);
}
