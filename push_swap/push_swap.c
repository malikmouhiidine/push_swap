/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 00:24:00 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/17 23:23:44 by mmouhiid         ###   ########.fr       */
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

t_list	*find_closest_min(t_list *node, t_list **stack_a)
{
	t_list	*closest;
	t_list	*tmp;
	int		min;

	tmp = *stack_a;
	min = INT_MAX;
	closest = NULL;
	while (tmp)
	{
		if (*(int *)node->content > *(int *)tmp->content
			&& *(int *)node->content - *(int *)tmp->content < min)
		{
			min = *(int *)node->content - *(int *)tmp->content;
			closest = tmp;
		}
		tmp = tmp->next;
	}
	return (closest);
}

t_list	*find_closest_bigger(t_list *node, t_list **stack_a)
{
	t_list	*closest;
	t_list	*tmp;
	int		min;

	tmp = *stack_a;
	min = INT_MAX;
	closest = NULL;
	while (tmp)
	{
		if (*(int *)node->content < *(int *)tmp->content
			&& *(int *)tmp->content - *(int *)node->content < min)
		{
			min = *(int *)tmp->content - *(int *)node->content;
			closest = tmp;
		}
		tmp = tmp->next;
	}
	return (closest);
}

t_list	*find_max(t_list *stack_a)
{
	t_list	*tmp;
	t_list	*target;
	int		max;

	tmp = stack_a;
	max = *(int *)tmp->content;
	target = tmp;
	while (tmp)
	{
		if (*(int *)tmp->content > max)
		{
			max = *(int *)tmp->content;
			target = tmp;
		}
		tmp = tmp->next;
	}
	return (target);
}

t_list	*find_min(t_list *stack_a)
{
	t_list	*tmp;
	t_list	*target;
	int		min;

	tmp = stack_a;
	min = *(int *)tmp->content;
	target = tmp;
	while (tmp)
	{
		if (*(int *)tmp->content < min)
		{
			min = *(int *)tmp->content;
			target = tmp;
		}
		tmp = tmp->next;
	}
	return (target);
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

int	get_index(t_list *stack, t_list *node)
{
	int		index;
	t_list	*tmp;

	index = 0;
	tmp = stack;
	while (tmp)
	{
		if (tmp == node)
			return (index);
		index++;
		tmp = tmp->next;
	}
	return (-1);
}

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
	int		current_score;
	int		cheapest_score;
	t_list	*cheapest_node;
	t_list	*tmp;

	push(stack_a, stack_b);
	push(stack_a, stack_b);
	ft_lstadd_back(operations, ft_lstnew("pb\n"));
	ft_lstadd_back(operations, ft_lstnew("pb\n"));
	cheapest_node = NULL;
	//while (ft_lstsize(*stack_a) > 3)
	//{
		//tmp = *stack_a;
		//cheapest_score = INT_MAX;
		//while (tmp)
		//{
			//current_score = ft_lstsize(push_node_target_totop(stack_a, stack_b,
						//tmp, find_target(tmp, stack_b, 0)));
			//if (current_score < cheapest_score)
			//{
				//cheapest_score = current_score;
				//cheapest_node = tmp;
			//}
			//tmp = tmp->next;
		//}
		//ft_lstadd_back(operations, push_node_target_totop(stack_a, stack_b,
				//cheapest_node, find_target(cheapest_node, stack_b, 0)));
		//apply_operations(stack_a, stack_b, push_node_target_totop(
				//stack_a, stack_b, cheapest_node,
				//find_target(cheapest_node, stack_b, 0)));
		//ft_lstadd_back(operations, ft_lstnew("pb\n"));
		//apply_operations(stack_a, stack_b, ft_lstnew("pb\n"));
	//}
	int median = (*(int *)find_max(*stack_a)->content + *(int *)find_min(*stack_a)->content) / 2;
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

t_list	*get_to_sort_operations(t_list **stack_a, t_list **stack_b)
{
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
		ft_lstadd_back(&operations, sort_3_numbers(stack_a));
		apply_operations(stack_a, stack_b, sort_3_numbers(stack_a));
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

int	main(int argc, char **argv)
{
	t_list	*operations;
	t_list	*stack_a;
	t_list	*stack_b;

	if (argc < 2)
		return (0);
	stack_a = NULL;
	stack_b = NULL;
	iterate_through_args(argc, argv, &stack_a);
	operations = get_to_sort_operations(&stack_a, &stack_b);
	while (operations)
	{
		ft_putstr_fd(operations->content, 1);
		operations = operations->next;
	}
	return (0);
}
