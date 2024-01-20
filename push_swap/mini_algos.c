/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_algos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 01:25:18 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/20 02:37:41 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	add_operation(t_list **operations, char *operation)
{
	ft_lstadd_back(operations, ft_lstnew(operation));
}

void	apply_and_add_operation(t_list **stack_a, t_list **stack_b,
		t_list **operations, char *operation)
{
	t_list	*tmp;

	tmp = ft_lstnew(operation);
	ft_lstadd_back(operations, tmp);
	apply_operations(stack_a, stack_b, tmp);
}

void	add_operations(t_list **operations, char *operation1, char *operation2)
{
	add_operation(operations, operation1);
	if (operation2)
		add_operation(operations, operation2);
}

void	push_and_add_operations(t_list **stack_a,
		t_list **stack_b, t_list **operations)
{
	push(stack_a, stack_b);
	push(stack_a, stack_b);
	add_operation(operations, "pb\n");
	add_operation(operations, "pb\n");
}

void	apply_operations_based_on_median(t_list **stack_a,
		t_list **stack_b, t_list **operations, long long median)
{
	t_list	*tmp;

	while (ft_lstsize(*stack_a) > 3)
	{
		tmp = *stack_a;
		if (*(int *)tmp->content < median)
		{
			apply_and_add_operation(stack_a, stack_b, operations, "pb\n");
			apply_and_add_operation(stack_a, stack_b, operations, "rrb\n");
		}
		else
		{
			apply_and_add_operation(stack_a, stack_b, operations, "pb\n");
		}
	}
}
