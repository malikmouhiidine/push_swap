/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:09:20 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/21 10:38:26 by mmouhiid         ###   ########.fr       */
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
			(ft_lstadd_back(&operations,
					ft_lstnew("sa\n")), ft_lstadd_back(&operations,
					ft_lstnew("rra\n")));
		else
			ft_lstadd_back(&operations, ft_lstnew("ra\n"));
		return (operations);
	}
	if (*(int *)(*stack_a)->content > *(int *)(*stack_a)->next->next->content)
		ft_lstadd_back(&operations, ft_lstnew("rra\n"));
	else if (*(int *)(*stack_a)->next->content
			> *(int *)(*stack_a)->next->next->content)
		(ft_lstadd_back(&operations,
				ft_lstnew("sa\n")), ft_lstadd_back(&operations,
				ft_lstnew("ra\n")));
	return (operations);
}

void	sort_4_numbers(t_list **stack_a, t_list **stack_b, t_list **operations)
{
	t_list	*tmp;
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
	tmp = make_min_on_top_ops(stack_a);
	ft_lstadd_back(operations, tmp);
	apply_operations(stack_a, stack_b, tmp);
}

void	b_to_a(t_turk_data *t, t_list **stack_b, t_list **stack_a,
		t_list **operations)
{
	while (t->tmp)
	{
		t->median = (long long)push_node_target_totop(stack_b,
				stack_a, t->tmp, find_target(t->tmp, stack_a, 1));
		t->current_score = ft_lstsize((t_list *)t->median);
		if (t->current_score < t->cheapest_score)
		{
			t->cheapest_score = t->current_score;
			t->cheapest_node = t->tmp;
		}
		while (t->median)
		{
			free((t_list *)t->median);
			t->median = (long long)(((t_list *)t->median)->next);
		}
		t->tmp = t->tmp->next;
	}
	t->tmp = push_node_target_totop(stack_b, stack_a,
			t->cheapest_node, find_target(t->cheapest_node, stack_a, 1));
	ft_lstadd_back(operations, t->tmp);
	apply_operations(stack_a, stack_b, t->tmp);
	t->tmp = ft_lstnew("pa\n");
	ft_lstadd_back(operations, t->tmp);
	apply_operations(stack_a, stack_b, t->tmp);
}

void	a_to_b(t_turk_data *t, t_list **stack_b, t_list **stack_a,
		t_list **operations)
{
	t->tmp = *stack_a;
	if (*(int *)t->tmp->content < t->median)
	{
		t->tmp = ft_lstnew("pb\n");
		ft_lstadd_back(operations, t->tmp);
		apply_operations(stack_a, stack_b, t->tmp);
		t->tmp = ft_lstnew("rrb\n");
		ft_lstadd_back(operations, t->tmp);
		apply_operations(stack_a, stack_b, t->tmp);
	}
	else
	{
		t->tmp = ft_lstnew("pb\n");
		ft_lstadd_back(operations, t->tmp);
		apply_operations(stack_a, stack_b, t->tmp);
	}
}

// median is used in the last part as a holder of the address of the
// list wich is bad design/naming and its better to be fixed in the future
void	turk_sort_numbers(t_list **stack_a, t_list **stack_b,
			t_list **operations)
{
	t_turk_data	t;

	push(stack_a, stack_b);
	push(stack_a, stack_b);
	ft_lstadd_back(operations, ft_lstnew("pb\n"));
	ft_lstadd_back(operations, ft_lstnew("pb\n"));
	t.cheapest_node = NULL;
	t.median = (*(int *)find_max(*stack_a)->content
			+ *(int *)find_min(*stack_a)->content) / 2;
	while (ft_lstsize(*stack_a) > 3)
		a_to_b(&t, stack_b, stack_a, operations);
	t.tmp = sort_3_numbers(stack_a);
	ft_lstadd_back(operations, t.tmp);
	apply_operations(stack_a, stack_b, t.tmp);
	while (*stack_b)
	{
		t.tmp = *stack_b;
		t.cheapest_score = INT_MAX;
		b_to_a(&t, stack_b, stack_a, operations);
	}
	t.tmp = make_min_on_top_ops(stack_a);
	ft_lstadd_back(operations, t.tmp);
	apply_operations(stack_a, stack_b, t.tmp);
}
