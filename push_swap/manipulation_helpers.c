/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:14:18 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/21 09:52:50 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_list	*make_min_on_top_ops(t_list **stack_a)
{
	t_list	*operations;
	t_list	*target;
	int		index;

	operations = NULL;
	target = find_min(*stack_a);
	index = get_index(*stack_a, target);
	if (index < ft_lstsize(*stack_a) / 2)
		while (index--)
			ft_lstadd_back(&operations, ft_lstnew("ra\n"));
	else
		while (index++ < ft_lstsize(*stack_a))
			ft_lstadd_back(&operations, ft_lstnew("rra\n"));
	return (operations);
}

t_list	*find_target(t_list *node, t_list **stack, int closest_bigger)
{
	t_list	*target;

	if (closest_bigger)
	{
		target = find_closest_bigger(node, stack);
		if (target == NULL)
			target = find_min(*stack);
	}
	else
	{
		target = find_closest_min(node, stack);
		if (target == NULL)
			target = find_max(*stack);
	}
	return (target);
}

t_list	*get_to_sort_operations(t_list **stack_a, t_list **stack_b)
{
	t_list	*tmp;
	t_list	*operations;

	operations = NULL;
	if (is_sorted(*stack_a))
		return (NULL);
	else if (ft_lstsize(*stack_a) == 2)
	{
		operations = ft_lstnew("sa\n");
		apply_operations(stack_a, stack_b, operations);
	}
	else if (ft_lstsize(*stack_a) == 3)
	{
		tmp = sort_3_numbers(stack_a);
		ft_lstadd_back(&operations, tmp);
		apply_operations(stack_a, stack_b, tmp);
	}
	else if (ft_lstsize(*stack_a) == 4)
		sort_4_numbers(stack_a, stack_b, &operations);
	else
		turk_sort_numbers(stack_a, stack_b, &operations);
	return (operations);
}
