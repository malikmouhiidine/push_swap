/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:25:13 by mmouhiid          #+#    #+#             */
/*   Updated: 2023/12/25 08:54:638y mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line/get_next_line.h"
#include <stdio.h>

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	is_valid_int(char *str)
{
	if (*str == '-')
	{
		if (!*++str || *str == '0')
			return (0);
	}
	while (*str)
	{
		if (*str < '0' || *str++ > '9')
			return (0);
	}
	return (1);
}

int	is_valid_operation(char *operation)
{
	if (!ft_strcmp(operation, "sa\n"))
		return (1);
	else if (!ft_strcmp(operation, "sb\n"))
		return (1);
	else if (!ft_strcmp(operation, "ss\n"))
		return (1);
	else if (!ft_strcmp(operation, "pa\n"))
		return (1);
	else if (!ft_strcmp(operation, "pb\n"))
		return (1);
	else if (!ft_strcmp(operation, "ra\n"))
		return (1);
	else if (!ft_strcmp(operation, "rb\n"))
		return (1);
	else if (!ft_strcmp(operation, "rr\n"))
		return (1);
	else if (!ft_strcmp(operation, "rra\n"))
		return (1);
	else if (!ft_strcmp(operation, "rrb\n"))
		return (1);
	else if (!ft_strcmp(operation, "rrr\n"))
		return (1);
	return (0);
}

void	exit_handler(void)
{
	ft_putstr_fd("Error\n", 1);
	exit(1);
}

int	is_sorted(t_list *stack)
{
	while (stack)
	{
		if (stack->next && stack->next->content < stack->content)
			return (0);
		stack = stack->next;
	}
	return (1);
}

t_list	*get_operations()
{
	t_list *operations;
	char	*operation;

	operations = NULL;
	operation = get_next_line(0);
	while (operation)
	{
		if (!is_valid_operation(operation))
			exit_handler();
		ft_lstadd_back(&operations, ft_lstnew(operation));
		operation = get_next_line(0);
	}
	return (operations);
}

t_list	*swap(t_list *stack)
{
	int	*tmp;

	if (stack && stack->next)
	{
		tmp = stack->content;
		stack->content = stack->next->content;
		stack->next->content = tmp;
	}
	return (stack);
}

void	push(t_list **stack_a, t_list **stack_b)
{
	t_list	*tmp;

	if (*stack_a)
	{
		tmp = (*stack_a)->next;
		(*stack_a)->next = *stack_b;
		*stack_b = *stack_a;
		*stack_a = tmp;
	}
}

t_list	*rotate(t_list *stack)
{
	t_list	*tmp;
	t_list	*last;

	if (stack && stack->next)
	{
		tmp = stack;
		stack = stack->next;
		last = stack;
		while (last->next)
			last = last->next;
		last->next = tmp;
		tmp->next = NULL;
	}
	return (stack);
}

t_list	*reverse_rotate(t_list *stack)
{
	t_list	*tmp;
	t_list	*last;

	if (stack && stack->next)
	{
		last = stack;
		while (last->next->next)
			last = last->next;
		tmp = last->next;
		last->next = NULL;
		tmp->next = stack;
		stack = tmp;
	}
	return (stack);
}

t_list	*apply_operations(t_list *stack_a, t_list *stack_b, t_list *operations)
{
	while (operations)
	{
		if (!ft_strcmp(operations->content, "sa\n"))
			stack_a = swap(stack_a);
		else if (!ft_strcmp(operations->content, "sb\n"))
			stack_b = swap(stack_b);
		else if (!ft_strcmp(operations->content, "ss\n"))
		{
			stack_a = swap(stack_a);
			stack_b = swap(stack_b);
		}
		else if (!ft_strcmp(operations->content, "pa\n"))
			push(&stack_b, &stack_a);
		else if (!ft_strcmp(operations->content, "pb\n"))
			push(&stack_a, &stack_b);
		else if (!ft_strcmp(operations->content, "ra\n"))
			stack_a = rotate(stack_a);
		else if (!ft_strcmp(operations->content, "rb\n"))
			stack_b = rotate(stack_b);
		else if (!ft_strcmp(operations->content, "rr\n"))
		{
			stack_a = rotate(stack_a);
			stack_b = rotate(stack_b);
		}
		else if (!ft_strcmp(operations->content, "rra\n"))
			stack_a = reverse_rotate(stack_a);
		else if (!ft_strcmp(operations->content, "rrb\n"))
			stack_b = reverse_rotate(stack_b);
		else if (!ft_strcmp(operations->content, "rrr\n"))
		{
			stack_a = reverse_rotate(stack_a);
			stack_b = reverse_rotate(stack_b);
		}
		operations = operations->next;
	}
	return (stack_a);
}

int	main(int argc, char **argv)
{
	int		i;
	int		*num;
	char	**tmp_nums;
	t_list	*operations;
	t_list	*stack_a;
	t_list	*stack_b;

	if (argc < 2)
		return (0);
	stack_a = NULL;
	stack_b = NULL;
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
				ft_lstadd_front(&stack_a, ft_lstnew(num));
			}
			else
				exit_handler();
		}
	}
	if (!is_sorted(stack_a))
	{
		operations = get_operations();
		if (is_sorted(apply_operations(stack_a, stack_b, operations)))
			ft_putstr_fd("OK\n", 1);
		else
			ft_putstr_fd("KO\n", 1);
	}
	return (0);
}
