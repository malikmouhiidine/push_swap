/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 08:59:16 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/11 14:56626112mouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_list	*sort_3_numbers(t_list	*stack_a)
{
	t_list *operations;
	
	operations = NULL;
	if (stack_a->content > stack_a->next->content)
	{
		if (stack_a->content < stack_a->next->next->content)
			ft_lstadd_back(&operations, ft_lstnew("sa\n"));
		else if (stack_a->next->content > stack_a->next->next->content)
		{
			ft_lstadd_back(&operations, ft_lstnew("sa\n"));
			ft_lstadd_back(&operations, ft_lstnew("rra\n"));
		}
		else
			ft_lstadd_back(&operations, ft_lstnew("ra\n"));
		return (operations);
	}
	if (stack_a->content > stack_a->next->next->content)
		ft_lstadd_back(&operations, ft_lstnew("rra\n"));
	else if (stack_a->next->content > stack_a->next->next->content)
	{
		ft_lstadd_back(&operations, ft_lstnew("sa\n"));
		ft_lstadd_back(&operations, ft_lstnew("ra\n"));
	}
	return (operations);
}

t_list *turk_sort_numbers(t_list *stack_a, t_list *stack_b)
{

}

t_list	*get_to_sort_operations(t_list *stack_a, t_list *stack_b)
{
	t_list	*operations;


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
		operations = sort_3_numbers(stack_a);
		apply_operations(&stack_a, &stack_b, operations);
		return (operations);
	}
	else
	{
		operations = turk_sort_numbers(&stack_a, &stack_b);
		apply_operations(&stack_a, &stack_b, operations);
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
