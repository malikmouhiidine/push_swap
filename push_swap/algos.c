/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:09:20 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/18 02:20:28 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_list	*sort_3_numbers(t_list	**stack_a)
{
	t_list	*operations;

	operations = NULL;
	if (*(int *)(*stack_a)->content > *(int *)(*stack_a)->next->content)
	{
		if (*(int *)(*stack_a)->content
				< *(int *)(*stack_a)->next->next->content)
			ft_lstadd_back(&operations, ft_lstnew("sa\n"));
		else if (*(int *)(*stack_a)->next->content
				> *(int *)(*stack_a)->next->next->content)
		{
			ft_lstadd_back(&operations, ft_lstnew("sa\n"));
			ft_lstadd_back(&operations, ft_lstnew("rra\n"));
		}
		else
			ft_lstadd_back(&operations, ft_lstnew("ra\n"));
		return (operations);
	}
	if (*(int *)(*stack_a)->content > *(int *)(*stack_a)->next->next->content)
		ft_lstadd_back(&operations, ft_lstnew("rra\n"));
	else if (*(int *)(*stack_a)->next->content
			> *(int *)(*stack_a)->next->next->content)
	{
		ft_lstadd_back(&operations, ft_lstnew("sa\n"));
		ft_lstadd_back(&operations, ft_lstnew("ra\n"));
	}
	return (operations);
}

void	sort_4_numbers(t_list **stack_a, t_list **stack_b, t_list **operations)
{
	t_list	*ops;
	t_list	*node;
	t_list	*target;

	ops = NULL;
	push(stack_a, stack_b);
	ft_lstadd_back(operations, ft_lstnew("pb\n"));
	ft_lstadd_back(operations, sort_3_numbers(stack_a));
	apply_operations(stack_a, stack_b, sort_3_numbers(stack_a));
	node = *stack_b;
	target = find_target(node, stack_a, 1);
	ft_lstadd_back(&ops,
		push_node_target_totop(stack_b, stack_a, node, target));
	ft_lstadd_back(&ops, ft_lstnew("pa\n"));
	ft_lstadd_back(operations, ops);
	apply_operations(stack_a, stack_b, ops);
	ft_lstadd_back(operations, make_min_on_top_ops(stack_a));
	apply_operations(stack_a, stack_b, make_min_on_top_ops(stack_a));
}

void	turk_sort_numbers(t_list **stack_a, t_list **stack_b,
			t_list **operations)
{
	int		median;
	int		current_score;
	int		cheapest_score;
	t_list	*cheapest_node;
	t_list	*tmp;

	push(stack_a, stack_b);
	push(stack_a, stack_b);
	ft_lstadd_back(operations, ft_lstnew("pb\n"));
	ft_lstadd_back(operations, ft_lstnew("pb\n"));
	cheapest_node = NULL;
	median = (*(int *)find_max(*stack_a)->content
			+ *(int *)find_min(*stack_a)->content) / 2;
	while (ft_lstsize(*stack_a) > 3)
	{
		tmp = *stack_a;
		if (*(int *)tmp->content < median)
		{
			ft_lstadd_back(operations, ft_lstnew("pb\n"));
			apply_operations(stack_a, stack_b, ft_lstnew("pb\n"));
			ft_lstadd_back(operations, ft_lstnew("rrb\n"));
			apply_operations(stack_a, stack_b, ft_lstnew("rrb\n"));
		}
		else
		{
			ft_lstadd_back(operations, ft_lstnew("pb\n"));
			apply_operations(stack_a, stack_b, ft_lstnew("pb\n"));
		}
	}
	ft_lstadd_back(operations, sort_3_numbers(stack_a));
	apply_operations(stack_a, stack_b, sort_3_numbers(stack_a));
	while (*stack_b)
	{
		tmp = *stack_b;
		cheapest_score = INT_MAX;
		while (tmp)
		{
			current_score = ft_lstsize(push_node_target_totop(stack_b, stack_a,
						tmp, find_target(tmp, stack_a, 1)));
			if (current_score < cheapest_score)
			{
				cheapest_score = current_score;
				cheapest_node = tmp;
			}
			tmp = tmp->next;
		}
		ft_lstadd_back(operations, push_node_target_totop(stack_b, stack_a,
				cheapest_node, find_target(cheapest_node, stack_a, 1)));
		apply_operations(stack_a, stack_b, push_node_target_totop(
				stack_b, stack_a,
				cheapest_node, find_target(cheapest_node, stack_a, 1)));
		ft_lstadd_back(operations, ft_lstnew("pa\n"));
		apply_operations(stack_a, stack_b, ft_lstnew("pa\n"));
	}
	ft_lstadd_back(operations, make_min_on_top_ops(stack_a));
	apply_operations(stack_a, stack_b, make_min_on_top_ops(stack_a));
}
