/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:09:20 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/20 01:26:36 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_list	*sort_3_numbers(t_list **stack_a)
{
	t_list	*operations;

	operations = NULL;
	if (*(int *)(*stack_a)->content > *(int *)(*stack_a)->next->content)
	{
		if (*(int *)(*stack_a)->content
				< *(int *)(*stack_a)->next->next->content)
			add_operations(&operations, "sa\n", NULL);
		else if (*(int *)(*stack_a)->next->content
				> *(int *)(*stack_a)->next->next->content)
			add_operations(&operations, "sa\n", "rra\n");
		else
			add_operations(&operations, "ra\n", NULL);
	}
	else if (*(int *)(*stack_a)->content
			> *(int *)(*stack_a)->next->next->content)
		add_operations(&operations, "rra\n", NULL);
	else if (*(int *)(*stack_a)->next->content
			> *(int *)(*stack_a)->next->next->content)
		add_operations(&operations, "sa\n", "ra\n");
	return (operations);
}

void	sort_4_numbers(t_list **stack_a, t_list **stack_b, t_list **operations)
{
	t_list	*tmp;
	t_list	*ops;
	t_list	*node;
	t_list	*target;

	ops = NULL;
	node = *stack_b;
	push(stack_a, stack_b);
	add_operation(operations, "pb\n");
	ft_lstadd_back(operations, sort_3_numbers(stack_a));
	apply_operations(stack_a, stack_b, sort_3_numbers(stack_a));
	target = find_target(node, stack_a, 1);
	ft_lstadd_back(&ops, push_node_target_totop(stack_b,
			stack_a, node, target));
	add_operation(&ops, "pa\n");
	ft_lstadd_back(operations, ops);
	apply_operations(stack_a, stack_b, ops);
	tmp = make_min_on_top_ops(stack_a);
	ft_lstadd_back(operations, tmp);
	apply_operations(stack_a, stack_b, tmp);
}

t_list	*find_cheapest_node(t_list **stack_a,
		t_list **stack_b, int *cheapest_score)
{
	int			current_score;
	t_list		*cheapest_node;
	t_list		*tmp;
	long long	median;

	tmp = *stack_b;
	cheapest_node = NULL;
	while (tmp)
	{
		median = (long long)push_node_target_totop(stack_b, stack_a,
				tmp, find_target(tmp, stack_a, 1));
		current_score = ft_lstsize((t_list *)median);
		if (current_score < *cheapest_score)
		{
			*cheapest_score = current_score;
			cheapest_node = tmp;
		}
		while (median)
		{
			free((t_list *)median);
			median = (long long)(((t_list *)median)->next);
		}
		tmp = tmp->next;
	}
	return (cheapest_node);
}

void	find_and_push_cheapest_node(t_list **stack_a,
		t_list **stack_b, t_list **operations)
{
	int		cheapest_score;
	t_list	*cheapest_node;
	t_list	*tmp;

	cheapest_score = INT_MAX;
	while (*stack_b)
	{
		cheapest_node = find_cheapest_node(stack_a, stack_b, &cheapest_score);
		tmp = push_node_target_totop(stack_b, stack_a, cheapest_node,
				find_target(cheapest_node, stack_a, 1));
		ft_lstadd_back(operations, tmp);
		apply_operations(stack_a, stack_b, tmp);
		apply_and_add_operation(stack_a, stack_b, operations, "pa\n");
	}
}

void	turk_sort_numbers(t_list **stack_a,
		t_list **stack_b, t_list **operations)
{
	long long	median;
	t_list		*tmp;

	push_and_add_operations(stack_a, stack_b, operations);
	median = (*(int *)find_max(*stack_a)->content
			+ *(int *)find_min(*stack_a)->content) / 2;
	apply_operations_based_on_median(stack_a, stack_b, operations, median);
	tmp = sort_3_numbers(stack_a);
	ft_lstadd_back(operations, tmp);
	apply_operations(stack_a, stack_b, tmp);
	find_and_push_cheapest_node(stack_a, stack_b, operations);
	tmp = make_min_on_top_ops(stack_a);
	ft_lstadd_back(operations, tmp);
	apply_operations(stack_a, stack_b, tmp);
}
