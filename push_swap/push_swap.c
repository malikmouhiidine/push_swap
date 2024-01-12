/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 08:59:16 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/12 12:29:54 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	sort_3_numbers(t_list	**stack_a, t_list **stack_b,
			t_list **operations)
{
	if ((*stack_a)->content > (*stack_a)->next->content)
	{
		if ((*stack_a)->content < (*stack_a)->next->next->content)
			ft_lstadd_back(operations, ft_lstnew("sa\n"));
		else if ((*stack_a)->next->content > (*stack_a)->next->next->content)
		{
			ft_lstadd_back(operations, ft_lstnew("sa\n"));
			ft_lstadd_back(operations, ft_lstnew("rra\n"));
		}
		else
			ft_lstadd_back(operations, ft_lstnew("ra\n"));
		apply_operations(stack_a, stack_b, *operations);
	}
	if ((*stack_a)->content > (*stack_a)->next->next->content)
		ft_lstadd_back(operations, ft_lstnew("rra\n"));
	else if ((*stack_a)->next->content > (*stack_a)->next->next->content)
	{
		ft_lstadd_back(operations, ft_lstnew("sa\n"));
		ft_lstadd_back(operations, ft_lstnew("ra\n"));
	}
	apply_operations(stack_a, stack_b, *operations);
}

t_list	*find_closest_min(t_list *node, t_list **stack_a)
{
	t_list *closest;
	t_list *tmp;
	int min;

	tmp = *stack_a;
	min = INT_MAX;
	closest = NULL;
	while (tmp)
	{
		if (node->content > tmp->content && node->content - tmp->content < min)
		{
			min = node->content - tmp->content;
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
	max = tmp->content;
	target = tmp;
	while (tmp)
	{
		if (tmp->content > max)
		{
			max = tmp->content;
			target = tmp;
		}
		tmp = tmp->next;
	}
	return (target);
}

t_list	*find_target(t_list *node, t_list **stack_b, t_list **stack_a)
{
	t_list	*target;
	
	target = find_closest_min(node, stack_a);
	if (target == NULL)
		target = find_max(*stack_a);
	return (target);
}

// push node and target to top of their perspective stacks, and keep in mind that you can use rr or rrr to use less operations and by seeing if their both above or below the middle of the stack
t_list	*push_node_target_totop(t_list **stack_b, t_list **stack_a,
            t_list *node, t_list *target)
{
    t_list	*operations;
    int		node_index;
    int		target_index;

    operations = NULL;
    node_index = get_index(*stack_b, node);
    target_index = get_index(*stack_a, target);
    if (node_index < ft_lstsize(*stack_b) / 2 && target_index < ft_lstsize(*stack_a) / 2)
    {
        while (node_index-- && target_index--)
            ft_lstadd_back(&operations, ft_lstnew("rr\n"));
        while (node_index-- >= 0)
            ft_lstadd_back(&operations, ft_lstnew("rb\n"));
        while (target_index-- >= 0)
            ft_lstadd_back(&operations, ft_lstnew("ra\n"));
    }
    else if (node_index >= ft_lstsize(*stack_b) / 2 && target_index >= ft_lstsize(*stack_a) / 2)
    {
        while (node_index++ < ft_lstsize(*stack_b) && target_index++ < ft_lstsize(*stack_a))
            ft_lstadd_back(&operations, ft_lstnew("rrr\n"));
        while (node_index++ < ft_lstsize(*stack_b))
            ft_lstadd_back(&operations, ft_lstnew("rrb\n"));
        while (target_index++ < ft_lstsize(*stack_a))
            ft_lstadd_back(&operations, ft_lstnew("rra\n"));
    }
    else
    {
        if (node_index < ft_lstsize(*stack_b) / 2)
            while (node_index--)
                ft_lstadd_back(&operations, ft_lstnew("rb\n"));
        else
            while (node_index++ < ft_lstsize(*stack_b))
                ft_lstadd_back(&operations, ft_lstnew("rrb\n"));
        if (target_index < ft_lstsize(*stack_a) / 2)
            while (target_index--)
                ft_lstadd_back(&operations, ft_lstnew("ra\n"));
        else
            while (target_index++ < ft_lstsize(*stack_a))
                ft_lstadd_back(&operations, ft_lstnew("rra\n"));
    }
    return (operations);
}

t_list	*push_node_above_target(t_list **stack_b, t_list **stack_a,
			t_list *node, t_list *target)
{
	t_list	*operations;
	
	operations = push_node_target_totop(stack_b, stack_a, node, target);
	ft_lstadd_back(&operations, ft_lstnew("pa\n"));
	return (operations);
}

void	sort_4_numbers(t_list **stack_a, t_list **stack_b, t_list **operations)
{
	t_list	*node;
	t_list	*target;

	push(stack_a, stack_b);
	sort_3_numbers(stack_a, stack_b, operations);
	node = *stack_b;
	target = find_target(node, stack_b, stack_a);
	ft_lstadd_back(operations, push_node_above_target(stack_b, stack_a, node, target));
	apply_operations(stack_a, stack_b, *operations);
	make_min_on_top(stack_a, operations);
}

void	turk_sort_numbers(t_list **stack_a, t_list **stack_b,
			t_list **operations)
{
	while (!is_sorted(*stack_a))
	{

	}
}

t_list	*get_to_sort_operations(t_list *stack_a, t_list *stack_b)
{
	t_list	*operations;

	operations = NULL;
	if (is_sorted(stack_a))
		return (NULL);
	else if (ft_lstsize(stack_a) == 2)
	{
		operations = ft_lstnew("sa\n");
		apply_operations(&stack_a, &stack_b, operations);
		return (operations);
	}
	else if (ft_lstsize(stack_a) == 3)
	{
		sort_3_numbers(&stack_a, &stack_b, &operations);
		return (operations);
	}
	else if (ft_lstsize(stack_a) == 4)
	{
		sort_4_numbers(&stack_a, &stack_b, &operations);
		return (operations);
	}
	else
	{
		turk_sort_numbers(&stack_a, &stack_b, &operations);
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
	operations = get_to_sort_operations(stack_a, stack_b);
	while (operations)
	{
		ft_putstr_fd(operations->content, 1);
		operations = operations->next;
	}
	return (0);
}
