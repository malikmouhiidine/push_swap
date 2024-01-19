/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:14:18 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/19 15:52:22y mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_list	*push_node_target_totop(t_list **stack_b, t_list **stack_a,
			t_list *node, t_list *target)
{
	t_list	*operations;
	int		node_index;
	int		target_index;
	int		stack_b_size;
	int		stack_a_size;

	operations = NULL;
	node_index = get_index(*stack_b, node);
	target_index = get_index(*stack_a, target);
	stack_b_size = ft_lstsize(*stack_b);
	stack_a_size = ft_lstsize(*stack_a);
	if (node_index < (float)stack_b_size / 2.0
		&& target_index < (float)stack_a_size / 2.0)
	{
		while (node_index > 0 && target_index > 0)
		{
			ft_lstadd_back(&operations, ft_lstnew("rr\n"));
			node_index--;
			target_index--;
		}
		while (node_index > 0)
		{
			ft_lstadd_back(&operations, ft_lstnew("rb\n"));
			node_index--;
		}
		while (target_index > 0)
		{
			ft_lstadd_back(&operations, ft_lstnew("ra\n"));
			target_index--;
		}
	}
	else if (node_index >= (float)stack_b_size / 2.0
		&& target_index >= (float)stack_a_size / 2.0)
	{
		while (node_index < stack_b_size && target_index < stack_a_size)
		{
			ft_lstadd_back(&operations, ft_lstnew("rrr\n"));
			node_index++;
			target_index++;
		}
		while (node_index < stack_b_size)
		{
			ft_lstadd_back(&operations, ft_lstnew("rrb\n"));
			node_index++;
		}
		while (target_index < stack_a_size)
		{
			ft_lstadd_back(&operations, ft_lstnew("rra\n"));
			target_index++;
		}
	}
	else
	{
		if (node_index < (float)stack_b_size / 2.0)
		{
			while (node_index > 0)
			{
				ft_lstadd_back(&operations, ft_lstnew("rb\n"));
				node_index--;
			}
		}
		else
		{
			while (node_index < stack_b_size)
			{
				ft_lstadd_back(&operations, ft_lstnew("rrb\n"));
				node_index++;
			}
		}
		if (target_index < (float)stack_a_size / 2.0)
		{
			while (target_index > 0)
			{
				ft_lstadd_back(&operations, ft_lstnew("ra\n"));
				target_index--;
			}
		}
		else
		{
			while (target_index < stack_a_size)
			{
				ft_lstadd_back(&operations, ft_lstnew("rra\n"));
				target_index++;
			}
		}
	}
	return (operations);
}

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
	t_list 	*tmp;
	t_list	*operations;

	operations = NULL;
	if (is_sorted(*stack_a))
		return (NULL);
	else if (ft_lstsize(*stack_a) == 2)
	{
		operations = ft_lstnew("sa\n");
		apply_operations(stack_a, stack_b, operations);
		return (operations);
	}
	else if (ft_lstsize(*stack_a) == 3)
	{
		tmp = sort_3_numbers(stack_a);
		ft_lstadd_back(&operations, tmp);
		apply_operations(stack_a, stack_b, tmp);
		return (operations);
	}
	else if (ft_lstsize(*stack_a) == 4)
	{
		sort_4_numbers(stack_a, stack_b, &operations);
		return (operations);
	}
	else
	{
		turk_sort_numbers(stack_a, stack_b, &operations);
		return (operations);
	}
}
