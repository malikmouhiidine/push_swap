/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:25:13 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/18 02:21:05 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	apply_swap_push(t_list **stack_a, t_list **stack_b, t_list *operations)
{
	if (!ft_strcmp(operations->content, "sa\n"))
		*stack_a = swap(*stack_a);
	else if (!ft_strcmp(operations->content, "sb\n"))
		*stack_b = swap(*stack_b);
	else if (!ft_strcmp(operations->content, "ss\n"))
	{
		*stack_a = swap(*stack_a);
		*stack_b = swap(*stack_b);
	}
	else if (!ft_strcmp(operations->content, "pa\n"))
		push(stack_b, stack_a);
	else if (!ft_strcmp(operations->content, "pb\n"))
		push(stack_a, stack_b);
}

void	apply_rotate_reverse(t_list **stack_a, t_list **stack_b,
			t_list *operations)
{
	if (!ft_strcmp(operations->content, "ra\n"))
		*stack_a = rotate(*stack_a);
	else if (!ft_strcmp(operations->content, "rb\n"))
		*stack_b = rotate(*stack_b);
	else if (!ft_strcmp(operations->content, "rr\n"))
	{
		*stack_a = rotate(*stack_a);
		*stack_b = rotate(*stack_b);
	}
	else if (!ft_strcmp(operations->content, "rra\n"))
		*stack_a = reverse_rotate(*stack_a);
	else if (!ft_strcmp(operations->content, "rrb\n"))
		*stack_b = reverse_rotate(*stack_b);
	else if (!ft_strcmp(operations->content, "rrr\n"))
	{
		*stack_a = reverse_rotate(*stack_a);
		*stack_b = reverse_rotate(*stack_b);
	}
}

void	apply_operations(t_list **stack_a, t_list **stack_b, t_list *operations)
{
	while (operations)
	{
		apply_swap_push(stack_a, stack_b, operations);
		apply_rotate_reverse(stack_a, stack_b, operations);
		operations = operations->next;
	}
}
