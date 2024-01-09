/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:25:13 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/09 08:35:42 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

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

t_list	*apply_operations(t_list *stack_a, t_list *stack_b, t_list *operations)
{
	while (operations)
	{
		apply_swap_push(&stack_a, &stack_b, operations);
		apply_rotate_reverse(&stack_a, &stack_b, operations);
		operations = operations->next;
	}
	return (stack_a);
}

void	iterate_through_args(int argc, char **argv, t_list **stack_a)
{
	int		i;
	int		*num;
	char	**tmp_nums;

	while (argc-- > 1)
	{
		tmp_nums = ft_split(argv[argc], ' ');
		if (!tmp_nums || !*tmp_nums)
			exit_handler();
		i = 0;
		while (tmp_nums[i])
			i++;
		while (i--)
		{
			if (is_valid_int(tmp_nums[i]))
			{
				num = (int *)malloc(sizeof(int));
				*num = ft_atoi(tmp_nums[i]);
				ft_lstadd_front(stack_a, ft_lstnew(num));
			}
			else
				exit_handler();
		}
	}
}

int	main(int argc, char **argv)
{
	int		size_diff;
	t_list	*operations;
	t_list	*stack_a;
	t_list	*stack_b;

	if (argc < 2)
		return (0);
	stack_a = NULL;
	stack_b = NULL;
	iterate_through_args(argc, argv, &stack_a);
	operations = get_operations();
	size_diff = ft_lstsize(stack_a);
	stack_a = apply_operations(stack_a, stack_b, operations);
	size_diff = ft_lstsize(stack_a) - size_diff;
	if (is_sorted(stack_a) && size_diff == 0)
		ft_putstr_fd("OK\n", 1);
	else
		ft_putstr_fd("KO\n", 1);
	return (0);
}
