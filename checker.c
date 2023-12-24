/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:25:13 by mmouhiid          #+#    #+#             */
/*   Updated: 2023/12/24 16:09:50 by mmouhiid         ###   ########.fr       */
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
		str++;
	if (!*str || *str == '0')
		return (0);
	while (*str)
	{
		if (*str < '0' || *str++ > '9')
			return (0);
	}
	return (1);
}

int	is_valid_operation(char *operation)
{
	if (!ft_strcmp(operation, "sa"))
		return (1);
	else if (!ft_strcmp(operation, "sb"))
		return (1);
	else if (!ft_strcmp(operation, "ss"))
		return (1);
	else if (!ft_strcmp(operation, "pa"))
		return (1);
	else if (!ft_strcmp(operation, "pb"))
		return (1);
	else if (!ft_strcmp(operation, "ra"))
		return (1);
	else if (!ft_strcmp(operation, "rb"))
		return (1);
	else if (!ft_strcmp(operation, "rr"))
		return (1);
	else if (!ft_strcmp(operation, "rra"))
		return (1);
	else if (!ft_strcmp(operation, "rrb"))
		return (1);
	else if (!ft_strcmp(operation, "rrr"))
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
	while (operation && is_valid_operation(operation))
		ft_lstadd_back(&operations, ft_lstnew(operation));
	return (operations);
}

t_list	*apply_operations(t_list *stack_a, t_list *stack_b, char **operations)
{

}

int	main(int argc, char **argv)
{
	int		i;
	int		operations_num;
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
		if (!operations)
			exit_handler();
		if (is_sorted(apply_operations(stack_a, stack_b, operations)))
			ft_putstr_fd("OK\n", 1);
		else
			ft_putstr_fd("KO\n", 1);
	}
	return (0);
}
